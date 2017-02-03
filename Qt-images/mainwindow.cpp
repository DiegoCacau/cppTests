#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <qdebug.h>
#include <QTableWidget>
#include <QScrollBar>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->cont1=0;
    this->cont2=0;

    //connect changes in tableWidget's selected item and the displayed image
    connect(ui->tableWidget, SIGNAL(itemSelectionChanged()), this, SLOT(changeImages()));

    ui->label->setFixedHeight(1000);
    ui->label_2->setFixedHeight(1000);
    ui->label_3->setFixedHeight(1000);

    //set the scrollAreas
    ui->scrollArea->setWidget(ui->label);
    ui->scrollArea->setWidgetResizable(true);
    ui->label->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

    ui->scrollArea_2->setWidget(ui->label_2);
    ui->scrollArea_2->setWidgetResizable(true);
    ui->label_2->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

    ui->scrollArea_3->setWidget(ui->label_3);
    ui->scrollArea_3->setWidgetResizable(true);
    ui->label_3->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);


    //disable scrollBar and scroll on scrollArea 2 and 3
    ui->scrollArea_2->verticalScrollBar()->setEnabled(false);
    ui->scrollArea_2->horizontalScrollBar()->setEnabled(false);
    ui->scrollArea_2->verticalScrollBar()->setVisible(false);
    ui->scrollArea_2->horizontalScrollBar()->setVisible(false);

    ui->scrollArea_3->verticalScrollBar()->setEnabled(false);
    ui->scrollArea_3->horizontalScrollBar()->setEnabled(false);
    ui->scrollArea_3->verticalScrollBar()->setVisible(false);
    ui->scrollArea_3->horizontalScrollBar()->setVisible(false);

    //connect changes in scrollArea 1 with the scrollAreas 2 and 3
    connect(ui->scrollArea->verticalScrollBar(),SIGNAL(valueChanged(int)),
            this,SLOT(setValueVertical(int)));

    connect(ui->scrollArea->horizontalScrollBar(),SIGNAL(valueChanged(int)),
            this,SLOT(setValueHorizontal(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


int getdir (QString dir, std::vector<QString> &files)
{
    DIR *dp;
    struct dirent *dirp;
    QString filepath = dir, nome;

    if((dp = opendir(dir.toUtf8().constData())) == NULL) {
        qDebug() << "Error(" << errno << ") opening " << dir;
        return errno;
    }
    //get file names
    while ((dirp = readdir(dp)) != NULL) {
        nome.clear();
        nome = dirp->d_name;

        //Avoid files with small name
        if(nome.size() > 5){
           filepath = dir + "/" + dirp->d_name;
           files.push_back(dirp->d_name);
        }
    }
    closedir(dp);
    return 0;
}

void MainWindow::on_pushButton_clicked()
{

    //get the paths
    QString path1 = ui->textEdit->toPlainText();
    QString path2 = ui->textEdit_2->toPlainText();
    QString path3 = ui->textEdit_3->toPlainText();

    //get file names
    std::vector<QString> files = std::vector<QString>();
    if((path1 != NULL)&&(path1 != "")){
        getdir(path1, files);


    }
    //populate tableWidget
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    while (ui->tableWidget->rowCount() > 0)
    {
       ui->tableWidget->removeRow(0);
    }
    for(unsigned int i=0; i<files.size();i++){

        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(files[i]));
    }
}


void MainWindow::changeImages(){
    //clean the 1 image
    ui->label->clear();
    ui->label->update();
    //get current row in tableWidget
    int n = ui->tableWidget->currentRow();

    //get complete filepaths
    QString path = ui->textEdit->toPlainText()+ "/"+ui->tableWidget->item(n,0)->text();
    QString path2 = ui->textEdit_2->toPlainText()+ "/"+ui->tableWidget->item(n,0)->text();
    QString path3 = ui->textEdit_3->toPlainText()+ "/"+ui->tableWidget->item(n,0)->text();

    //display images
    this->pix.load(path);
    this->w = this->pix.width();
    this->h = this->pix.height();
    ui->label->setPixmap(this->pix);
    ui->label->update();

    this->pix2.load(path2);
    ui->label_2->setPixmap(this->pix2);
    ui->label_2->update();

    this->pix3.load(path3);
    ui->label_3->setPixmap(this->pix3);
    ui->label_3->update();

}

//update counter
void MainWindow::on_pushButton_3_clicked()
{
    this->cont1++;
    ui->lcdNumber->display(this->cont1);
}

//update counter
void MainWindow::on_pushButton_4_clicked()
{
    this->cont2++;
    ui->lcdNumber_2->display(this->cont2);
}

//zoom in
void MainWindow::on_pushButton_2_clicked()
{

    this->w = this->w*1.1;
    this->h = this->h*1.1;


    ui->label->setPixmap(this->pix.scaled(this->w,this->h,Qt::KeepAspectRatio));
    ui->label_2->setPixmap(this->pix.scaled(this->w,this->h,Qt::KeepAspectRatio));
    ui->label_3->setPixmap(this->pix.scaled(this->w,this->h,Qt::KeepAspectRatio));


}

//zoom out
void MainWindow::on_pushButton_5_clicked()
{
    this->w = this->w*0.9;
    this->h = this->h*0.9;


    ui->label->setPixmap(this->pix.scaled(this->w,this->h,Qt::KeepAspectRatio));
    ui->label_2->setPixmap(this->pix.scaled(this->w,this->h,Qt::KeepAspectRatio));
    ui->label_3->setPixmap(this->pix.scaled(this->w,this->h,Qt::KeepAspectRatio));

}

//update images positions
void MainWindow::setValueVertical(int x)
{

    ui->scrollArea_2->verticalScrollBar()->setValue(x);
    ui->scrollArea_3->verticalScrollBar()->setValue(x);
}

//update images positions
void MainWindow::setValueHorizontal(int x)
{

    ui->scrollArea_2->horizontalScrollBar()->setValue(x);
    ui->scrollArea_3->horizontalScrollBar()->setValue(x);
}

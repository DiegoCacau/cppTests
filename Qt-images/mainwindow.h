#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPixmap pix;
    QPixmap pix2;
    QPixmap pix3;
    int cont1;
    int cont2;
    int h;
    int w;


public slots:
    //update displayed images
    void changeImages();
    //slots for update position of scrollBar
    void setValueVertical(int);
    void setValueHorizontal(int);

private slots:
    //load the tableWidget with the file names
    void on_pushButton_clicked();

    //update lcd counter
    void on_pushButton_3_clicked();

    //update lcd counter
    void on_pushButton_4_clicked();

    //zoom in
    void on_pushButton_2_clicked();

    //zoom out
    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

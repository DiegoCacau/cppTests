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
    int max_h = 1000;
    int max_w = 500;
    int min_h = 1000;
    int min_w = 1000;


public slots:
    void changeImages();

private slots:
    void on_pushButton_clicked();


    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

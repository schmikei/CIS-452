#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "memory.h"
#include "page_table.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
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

private slots:

    void updateFrames();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void setup_frames();


    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<page_table*> the_pages;
    //gui frames to match up with the memory objects
    QVector<QTextEdit*> frame_list;
    //memory object to simulate memory
    memory* my_memory;
    void recreateFrames();
    void clearLayout(QLayout* layout);
    int frameSize;
};

#endif // MAINWINDOW_H

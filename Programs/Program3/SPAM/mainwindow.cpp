#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "memory.h"
#include <iostream>




/*******************************************************************************
 * Constructor used to initialize ui, memory and page_table
 * objects
 * @author Keith Schmitt
 * @version 1.0
 ******************************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    setup_frames();
    ui->verticalLayout->setSpacing(0);
    my_memory = new memory;
    this->frameSize = 512;
    updateFrames();
}

/******************************************************************************
 * method to update the gui frames
 ******************************************************************************/
void MainWindow::updateFrames(){
    for(int i = 0; i < frame_list.count(); ++i){
        // underlying storage has things that are free stored as -1
        if (my_memory->getFrame(i) == -1){
            frame_list.at(i)->setText(QString("Free"));
        }
        //we want to print out the pid and whether it is a code or data section
        else{
            frame_list.at(i)->setText("P" + QString::number(my_memory->getFrameOwner(i))
                                      +": " + "-- " + QString
                                      ::fromStdString(my_memory->getFrameType(i)));
        }
    }
}

/*******************************************************************************
 * called in constructor to setup gui frames
 * to be put into the framelist vector
 ******************************************************************************/
void MainWindow::setup_frames(){
    frame_list.push_back(ui->textEdit_1);
    frame_list.push_back(ui->textEdit_2);
    frame_list.push_back(ui->textEdit_3);
    frame_list.push_back(ui->textEdit_4);
    frame_list.push_back(ui->textEdit_5);
    frame_list.push_back(ui->textEdit_6);
    frame_list.push_back(ui->textEdit_7);
    frame_list.push_back(ui->textEdit_8);
}


/*******************************************************************************
 * destructor, make sure to delete new objects
 ******************************************************************************* */
MainWindow::~MainWindow(){
    delete my_memory;
    delete ui;

}


/**********************************************************************************
* allocate all button logic
 ************************************************************************************/
void MainWindow::on_pushButton_clicked(){
    QStringList lines;
    lines = ui->textEdit->toPlainText().split('\n', QString::SkipEmptyParts);
    for (QStringList::iterator iter = lines.begin(); iter != lines.end(); ++iter){
        ui->plainTextEdit->insertPlainText(  *iter +'\n');
        QString line = *iter;
        QStringList arguments;
        arguments = line.split(' ');


        //checking if it is in correct format
        if (arguments.count() == 3 ){
            int process = arguments[0].toInt();
            int code = arguments[1].toInt();
            int data = arguments[2].toInt();
            if (arguments[0] < 0 || arguments[1] < 0 || arguments[2] < 0 ){
                ui->plainTextEdit->clear();
                ui->plainTextEdit->insertPlainText(QString::fromStdString(
                                                       "Sorry error at input: "+
                                                       std::to_string(iter - lines.begin())+
                                                       "\nTry a valid input:\npid code_size data_size\n"
                                                       "or to terminate\nprocess -1\n"));
            }
            else{
                the_pages.push_back(new page_table(process, code, data, my_memory, frameSize));

                ui->plainTextEdit->insertPlainText(QString::fromStdString(
                                                       the_pages[the_pages.size() -1]->allocate(process, code, data)));


            }
        }
        //logic for two inputs on the line; here we wanna see if its termination
        else if( arguments.count() == 2){
            int process = arguments[0].toInt();
            int code = arguments[1].toInt();
            if (code == -1){
                ui->plainTextEdit->insertPlainText(QString::fromStdString(
                                                       my_memory->deallocate(process)));
            }
            else{
                ui->plainTextEdit->clear();
                ui->plainTextEdit->insertPlainText(QString::fromStdString(
                                                       "Sorry error at input: "+std::to_string(
                                                           iter - lines.begin())+"\nTry a valid input:"+
                                                       "\npid code_size data_size\n"+
                                                       "or to terminate\nprocess -1\n"));
            }
        }
        else{
            //incorrect input
            ui->plainTextEdit->clear();
            ui->plainTextEdit->insertPlainText(
                        QString::fromStdString("Sorry error at input: "+std::to_string(
                                                   iter - lines.begin())+"\nTry a valid input:\npid code_size data_size"+
                                               "\ni.e 0 100 200\n"));
        }
        ui->plainTextEdit->verticalScrollBar()->setValue(ui->plainTextEdit->
                                                         verticalScrollBar()->maximum());
        updateFrames();
    }
}

/*******************************************************************************
 * clear button
 ******************************************************************************/
void MainWindow::on_pushButton_2_clicked(){
    ui->textEdit->clear();
    ui->plainTextEdit->clear();

    //delete old memory
    delete my_memory;
    //create new memory
    my_memory = new memory();

    //update the ui
    the_pages.clear();
    updateFrames();
}


/******************************************************************************
 *clear input button
 *******************************************************************************/
void MainWindow::on_pushButton_4_clicked(){
    ui->textEdit->clear();
}

/******************************************************************************
  * change frame size
 ******************************************************************************/
void MainWindow::on_pushButton_3_clicked(){
    QString input = ui->lineEdit->text();
    int i;
    if ((i = input.toInt()) < 0) {
      ui->plainTextEdit->insertPlainText("Please enter something into the text box\n");
    }
    else if (i <= 0 || i > 30 ){
        ui->plainTextEdit->insertPlainText("Invalid frame size, try a positive int and less than 30\n");
    }
    else{
        //ui->verticalLayout->addWidget(new QTextEdit);
        frameSize = 4096/i;
        delete my_memory;
        the_pages.clear();
        frame_list.clear();
        my_memory = new memory;
        my_memory->setSize(frameSize);
        recreateFrames();
        ui->label_4->setText(QString::fromStdString("Frame Size: " + std::to_string(my_memory->getFrameSize()) + " KB"));
        ui->plainTextEdit->setPlainText(QString::fromStdString("Hey so you now have " + std::to_string(frame_list.size()) + " frames of size: "+ std::to_string(my_memory->getFrameSize())));
    }
}


void MainWindow::recreateFrames(){
    clearLayout(ui->verticalLayout);
    int RAMoverFrame = 4096 / my_memory->getFrameSize();
    ui->verticalLayout->activate();
    ui->plainTextEdit->setPlainText(QString::fromStdString("RoverF: "+ std::to_string(RAMoverFrame)));
    for (int i = 0; i < RAMoverFrame; ++i ){
        frame_list.push_back(new QTextEdit);
        ui->verticalLayout->addWidget(frame_list[i]);
        if (my_memory->getFrame(i) == -1){
            frame_list.at(i)->setText(QString("Free"));
        }
        else{
            frame_list.at(i)->setText("P" + QString::number(my_memory->getFrameOwner(i))
                                      +": " + "-- " + QString
                                      ::fromStdString(my_memory->getFrameType(i)));
        }
    }

}


void MainWindow::clearLayout(QLayout* layout){
    QLayoutItem* old_text;
    while((old_text = ui->verticalLayout->takeAt(0)) !=NULL){
        if (old_text->layout()){
            clearLayout(old_text->layout());
            delete old_text->layout();
        }
        if (old_text->widget()){
            delete old_text->widget();
        }
        delete old_text;
    }
}



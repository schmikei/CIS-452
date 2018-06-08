/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionClear;
    QAction *actionclear;
    QAction *actionClear_2;
    QWidget *centralWidget;
    QTextEdit *textEdit;
    QLabel *label;
    QPushButton *pushButton;
    QPlainTextEdit *plainTextEdit;
    QLabel *label_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit_1;
    QTextEdit *textEdit_2;
    QTextEdit *textEdit_3;
    QTextEdit *textEdit_4;
    QTextEdit *textEdit_5;
    QTextEdit *textEdit_6;
    QTextEdit *textEdit_7;
    QTextEdit *textEdit_8;
    QPushButton *pushButton_2;
    QScrollBar *verticalScrollBar;
    QPushButton *pushButton_4;
    QLineEdit *lineEdit;
    QPushButton *pushButton_3;
    QLabel *label_3;
    QLabel *label_4;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(767, 428);
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        actionclear = new QAction(MainWindow);
        actionclear->setObjectName(QStringLiteral("actionclear"));
        actionClear_2 = new QAction(MainWindow);
        actionClear_2->setObjectName(QStringLiteral("actionClear_2"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(10, 30, 121, 191));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 60, 16));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(380, 210, 101, 32));
        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(380, 30, 371, 131));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(380, 10, 60, 16));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(270, 10, 101, 311));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        textEdit_1 = new QTextEdit(verticalLayoutWidget);
        textEdit_1->setObjectName(QStringLiteral("textEdit_1"));
        textEdit_1->setMaximumSize(QSize(16777215, 74));

        verticalLayout->addWidget(textEdit_1);

        textEdit_2 = new QTextEdit(verticalLayoutWidget);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));

        verticalLayout->addWidget(textEdit_2);

        textEdit_3 = new QTextEdit(verticalLayoutWidget);
        textEdit_3->setObjectName(QStringLiteral("textEdit_3"));

        verticalLayout->addWidget(textEdit_3);

        textEdit_4 = new QTextEdit(verticalLayoutWidget);
        textEdit_4->setObjectName(QStringLiteral("textEdit_4"));

        verticalLayout->addWidget(textEdit_4);

        textEdit_5 = new QTextEdit(verticalLayoutWidget);
        textEdit_5->setObjectName(QStringLiteral("textEdit_5"));

        verticalLayout->addWidget(textEdit_5);

        textEdit_6 = new QTextEdit(verticalLayoutWidget);
        textEdit_6->setObjectName(QStringLiteral("textEdit_6"));

        verticalLayout->addWidget(textEdit_6);

        textEdit_7 = new QTextEdit(verticalLayoutWidget);
        textEdit_7->setObjectName(QStringLiteral("textEdit_7"));

        verticalLayout->addWidget(textEdit_7);

        textEdit_8 = new QTextEdit(verticalLayoutWidget);
        textEdit_8->setObjectName(QStringLiteral("textEdit_8"));
        textEdit_8->setMaximumSize(QSize(16777215, 74));

        verticalLayout->addWidget(textEdit_8);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(380, 240, 101, 32));
        verticalScrollBar = new QScrollBar(centralWidget);
        verticalScrollBar->setObjectName(QStringLiteral("verticalScrollBar"));
        verticalScrollBar->setGeometry(QRect(730, 30, 16, 131));
        verticalScrollBar->setOrientation(Qt::Vertical);
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(10, 230, 113, 32));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 300, 81, 21));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(0, 320, 141, 31));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(149, 40, 91, 20));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(140, 70, 121, 16));
        MainWindow->setCentralWidget(centralWidget);
        verticalScrollBar->raise();
        textEdit->raise();
        label->raise();
        pushButton->raise();
        plainTextEdit->raise();
        label_2->raise();
        verticalLayoutWidget->raise();
        pushButton_2->raise();
        pushButton_4->raise();
        lineEdit->raise();
        pushButton_3->raise();
        label_3->raise();
        label_4->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 767, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionClear->setText(QApplication::translate("MainWindow", "Clear", nullptr));
        actionclear->setText(QApplication::translate("MainWindow", "clear", nullptr));
        actionClear_2->setText(QApplication::translate("MainWindow", "Clear", nullptr));
        label->setText(QApplication::translate("MainWindow", "File", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Allocate", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Output", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "Clear", nullptr));
        pushButton_4->setText(QApplication::translate("MainWindow", "Clear Input", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "Change Frame Size", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Mem: 4096 KB", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Frame Size: 512 KB", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

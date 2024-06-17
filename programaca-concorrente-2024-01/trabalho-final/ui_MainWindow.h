/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpenFile;
    QAction *actionExit;
    QAction *actionPrint;
    QAction *actionHelp;
    QAction *actionSave;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBoxGraph;
    QGridLayout *gridLayout;
    QLabel *ImageOutput;
    QLabel *ImageInput;
    QPushButton *convertButton;
    QPushButton *convertButtonC;
    QPlainTextEdit *plainTextOutput;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1002, 666);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icons/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setIconSize(QSize(22, 22));
        actionOpenFile = new QAction(MainWindow);
        actionOpenFile->setObjectName("actionOpenFile");
        actionOpenFile->setEnabled(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icons/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenFile->setIcon(icon1);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionPrint = new QAction(MainWindow);
        actionPrint->setObjectName("actionPrint");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icons/print.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrint->setIcon(icon2);
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName("actionHelp");
        actionHelp->setIcon(icon);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icons/filesave.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon3);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        groupBoxGraph = new QGroupBox(centralwidget);
        groupBoxGraph->setObjectName("groupBoxGraph");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(groupBoxGraph->sizePolicy().hasHeightForWidth());
        groupBoxGraph->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(groupBoxGraph);
        gridLayout->setObjectName("gridLayout");
        ImageOutput = new QLabel(groupBoxGraph);
        ImageOutput->setObjectName("ImageOutput");

        gridLayout->addWidget(ImageOutput, 0, 1, 1, 1);

        ImageInput = new QLabel(groupBoxGraph);
        ImageInput->setObjectName("ImageInput");

        gridLayout->addWidget(ImageInput, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBoxGraph, 0, 0, 1, 1);

        convertButton = new QPushButton(centralwidget);
        convertButton->setObjectName("convertButton");

        gridLayout_2->addWidget(convertButton, 1, 0, 1, 1);

        convertButtonC = new QPushButton(centralwidget);
        convertButtonC->setObjectName("convertButtonC");

        gridLayout_2->addWidget(convertButtonC, 2, 0, 1, 1);

        plainTextOutput = new QPlainTextEdit(centralwidget);
        plainTextOutput->setObjectName("plainTextOutput");

        gridLayout_2->addWidget(plainTextOutput, 3, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1002, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        toolBar->setOrientation(Qt::Orientation::Horizontal);
        toolBar->setIconSize(QSize(22, 22));
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpenFile);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionPrint);
        menuFile->addAction(actionHelp);
        menuFile->addAction(actionExit);
        toolBar->addAction(actionOpenFile);
        toolBar->addAction(actionSave);
        toolBar->addSeparator();
        toolBar->addAction(actionPrint);
        toolBar->addAction(actionHelp);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Segmenta\303\247\303\243o de Imagem por Thresholding", nullptr));
        actionOpenFile->setText(QCoreApplication::translate("MainWindow", "Open File...", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionPrint->setText(QCoreApplication::translate("MainWindow", "Print", nullptr));
        actionHelp->setText(QCoreApplication::translate("MainWindow", "Help", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        groupBoxGraph->setTitle(QCoreApplication::translate("MainWindow", "Views", nullptr));
        ImageOutput->setText(QString());
        ImageInput->setText(QString());
        convertButton->setText(QCoreApplication::translate("MainWindow", "Converter", nullptr));
        convertButtonC->setText(QCoreApplication::translate("MainWindow", "Converter com Concorrencia", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

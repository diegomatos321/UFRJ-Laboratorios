/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionRun;
    QAction *actionNewProject;
    QAction *actionSelectFile;
    QAction *actionSaveResult;
    QAction *actionExit;
    QAction *actionSequentialMode;
    QAction *actionConcurrentMode;
    QAction *actionAbout;
    QAction *actionWelcomePage;
    QAction *actionReadReport;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuMode;
    QMenu *menuAbout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(700, 600);
        MainWindow->setMinimumSize(QSize(700, 600));
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        MainWindow->setTabShape(QTabWidget::TabShape::Rounded);
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName("actionRun");
        actionNewProject = new QAction(MainWindow);
        actionNewProject->setObjectName("actionNewProject");
        actionSelectFile = new QAction(MainWindow);
        actionSelectFile->setObjectName("actionSelectFile");
        actionSaveResult = new QAction(MainWindow);
        actionSaveResult->setObjectName("actionSaveResult");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionSequentialMode = new QAction(MainWindow);
        actionSequentialMode->setObjectName("actionSequentialMode");
        actionConcurrentMode = new QAction(MainWindow);
        actionConcurrentMode->setObjectName("actionConcurrentMode");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        actionWelcomePage = new QAction(MainWindow);
        actionWelcomePage->setObjectName("actionWelcomePage");
        actionReadReport = new QAction(MainWindow);
        actionReadReport->setObjectName("actionReadReport");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");

        verticalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 700, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuMode = new QMenu(menubar);
        menuMode->setObjectName("menuMode");
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName("menuAbout");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuMode->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionRun);
        menuFile->addAction(actionNewProject);
        menuFile->addAction(actionSelectFile);
        menuFile->addAction(actionSaveResult);
        menuFile->addAction(actionExit);
        menuMode->addAction(actionSequentialMode);
        menuMode->addAction(actionConcurrentMode);
        menuAbout->addAction(actionWelcomePage);
        menuAbout->addAction(actionReadReport);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Image Segmentation Tool", nullptr));
        actionRun->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
        actionNewProject->setText(QCoreApplication::translate("MainWindow", "New project", nullptr));
        actionSelectFile->setText(QCoreApplication::translate("MainWindow", "Select File", nullptr));
        actionSaveResult->setText(QCoreApplication::translate("MainWindow", "Save result", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionSequentialMode->setText(QCoreApplication::translate("MainWindow", "Sequential", nullptr));
        actionConcurrentMode->setText(QCoreApplication::translate("MainWindow", "Concurrent", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionWelcomePage->setText(QCoreApplication::translate("MainWindow", "Welcome Page", nullptr));
        actionReadReport->setText(QCoreApplication::translate("MainWindow", "Read report", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuMode->setTitle(QCoreApplication::translate("MainWindow", "Mode", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("MainWindow", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpenFile;
    QAction *actionExit;
    QAction *actionHelp;
    QAction *actionSave;
    QAction *actionRun;
    QAction *actionSequencial;
    QAction *actionConcorrente;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *OriginalImage;
    QLabel *ResultImage;
    QHBoxLayout *horizontalLayout_2;
    QLabel *GrayScaleImage;
    QVBoxLayout *verticalLayout_2;
    QLabel *Histogram;
    QSlider *thresholdingInput;
    QLabel *BinaryImage;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuModo;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(725, 631);
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
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName("actionHelp");
        actionHelp->setIcon(icon);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icons/filesave.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName("actionRun");
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart));
        actionRun->setIcon(icon3);
        actionRun->setMenuRole(QAction::MenuRole::NoRole);
        actionSequencial = new QAction(MainWindow);
        actionSequencial->setObjectName("actionSequencial");
        actionSequencial->setCheckable(true);
        actionSequencial->setChecked(true);
        actionConcorrente = new QAction(MainWindow);
        actionConcorrente->setObjectName("actionConcorrente");
        actionConcorrente->setCheckable(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        OriginalImage = new QLabel(centralwidget);
        OriginalImage->setObjectName("OriginalImage");

        horizontalLayout->addWidget(OriginalImage);

        ResultImage = new QLabel(centralwidget);
        ResultImage->setObjectName("ResultImage");

        horizontalLayout->addWidget(ResultImage);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        GrayScaleImage = new QLabel(centralwidget);
        GrayScaleImage->setObjectName("GrayScaleImage");

        horizontalLayout_2->addWidget(GrayScaleImage);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        Histogram = new QLabel(centralwidget);
        Histogram->setObjectName("Histogram");

        verticalLayout_2->addWidget(Histogram);

        thresholdingInput = new QSlider(centralwidget);
        thresholdingInput->setObjectName("thresholdingInput");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(thresholdingInput->sizePolicy().hasHeightForWidth());
        thresholdingInput->setSizePolicy(sizePolicy);
        thresholdingInput->setOrientation(Qt::Orientation::Horizontal);

        verticalLayout_2->addWidget(thresholdingInput);


        horizontalLayout_2->addLayout(verticalLayout_2);

        BinaryImage = new QLabel(centralwidget);
        BinaryImage->setObjectName("BinaryImage");

        horizontalLayout_2->addWidget(BinaryImage);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 725, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuModo = new QMenu(menubar);
        menuModo->setObjectName("menuModo");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        toolBar->setMovable(false);
        toolBar->setOrientation(Qt::Orientation::Horizontal);
        toolBar->setIconSize(QSize(22, 22));
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuModo->menuAction());
        menuFile->addAction(actionRun);
        menuFile->addAction(actionOpenFile);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionHelp);
        menuFile->addAction(actionExit);
        menuModo->addAction(actionSequencial);
        menuModo->addAction(actionConcorrente);
        toolBar->addAction(actionRun);
        toolBar->addAction(actionOpenFile);
        toolBar->addAction(actionSave);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Segmenta\303\247\303\243o de Imagem por Thresholding", nullptr));
        actionOpenFile->setText(QCoreApplication::translate("MainWindow", "Open File...", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionHelp->setText(QCoreApplication::translate("MainWindow", "Help", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionRun->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
#if QT_CONFIG(tooltip)
        actionRun->setToolTip(QCoreApplication::translate("MainWindow", "Executa o algoritmo na imagem selecionada", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSequencial->setText(QCoreApplication::translate("MainWindow", "Sequencial", nullptr));
        actionConcorrente->setText(QCoreApplication::translate("MainWindow", "Concorrente", nullptr));
        OriginalImage->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        ResultImage->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        GrayScaleImage->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        Histogram->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        BinaryImage->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuModo->setTitle(QCoreApplication::translate("MainWindow", "Modo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'SolverPage.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOLVERPAGE_H
#define UI_SOLVERPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SolverPage
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *runBtn;
    QPushButton *openFileBtn;
    QPushButton *saveFileBtn;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *OriginalImage;
    QLabel *ResultImage;
    QHBoxLayout *horizontalLayout_2;
    QLabel *GrayScaleImage;
    QVBoxLayout *verticalLayout_2;
    QLabel *Histogram;
    QSlider *thresholdingInput;
    QLabel *BinaryImage;

    void setupUi(QWidget *SolverPage)
    {
        if (SolverPage->objectName().isEmpty())
            SolverPage->setObjectName("SolverPage");
        SolverPage->resize(725, 631);
        verticalLayout = new QVBoxLayout(SolverPage);
        verticalLayout->setSpacing(9);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(-1, 0, -1, -1);
        widget = new QWidget(SolverPage);
        widget->setObjectName("widget");
        widget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        runBtn = new QPushButton(widget);
        runBtn->setObjectName("runBtn");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(runBtn->sizePolicy().hasHeightForWidth());
        runBtn->setSizePolicy(sizePolicy1);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart));
        runBtn->setIcon(icon);
        runBtn->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(runBtn);

        openFileBtn = new QPushButton(widget);
        openFileBtn->setObjectName("openFileBtn");
        sizePolicy1.setHeightForWidth(openFileBtn->sizePolicy().hasHeightForWidth());
        openFileBtn->setSizePolicy(sizePolicy1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icons/fileopen.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        openFileBtn->setIcon(icon1);
        openFileBtn->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(openFileBtn);

        saveFileBtn = new QPushButton(widget);
        saveFileBtn->setObjectName("saveFileBtn");
        sizePolicy1.setHeightForWidth(saveFileBtn->sizePolicy().hasHeightForWidth());
        saveFileBtn->setSizePolicy(sizePolicy1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icons/filesave.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        saveFileBtn->setIcon(icon2);
        saveFileBtn->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(saveFileBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addWidget(widget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        OriginalImage = new QLabel(SolverPage);
        OriginalImage->setObjectName("OriginalImage");
        OriginalImage->setStyleSheet(QString::fromUtf8("border: 1px solid rgb(0, 0, 0);"));
        OriginalImage->setFrameShadow(QFrame::Shadow::Raised);

        horizontalLayout->addWidget(OriginalImage);

        ResultImage = new QLabel(SolverPage);
        ResultImage->setObjectName("ResultImage");
        ResultImage->setStyleSheet(QString::fromUtf8("border: 1px solid black;"));

        horizontalLayout->addWidget(ResultImage);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        GrayScaleImage = new QLabel(SolverPage);
        GrayScaleImage->setObjectName("GrayScaleImage");
        GrayScaleImage->setStyleSheet(QString::fromUtf8("border: 1px solid black;"));

        horizontalLayout_2->addWidget(GrayScaleImage);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        Histogram = new QLabel(SolverPage);
        Histogram->setObjectName("Histogram");
        Histogram->setStyleSheet(QString::fromUtf8("border: 1px solid black;"));

        verticalLayout_2->addWidget(Histogram);

        thresholdingInput = new QSlider(SolverPage);
        thresholdingInput->setObjectName("thresholdingInput");
        sizePolicy.setHeightForWidth(thresholdingInput->sizePolicy().hasHeightForWidth());
        thresholdingInput->setSizePolicy(sizePolicy);
        thresholdingInput->setMaximum(255);
        thresholdingInput->setValue(100);
        thresholdingInput->setOrientation(Qt::Orientation::Horizontal);

        verticalLayout_2->addWidget(thresholdingInput);


        horizontalLayout_2->addLayout(verticalLayout_2);

        BinaryImage = new QLabel(SolverPage);
        BinaryImage->setObjectName("BinaryImage");
        BinaryImage->setStyleSheet(QString::fromUtf8("border: 1px solid black;"));

        horizontalLayout_2->addWidget(BinaryImage);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(SolverPage);

        QMetaObject::connectSlotsByName(SolverPage);
    } // setupUi

    void retranslateUi(QWidget *SolverPage)
    {
        SolverPage->setWindowTitle(QCoreApplication::translate("SolverPage", "Form", nullptr));
#if QT_CONFIG(tooltip)
        runBtn->setToolTip(QCoreApplication::translate("SolverPage", "Run solver", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        openFileBtn->setToolTip(QCoreApplication::translate("SolverPage", "Select file", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        saveFileBtn->setToolTip(QCoreApplication::translate("SolverPage", "Save result", nullptr));
#endif // QT_CONFIG(tooltip)
        OriginalImage->setText(QString());
        ResultImage->setText(QString());
        GrayScaleImage->setText(QString());
        Histogram->setText(QString());
        BinaryImage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SolverPage: public Ui_SolverPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOLVERPAGE_H

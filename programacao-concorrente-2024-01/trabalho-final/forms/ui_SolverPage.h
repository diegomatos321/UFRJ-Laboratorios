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
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SolverPage
{
public:
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

    void setupUi(QWidget *SolverPage)
    {
        if (SolverPage->objectName().isEmpty())
            SolverPage->setObjectName("SolverPage");
        SolverPage->resize(725, 631);
        verticalLayout = new QVBoxLayout(SolverPage);
        verticalLayout->setObjectName("verticalLayout");
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
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(thresholdingInput->sizePolicy().hasHeightForWidth());
        thresholdingInput->setSizePolicy(sizePolicy);
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

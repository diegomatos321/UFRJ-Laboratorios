/********************************************************************************
** Form generated from reading UI file 'WelcomePage.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOMEPAGE_H
#define UI_WELCOMEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WelcomePage
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *PageHeader;
    QVBoxLayout *verticalLayout_5;
    QLabel *title;
    QLabel *description;
    QHBoxLayout *horizontalLayout;
    QWidget *col1;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label;
    QLabel *label_10;
    QWidget *col2;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_11;
    QPushButton *newProjectBtn;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_8;
    QLabel *label_9;

    void setupUi(QWidget *WelcomePage)
    {
        if (WelcomePage->objectName().isEmpty())
            WelcomePage->setObjectName("WelcomePage");
        WelcomePage->resize(700, 600);
        verticalLayout = new QVBoxLayout(WelcomePage);
        verticalLayout->setObjectName("verticalLayout");
        PageHeader = new QWidget(WelcomePage);
        PageHeader->setObjectName("PageHeader");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PageHeader->sizePolicy().hasHeightForWidth());
        PageHeader->setSizePolicy(sizePolicy);
        verticalLayout_5 = new QVBoxLayout(PageHeader);
        verticalLayout_5->setObjectName("verticalLayout_5");
        title = new QLabel(PageHeader);
        title->setObjectName("title");
        QFont font;
        font.setPointSize(24);
        font.setBold(true);
        title->setFont(font);
        title->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        verticalLayout_5->addWidget(title);

        description = new QLabel(PageHeader);
        description->setObjectName("description");
        description->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        verticalLayout_5->addWidget(description);


        verticalLayout->addWidget(PageHeader);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        col1 = new QWidget(WelcomePage);
        col1->setObjectName("col1");
        verticalLayout_3 = new QVBoxLayout(col1);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_4 = new QLabel(col1);
        label_4->setObjectName("label_4");
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        label_4->setFont(font1);
        label_4->setScaledContents(false);
        label_4->setWordWrap(true);

        verticalLayout_3->addWidget(label_4);

        label_6 = new QLabel(col1);
        label_6->setObjectName("label_6");
        QFont font2;
        font2.setPointSize(12);
        label_6->setFont(font2);
        label_6->setScaledContents(false);
        label_6->setWordWrap(true);

        verticalLayout_3->addWidget(label_6);

        label_7 = new QLabel(col1);
        label_7->setObjectName("label_7");
        label_7->setFont(font1);
        label_7->setScaledContents(false);
        label_7->setWordWrap(true);

        verticalLayout_3->addWidget(label_7);

        label = new QLabel(col1);
        label->setObjectName("label");
        label->setFont(font2);
        label->setScaledContents(false);
        label->setWordWrap(true);

        verticalLayout_3->addWidget(label);

        label_10 = new QLabel(col1);
        label_10->setObjectName("label_10");
        label_10->setFont(font2);
        label_10->setScaledContents(false);
        label_10->setWordWrap(true);

        verticalLayout_3->addWidget(label_10);


        horizontalLayout->addWidget(col1);

        col2 = new QWidget(WelcomePage);
        col2->setObjectName("col2");
        verticalLayout_4 = new QVBoxLayout(col2);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        label_11 = new QLabel(col2);
        label_11->setObjectName("label_11");
        label_11->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_11->setWordWrap(true);

        verticalLayout_4->addWidget(label_11);

        newProjectBtn = new QPushButton(col2);
        newProjectBtn->setObjectName("newProjectBtn");

        verticalLayout_4->addWidget(newProjectBtn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        label_2 = new QLabel(col2);
        label_2->setObjectName("label_2");
        label_2->setWordWrap(true);

        verticalLayout_4->addWidget(label_2);

        label_5 = new QLabel(col2);
        label_5->setObjectName("label_5");
        label_5->setWordWrap(true);

        verticalLayout_4->addWidget(label_5);

        label_3 = new QLabel(col2);
        label_3->setObjectName("label_3");
        label_3->setWordWrap(true);

        verticalLayout_4->addWidget(label_3);

        label_8 = new QLabel(col2);
        label_8->setObjectName("label_8");
        label_8->setWordWrap(true);

        verticalLayout_4->addWidget(label_8);

        label_9 = new QLabel(col2);
        label_9->setObjectName("label_9");
        label_9->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_9->setWordWrap(true);

        verticalLayout_4->addWidget(label_9);


        horizontalLayout->addWidget(col2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(WelcomePage);

        QMetaObject::connectSlotsByName(WelcomePage);
    } // setupUi

    void retranslateUi(QWidget *WelcomePage)
    {
        WelcomePage->setWindowTitle(QCoreApplication::translate("WelcomePage", "Form", nullptr));
        title->setText(QCoreApplication::translate("WelcomePage", "Image Segmentation Tool", nullptr));
        description->setText(QCoreApplication::translate("WelcomePage", "Simplifying Image Proccessing with Thresholding", nullptr));
        label_4->setText(QCoreApplication::translate("WelcomePage", "Welcome to the Image Segmentation Tool!", nullptr));
        label_6->setText(QCoreApplication::translate("WelcomePage", "<html><head/><body><p>This project allows users to easily apply thresholding method to segment images. Through an intuitive interface, users can load images, apply mas filter, and save results. </p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("WelcomePage", "Project Summary", nullptr));
        label->setText(QCoreApplication::translate("WelcomePage", "<html><head/><body><p>Thresholding is a type of image segmentation, where we change the pixels of an image to make the image easier to analyze and can chain it to some other method, as a preprocessor, to improve its results. In thresholding, we convert an image from colour or grayscale into a binary image, i.e., one that is simply black and white, and use the binary image for something else. </p></body></html>", nullptr));
        label_10->setText(QCoreApplication::translate("WelcomePage", "In this application we apply the binary image as a mask to the original image pottencially removing unwanted elements in the image.", nullptr));
        label_11->setText(QCoreApplication::translate("WelcomePage", "<html><head/><body><p>This is a educative project developed for Concurrency Programming Major at UFRJ, it's main feature is to apply concurrency at the Thresholding method.</p></body></html>", nullptr));
        newProjectBtn->setText(QCoreApplication::translate("WelcomePage", "Start new Project", nullptr));
        label_2->setText(QCoreApplication::translate("WelcomePage", "Created by: Diego V. S. de Matos", nullptr));
        label_5->setText(QCoreApplication::translate("WelcomePage", "<html><head/><body><p>Github: <a href=\"https://github.com/diegomatos321\"><span style=\" text-decoration: underline; color:#0078d7;\">https://github.com/diegomatos321</span></a></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("WelcomePage", "<html><head/><body><p>Linkedin: <a href=\"https://www.linkedin.com/in/dev-diego-matos/\"><span style=\" text-decoration: underline; color:#0078d7;\">https://www.linkedin.com/in/dev-diego-matos/</span></a></p></body></html>", nullptr));
        label_8->setText(QCoreApplication::translate("WelcomePage", "<html><head/><body><p>Website: <a href=\"https://www.devdiegomatos.com.br/\"><span style=\" text-decoration: underline; color:#0078d7;\">https://www.devdiegomatos.com.br/</span></a></p></body></html>", nullptr));
        label_9->setText(QCoreApplication::translate("WelcomePage", "Made with Qt6", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WelcomePage: public Ui_WelcomePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOMEPAGE_H

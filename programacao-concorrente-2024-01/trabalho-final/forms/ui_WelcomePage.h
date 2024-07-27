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
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WelcomePage
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *PageHeader;
    QVBoxLayout *verticalLayout_2;
    QLabel *title;
    QLabel *description;
    QWidget *PageContent;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label;
    QLabel *label_10;
    QPushButton *newProjectBtn;
    QFrame *line;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_11;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_8;
    QLabel *label_9;

    void setupUi(QWidget *WelcomePage)
    {
        if (WelcomePage->objectName().isEmpty())
            WelcomePage->setObjectName("WelcomePage");
        WelcomePage->resize(620, 550);
        verticalLayout = new QVBoxLayout(WelcomePage);
        verticalLayout->setObjectName("verticalLayout");
        PageHeader = new QWidget(WelcomePage);
        PageHeader->setObjectName("PageHeader");
        verticalLayout_2 = new QVBoxLayout(PageHeader);
        verticalLayout_2->setObjectName("verticalLayout_2");
        title = new QLabel(PageHeader);
        title->setObjectName("title");
        QFont font;
        font.setFamilies({QString::fromUtf8("Times New Roman")});
        font.setPointSize(24);
        font.setBold(true);
        title->setFont(font);
        title->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        verticalLayout_2->addWidget(title);

        description = new QLabel(PageHeader);
        description->setObjectName("description");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Times New Roman")});
        description->setFont(font1);
        description->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        verticalLayout_2->addWidget(description);


        verticalLayout->addWidget(PageHeader);

        PageContent = new QWidget(WelcomePage);
        PageContent->setObjectName("PageContent");
        verticalLayout_3 = new QVBoxLayout(PageContent);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_4 = new QLabel(PageContent);
        label_4->setObjectName("label_4");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Times New Roman")});
        font2.setPointSize(18);
        label_4->setFont(font2);

        verticalLayout_3->addWidget(label_4);

        label_6 = new QLabel(PageContent);
        label_6->setObjectName("label_6");
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Times New Roman")});
        font3.setPointSize(12);
        label_6->setFont(font3);
        label_6->setWordWrap(true);

        verticalLayout_3->addWidget(label_6);

        label_7 = new QLabel(PageContent);
        label_7->setObjectName("label_7");
        QFont font4;
        font4.setPointSize(18);
        label_7->setFont(font4);

        verticalLayout_3->addWidget(label_7);

        label = new QLabel(PageContent);
        label->setObjectName("label");
        label->setFont(font3);
        label->setWordWrap(true);

        verticalLayout_3->addWidget(label);

        label_10 = new QLabel(PageContent);
        label_10->setObjectName("label_10");
        label_10->setFont(font3);
        label_10->setWordWrap(true);

        verticalLayout_3->addWidget(label_10);

        newProjectBtn = new QPushButton(PageContent);
        newProjectBtn->setObjectName("newProjectBtn");

        verticalLayout_3->addWidget(newProjectBtn);


        verticalLayout->addWidget(PageContent);

        line = new QFrame(WelcomePage);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);

        widget = new QWidget(WelcomePage);
        widget->setObjectName("widget");
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_11 = new QLabel(widget);
        label_11->setObjectName("label_11");
        label_11->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_11->setWordWrap(true);

        verticalLayout_4->addWidget(label_11);

        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        verticalLayout_4->addWidget(label_2);

        label_5 = new QLabel(widget);
        label_5->setObjectName("label_5");

        verticalLayout_4->addWidget(label_5);

        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");

        verticalLayout_4->addWidget(label_3);

        label_8 = new QLabel(widget);
        label_8->setObjectName("label_8");

        verticalLayout_4->addWidget(label_8);

        label_9 = new QLabel(widget);
        label_9->setObjectName("label_9");
        label_9->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(label_9);


        verticalLayout->addWidget(widget);


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
        newProjectBtn->setText(QCoreApplication::translate("WelcomePage", "Start new Project", nullptr));
        label_11->setText(QCoreApplication::translate("WelcomePage", "<html><head/><body><p>This is a educative project developed for Concurrency Programming Major at UFRJ, it's main feature is to apply concurrency at the Thresholding method.</p></body></html>", nullptr));
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

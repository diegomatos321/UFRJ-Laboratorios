#include "../headers/WelcomePage.h"

WelcomePage::WelcomePage(QWidget *parent): QWidget(parent), ui(new Ui::WelcomePage) {
    this->ui->setupUi(this);

    QObject::connect(this->ui->newProjectBtn, &QPushButton::clicked, this, &WelcomePage::StartNewProject);
}

WelcomePage::~WelcomePage() {}

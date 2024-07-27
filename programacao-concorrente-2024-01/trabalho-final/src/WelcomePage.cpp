#include "../headers/WelcomePage.h"

WelcomePage::WelcomePage(QWidget *parent): QWidget(parent), ui(new Ui::WelcomePage) {
    this->ui->setupUi(this);

    QObject::connect(this->ui->newProjectBtn, &QPushButton::clicked, this, &WelcomePage::HandleNewProjectBtnClicked);
}

WelcomePage::~WelcomePage() {}

void WelcomePage::HandleNewProjectBtnClicked() {
    emit this->StartNewProject();
}

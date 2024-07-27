#include "../headers/WelcomePage.h"

WelcomePage::WelcomePage(QWidget *parent): QWidget(parent), ui(new Ui::WelcomePage) {
    this->ui->setupUi(this);
}

WelcomePage::~WelcomePage() {}
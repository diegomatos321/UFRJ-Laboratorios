#include "../headers/Application.h"

Application::Application(QWidget *parent): QMainWindow(parent), ui(new Ui::Application) {
    this->ui->setupUi(this);

    this->welcomePage = new WelcomePage();

    int index = this->ui->stackedWidget->addWidget(this->welcomePage);
    this->ui->stackedWidget->setCurrentIndex(1);
}

Application::~Application() {}

#include "../headers/MainWindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    this->ui->setupUi(this);

    this->welcomePage = new WelcomePage();

    int index = this->ui->stackedWidget->addWidget(this->welcomePage);
    this->ui->stackedWidget->setCurrentIndex(1);
}

MainWindow::~MainWindow() {}

#include "../headers/MainWindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    this->ui->setupUi(this);

    this->welcomePage = new WelcomePage();
    this->solverPage = new SolverPage();

    this->ui->stackedWidget->addWidget(this->welcomePage);
    this->ui->stackedWidget->addWidget(this->solverPage);
    this->ui->stackedWidget->setCurrentWidget(this->welcomePage);

    QObject::connect(this->welcomePage, &WelcomePage::StartNewProject, this, &MainWindow::OnStartNewProjectSignal);
}

MainWindow::~MainWindow() { }

void MainWindow::OnStartNewProjectSignal() {
    this->ui->stackedWidget->setCurrentWidget(this->solverPage);
}

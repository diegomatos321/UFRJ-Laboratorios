#include "../headers/MainWindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    this->ui->setupUi(this);

    QActionGroup *executionMode = new QActionGroup(this);
    executionMode->addAction(this->ui->actionSequentialMode);
    executionMode->addAction(this->ui->actionConcurrentMode);

    this->welcomePage = new WelcomePage();
    this->solverPage = new SolverPage();

    this->ui->stackedWidget->addWidget(this->welcomePage);
    this->ui->stackedWidget->addWidget(this->solverPage);

    QObject::connect(this->welcomePage, &WelcomePage::StartNewProject, this, &MainWindow::OnStartNewProjectSignal);
    QObject::connect(this->ui->actionNewProject, &QAction::triggered, this, &MainWindow::OnStartNewProjectSignal);
    QObject::connect(this->ui->actionExit, &QAction::triggered, this, &QApplication::quit);
    QObject::connect(this->ui->actionRun, &QAction::triggered, this->solverPage, &SolverPage::slotRun);
    QObject::connect(this->ui->actionSelectFile, &QAction::triggered, this->solverPage, &SolverPage::slotOpenFile);
    QObject::connect(this->ui->actionSaveResult, &QAction::triggered, this->solverPage, &SolverPage::slotSaveResultImage);
    QObject::connect(this->ui->actionWelcomePage, &QAction::triggered, this, &MainWindow::OnWelcomePageSignal);
    
    // QObject::connect(this->ui->actionHelp, &QAction::triggered, this, &SolverPage::slotOpenReport);
    QObject::connect(this->ui->actionSequentialMode, &QAction::triggered, this->solverPage, &SolverPage::slotSetSequencialAlgorithm);
    QObject::connect(this->ui->actionConcurrentMode, &QAction::triggered, this->solverPage, &SolverPage::slotSetConcorrentAlgorithm);
}

MainWindow::~MainWindow() { }

void MainWindow::OnStartNewProjectSignal() {
    this->ui->stackedWidget->setCurrentWidget(this->solverPage);
}

void MainWindow::OnWelcomePageSignal() {
    this->ui->stackedWidget->setCurrentWidget(this->welcomePage);
}

#ifndef MainWindow_H
#define MainWindow_H

#include "../forms/ui_MainWindow.h"
#include "../headers/WelcomePage.h"
#include "../headers/SolverPage.h"
#include <QtWidgets/QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    Ui::MainWindow* ui;

    WelcomePage* welcomePage;
    SolverPage* solverPage;

protected slots:
    void OnStartNewProjectSignal();
    void OnWelcomePageSignal();
};

#endif

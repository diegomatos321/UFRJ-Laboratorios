#ifndef Application_H
#define Application_H

#include "../forms/ui_Application.h"
#include "../headers/WelcomePage.h"
#include <QtWidgets/QMainWindow>

class Application : public QMainWindow {
    Q_OBJECT

public:
    Application(QWidget *parent = nullptr);
    ~Application() override;

protected:
    Ui::Application* ui;

    WelcomePage* welcomePage;
};

#endif

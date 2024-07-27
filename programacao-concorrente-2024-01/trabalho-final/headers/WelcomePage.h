#ifndef WelcomePage_H
#define WelcomePage_H

#include "../forms/ui_WelcomePage.h"
#include <QtWidgets/QWidget>

class WelcomePage : public QWidget {
    Q_OBJECT

public:
    WelcomePage(QWidget *parent = nullptr);
    ~WelcomePage() override;

protected:
    Ui::WelcomePage* ui;
};

#endif

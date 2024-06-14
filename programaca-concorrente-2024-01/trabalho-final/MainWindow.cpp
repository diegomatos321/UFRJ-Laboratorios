#include <QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent), ui(new Ui::MainWindow) {
        ui->setupUi(this);
    }

    ~MainWindow() {
        delete ui;
    }

private:
    Ui::MainWindow *ui;
};

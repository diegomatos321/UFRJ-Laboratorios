#include <QMainWindow>
#include "ui_mainwindow.h"  // Inclua o arquivo gerado

class MainWindow : public QMainWindow {

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

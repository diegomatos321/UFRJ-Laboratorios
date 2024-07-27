#include <QApplication>
#include "../headers/Application.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    Application main;
    main.show();

    return app.exec();
}
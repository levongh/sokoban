#include <QApplication>

#include "sokoban.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Settings::getInstance();
    Sokoban app;
    app.setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    app.setFixedSize(800, 600);
    app.show();

    return a.exec();
}

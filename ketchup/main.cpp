#include "ketchupmain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(ketchup);
    QApplication app(argc, argv);
    app.setOrganizationName("zokier");
    app.setOrganizationDomain("zokier.net");
    app.setApplicationName("Ketchup");
    app.setQuitOnLastWindowClosed(false);
    KetchupMain w;
    QObject::connect(&w, &KetchupMain::quit, &app, &QApplication::quit);

    return app.exec();
}

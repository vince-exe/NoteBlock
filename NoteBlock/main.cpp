#include "main_dialog.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainDialog w;
    w.show();

    qDebug() << "App path : " << qApp->applicationDirPath();

    return w.exec();
}

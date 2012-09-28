#include <QtGui/QApplication>
#include <QSettings>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setApplicationName("prism");
    QApplication::setOrganizationName("aarg");
    QApplication::setOrganizationDomain("aarg.eu");

    QSettings::setDefaultFormat(QSettings::IniFormat);

    // set some default settings

    QSettings s;

    if (!s.contains("path/data"))
    {
        const QString &app_path = QApplication::applicationDirPath();

        s.setValue("path/data", app_path);
        s.setValue("path/gfx", app_path + "/data/gfx");
        s.setValue("path/levels", app_path + "/data/levels");
    }

    MainWindow mw;
    mw.show();

    return a.exec();
}

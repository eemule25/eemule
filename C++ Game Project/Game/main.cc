#include <QApplication>
#include "engine.hh"
#include <QObject>

int main(int argc, char *argv[])
{
    int CurrentExitCode = 0;

    do {
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);

    StudentSide::Engine engine;

    CurrentExitCode = a.exec();
    } while (CurrentExitCode == StudentSide::MainWindow::EXIT_CODE_REBOOT);

    return CurrentExitCode;
}

#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mw;
    LoginDialog ld;

    if (ld.exec() == QDialog::Accepted) { mw.show(); app.exec(); }
    else { app.quit(); }

    return 0;
}

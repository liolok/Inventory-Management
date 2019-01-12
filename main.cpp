#include "const.h"
#include "logindialog.h"
#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase(DB_TYPE);
    db.setDatabaseName(DB_PATH);
    if (!db.open())
    {
        qDebug() << "Fails opening database:" << db.lastError();
        return -1;
    }

    QApplication app(argc, argv);
    LoginDialog ld;

    if (ld.exec() == QDialog::Accepted)
    {
        MainWindow mw;
        mw.show();
        app.exec();
    }
    else app.quit();

    db.close();
    return 0;
}

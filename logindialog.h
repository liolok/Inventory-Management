#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "const.h"
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>

namespace Ui {
    class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;
    QLineEdit *lineEditUsername;
    QLineEdit *lineEditPassword;
    QPushButton *loginButton;

    QSqlDatabase db;
    QSqlQuery query;

private slots:
    void on_loginButton_clicked();
};

#endif // LOGINDIALOG_H

#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "const.h"
#include <QDialog>
#include <QSqlQuery>

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
    QSqlQuery *qry;

private slots:
    void on_loginButton_clicked();
};

#endif // LOGINDIALOG_H

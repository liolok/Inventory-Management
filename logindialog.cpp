#include "logindialog.h"
#include "ui_logindialog.h"
#include <QtDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    qry(new QSqlQuery)
{
    qDebug() << "[Login Dialog] Constructing...";
    ui->setupUi(this);
    ui->lineEditUsername->setMaxLength(USERNAME_MAX_LEN);
    ui->lineEditPassword->setMaxLength(PASSWORD_MAX_LEN);

    // If no user table yet, create it.
    QString s = "CREATE TABLE IF NOT EXISTS Users ("
        "name char(%1) PRIMARY KEY, pswd char(%2))";
    QString create_user_table = s.arg(
        QString::number(USERNAME_MAX_LEN), QString::number(PASSWORD_MAX_LEN));
    qDebug() << create_user_table << qry->exec(create_user_table);
    // WONTDO: visual feedback, like initial message box.

    // If no user yet, add a default one to login.
    QString count_users = "SELECT COUNT(*) FROM Users";
    qDebug() << count_users << qry->exec(count_users);
    if (qry->first() && !qry->value(0).toInt())
    {
        QString s = "INSERT INTO Users VALUES ('%1', '%2')";
        QString add_default_user = s.arg(DEFAULT_USERNAME, DEFAULT_PASSWORD);
        qDebug() << add_default_user << qry->exec(add_default_user);
    }
}

LoginDialog::~LoginDialog()
{
    qDebug() << "[Login Dialog] Destructing...";
    delete ui;
    delete qry;
}

void LoginDialog::on_loginButton_clicked()
{
    qDebug() << "[Login Button] Clicked...";
    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();

    // Validate input user info against user table in database
    QString s = "SELECT COUNT(*) FROM Users WHERE name='%1' AND pswd='%2'";
    QString validate_user = s.arg(username, password);
    qDebug() << validate_user << qry->exec(validate_user);
    if (qry->first() && qry->value(0).toInt()) accept();
    // WONTDO: Exceoption when input user info incorrect
}

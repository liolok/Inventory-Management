#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    qry(new QSqlQuery)
{
    qDebug() << "[Login Dialog] Constructing...";
    ui->setupUi(this);
    ui->lineEditUsername->setMaxLength(USERNAME_MAX_LEN);
    ui->lineEditPassword->setMaxLength(PASSWORD_MAX_LEN);

    // If user table doesn't exist yet, create it.
    QString create_user_table = "CREATE TABLE IF NOT EXISTS Users ("
        "name char(name_len) PRIMARY KEY, pswd char(pswd_len))";
    create_user_table.replace("name_len", QString::number(USERNAME_MAX_LEN));
    create_user_table.replace("pswd_len", QString::number(PASSWORD_MAX_LEN));
    qDebug() << create_user_table << qry->exec(create_user_table);

    // If there's no user yet, insert a default one.
    QString count_users = "SELECT COUNT(*) FROM Users";
    qDebug() << count_users << qry->exec(count_users);
    if (qry->first() && !qry->value(0).toInt())
    {
        QString insert_default_user = "INSERT INTO Users VALUES (name, pswd)";
        insert_default_user.replace("name", DEFAULT_USERNAME);
        insert_default_user.replace("pswd", DEFAULT_PASSWORD);
        qDebug() << insert_default_user << qry->exec();
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
    QString validate_user = "SELECT COUNT(*) FROM Users "
        "WHERE name = 'username' AND pswd = 'password'";
    validate_user.replace("username", username);
    validate_user.replace("password", password);
    qDebug() << validate_user << qry->exec(validate_user);
    if (qry->first() && qry->value(0).toInt()) accept();
    // WONTDO: Exceoption when input user info incorrect
}

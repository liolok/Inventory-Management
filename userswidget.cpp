#include "userswidget.h"
#include "ui_userswidget.h"
#include <QtDebug>

UsersWidget::UsersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UsersWidget),
    qry(new QSqlQuery)
{
    qDebug() << "[Users Widget] Constructing...";
    ui->setupUi(this);
    ui->lineEditUsername->setMaxLength(USERNAME_MAX_LEN);
    ui->lineEditPassword->setMaxLength(PASSWORD_MAX_LEN);
    ui->lineEditPasswordConfirm->setMaxLength(PASSWORD_MAX_LEN);

    refreshUserList();
}

UsersWidget::~UsersWidget()
{
    qDebug() << "[Users Widget] Destructing...";
    delete ui;
    delete qry;
}

void UsersWidget::on_addUserButton_clicked()
{
    qDebug() << "[Users Widget] Clicked add user button...";
    QString name = ui->lineEditUsername->text();
    QString pswd = ui->lineEditPassword->text();
    QString pswdConfirm = ui->lineEditPasswordConfirm->text();

    if (!(name.length() && pswd.length() && pswdConfirm.length())
        || (pswd != pswdConfirm))
    {
        qDebug() << "Field no input or password not confirmed, won't add user.";
        return; // WONTDO: visual feedback, like lineEdit border get red.
    }

    QString s = "INSERT INTO Users VALUES ('%1', '%2')";
    QString add_user = s.arg(name, pswd);
    bool success = qry->exec(add_user);
    qDebug() << add_user << success;
    if (success) refreshUserList();
}

void UsersWidget::refreshUserList()
{
    qDebug() << "Refreshing user list...";
    QString get_all_username = "SELECT name FROM Users";
    qDebug() << get_all_username << qry->exec(get_all_username);
    ui->userList->clear();
    while (qry->next()) { ui->userList->addItem(qry->value(0).toString()); }
}

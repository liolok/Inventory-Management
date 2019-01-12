#ifndef USERSWIDGET_H
#define USERSWIDGET_H

#include "const.h"
#include <QWidget>
#include <QSqlQuery>

namespace Ui {
    class UsersWidget;
}

class UsersWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UsersWidget(QWidget *parent = nullptr);
    ~UsersWidget();

private:
    Ui::UsersWidget *ui;
    QSqlQuery *qry;
    void refreshUserList();

private slots:
    void on_addUserButton_clicked();
};

#endif // USERSWIDGET_H

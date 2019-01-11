#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "inventorywidget.h"
#include "inboundwidget.h"
#include "userswidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    InventoryWidget *inventory;
    InboundWidget *inbound;
    UsersWidget *users;
};

#endif // MAINWINDOW_H

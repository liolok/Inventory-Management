#ifndef INVENTORYWIDGET_H
#define INVENTORYWIDGET_H

#include "const.h"
#include <QWidget>
#include <QSqlTableModel>
#include <QSqlQueryModel>

namespace Ui {
    class InventoryWidget;
}

class InventoryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InventoryWidget(QWidget *parent = nullptr);
    ~InventoryWidget();

private:
    Ui::InventoryWidget *ui;
    QSqlQuery *qry;
    QSqlQueryModel *model;
    void refreshInventoryTable();

signals:

private slots:
    void on_inboundButton_clicked();
    void on_outboundButton_clicked();
};

#endif // INVENTORYWIDGET_H

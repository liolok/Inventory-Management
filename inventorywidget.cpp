#include "inventorywidget.h"
#include "ui_inventorywidget.h"
#include <QtDebug>

InventoryWidget::InventoryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InventoryWidget),
    qry(new QSqlQuery),
    model(new QSqlQueryModel)
{
    qDebug() << "[Inventory Widget] Constructing...";
    ui->setupUi(this);
    ui->lineEditInName->setMaxLength(ITEMNAME_MAX_LEN);
    ui->lineEditInCategory->setMaxLength(CATEGORY_MAX_LEN);
    ui->spinBoxInAmount->setMaximum(INVENTORY_IO_MAX);
    ui->lineEditOutName->setMaxLength(ITEMNAME_MAX_LEN);
    ui->spinBoxOutAmount->setMaximum(INVENTORY_IO_MAX);
    ui->tableViewInventory->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::Stretch);

    // If no inventory table yet, create it.
    QString s = "CREATE TABLE IF NOT EXISTS Inventory ("
        "name char(%1) PRIMARY KEY, cate char(%2), amount int)";
    QString create_inventory_table = s.arg(
        QString::number(ITEMNAME_MAX_LEN), QString::number(CATEGORY_MAX_LEN));
    qDebug() << create_inventory_table << qry->exec(create_inventory_table);

    // If no inbound table yet, create it.
    s = "CREATE TABLE IF NOT EXISTS Inbound ("
        "name char(%1), cate char(%2), amount int, time char(20) PRIMARY KEY)";
    QString create_inbound_table = s.arg(
        QString::number(ITEMNAME_MAX_LEN), QString::number(CATEGORY_MAX_LEN));
    qDebug() << create_inbound_table << qry->exec(create_inbound_table);

    // If no outbound table yet, create it.
    s = "CREATE TABLE IF NOT EXISTS Outbound ("
        "name char(%1), cate char(%2), amount int, time char(20) PRIMARY KEY)";
    QString create_outbound_table = s.arg(
        QString::number(ITEMNAME_MAX_LEN), QString::number(CATEGORY_MAX_LEN));
    qDebug() << create_outbound_table << qry->exec(create_outbound_table);

    refreshInventoryTable();
}

InventoryWidget::~InventoryWidget()
{
    qDebug() << "[Inventory Widget] Destructing...";
    delete ui;
    delete qry;
    delete model;
}

void InventoryWidget::on_pushButtonInbound_clicked()
{
    qDebug() << "[Inventory Widget] Inbound button clicked...";
    QString name = ui->lineEditInName->text();
    QString cate = ui->lineEditInCategory->text();
    int increment = ui->spinBoxInAmount->value();

    if (!(name.length() && cate.length()))
    {
        qDebug() << "Field no input, won't inbound item.";
        return;
    }

    // Special Syntax Addition | NOT Standard SQL | SQLite >= 3.24.0
    // See: https://www.sqlite.org/lang_UPSERT.html
    QString s = "INSERT INTO Inventory VALUES('%1', '%2', %3) "
        "ON CONFLICT(name) DO UPDATE SET amount = amount + %3";
    QString inbound = s.arg(name, cate, QString::number(increment));
    bool success = qry->exec(inbound);
    qDebug() << inbound << success;
    if (success)
    {
        refreshInventoryTable();
        qDebug() << "Logging inbound...";
        QString s = "INSERT INTO Inbound VALUES("
            "'%1', '%2', %3, datetime('now', 'localtime'))";
        QString log_inbound = s.arg(name, cate, QString::number(increment));
        qDebug() << log_inbound << qry->exec(log_inbound);
        inbounded();
    }
}

void InventoryWidget::on_pushButtonOutbound_clicked()
{
    qDebug() << "[Inventory Widget] Outbound button clicked...";
    QString name = ui->lineEditOutName->text(), cate;
    int amount, decrement = ui->spinBoxOutAmount->value();

    // Get category and currnet amount of item.
    QString s = "SELECT cate, amount FROM Inventory WHERE name='%1'";
    QString get_item_info = s.arg(name);
    qDebug() << get_item_info << qry->exec(get_item_info);
    if (!qry->first()) { qDebug() << "Item not found."; return; }
    else { cate = qry->value(0).toString(); amount = qry->value(1).toInt(); }
    // Ensure amount would still be non-negtaive after outbound.
    if (amount < decrement) { qDebug() << "Amount not enough."; return; }

    s = "UPDATE Inventory SET amount = amount - %1 WHERE name = '%2'";
    QString outbound = s.arg(QString::number(decrement), name);
    bool success = qry->exec(outbound);
    qDebug() << outbound << success;
    if (success)
    {
        refreshInventoryTable();
        qDebug() << "Logging outbound...";
        s = "INSERT INTO Outbound VALUES("
            "'%1', '%2', %3, datetime('now', 'localtime'))";
        QString log_outbound = s.arg(name, cate, QString::number(decrement));
        qDebug() << log_outbound << qry->exec(log_outbound);
        outbounded();
    }
}

void InventoryWidget::refreshInventoryTable()
{
    qDebug() << "Refreshing inventory table...";
    QString s = "SELECT name AS %1, cate AS %2, amount AS %3 FROM Inventory";
    QString view_inventory = s.arg(tr("Name"), tr("Category"), tr("Amount"));
    model->setQuery(view_inventory);
    ui->tableViewInventory->setModel(model);
}

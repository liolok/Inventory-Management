#include "inventorywidget.h"
#include "ui_inventorywidget.h"

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

    // If no inventory table yet, create it.
    QString s = "CREATE TABLE IF NOT EXISTS Inventory ("
        "name char(%1) PRIMARY KEY, cate char(%2), amount int)";
    QString create_inventory_table = s.arg(
        QString::number(ITEMNAME_MAX_LEN), QString::number(CATEGORY_MAX_LEN));
    qDebug() << create_inventory_table << qry->exec(create_inventory_table);

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
        "ON CONFLICT(name) DO UPDATE SET amount=amount+%3";
    QString inbound = s.arg(name, cate, QString::number(increment));
    bool success = qry->exec(inbound);
    qDebug() << inbound << success;
    if (success) { refreshInventoryTable(); }
}

void InventoryWidget::on_pushButtonOutbound_clicked()
{
    qDebug() << "[Inventory Widget] Outbound button clicked...";
    QString name = ui->lineEditOutName->text();
    int amount, decrement = ui->spinBoxOutAmount->value();

    // Get currnet amount of item.
    QString s = "SELECT amount FROM Inventory WHERE name='%1'";
    QString get_amount = s.arg(name);
    qDebug() << get_amount << qry->exec(get_amount);
    if (qry->first()) { amount = qry->value(0).toInt(); }
    else { qDebug() << "Item not found, won't outbound."; return; }
    // Ensure amount would still be non-negtaive after outbound.
    if (amount < decrement)
    {
        qDebug() << "Item amount not enough, won't outbound.";
        return;
    }

    s = "UPDATE Inventory SET amount=amount-%1 WHERE name='%2'";
    QString outbound = s.arg(QString::number(decrement), name);
    bool success = qry->exec(outbound);
    qDebug() << outbound << success;
    if (success) { refreshInventoryTable(); }
}

void InventoryWidget::refreshInventoryTable()
{
    qDebug() << "Refreshing inventory table...";
    QString s = "SELECT name AS %1, cate AS %2, amount AS %3 FROM Inventory";
    QString view_inventory = s.arg(tr("Name"), tr("Category"), tr("Amount"));
    model->setQuery(view_inventory);
    ui->tableInventory->setModel(model);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    inventory(new InventoryWidget(this)),
    inbound(new InboundWidget(this)),
    outbound(new OutboundWidget(this)),
    users(new UsersWidget(this))
{
    qDebug() << "[Main Window] Constructing...";
    ui->setupUi(this);

    ui->tabWidget->addTab(inventory, tr("Inventory"));
    ui->tabWidget->addTab(inbound, tr("Inbound"));
    ui->tabWidget->addTab(outbound, tr("Outbound"));
    ui->tabWidget->addTab(users, tr("Users"));

    connect(inventory, &InventoryWidget::inbounded,
            inbound, &InboundWidget::refreshCategoryComboBox);
    connect(inventory, &InventoryWidget::inbounded,
            inbound, &InboundWidget::on_pushButtonQuery_clicked);

    connect(inventory, &InventoryWidget::outbounded,
            outbound, &OutboundWidget::refreshCategoryComboBox);
    connect(inventory, &InventoryWidget::outbounded,
            outbound, &OutboundWidget::on_pushButtonQuery_clicked);
}

MainWindow::~MainWindow()
{
    qDebug() << "[Main Window] Destructing...";
    delete ui;
    delete inventory;
    delete inbound;
    delete outbound;
    delete users;
}

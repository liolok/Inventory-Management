#ifndef OUTBOUNDWIDGET_H
#define OUTBOUNDWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
    class OutboundWidget;
}

class OutboundWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OutboundWidget(QWidget *parent = nullptr);
    ~OutboundWidget();

private:
    Ui::OutboundWidget *ui;
    QSqlQuery *qry;
    QSqlQueryModel *modelOutbound;
    QSqlQueryModel *modelCategory;
    void refreshOutboundTableView(const QString& qry_clause = "");

public slots:
    void refreshCategoryComboBox();
    void on_pushButtonQuery_clicked();
};

#endif // OUTBOUNDWIDGET_H
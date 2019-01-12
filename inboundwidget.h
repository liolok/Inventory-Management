#ifndef INBOUNDWIDGET_H
#define INBOUNDWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
    class InboundWidget;
}

class InboundWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InboundWidget(QWidget *parent = nullptr);
    ~InboundWidget();

private:
    Ui::InboundWidget *ui;
    QSqlQuery *qry;
    QSqlQueryModel *modelInbound;
    QSqlQueryModel *modelCategory;
    void refreshInboundTableView(const QString& qry_clause = "");

public slots:
    void refreshCategoryComboBox();
    void on_pushButtonQuery_clicked();
};

#endif // INBOUNDWIDGET_H

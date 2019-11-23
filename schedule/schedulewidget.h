#ifndef SCHEDULEWIDGET_H
#define SCHEDULEWIDGET_H

#include <database/databaseholder.h>
#include <QTableView>
#include <QSqlTableModel>

class ScheduleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScheduleWidget(QWidget *parent = nullptr);

signals:

public slots:

private:
    const QString TABLE_NAME = "schedule";
    QTableView* view;
    QSqlTableModel* model;
    DataBaseHolder* db;

    void initModel();
    void initView();
};

#endif // SCHEDULEWIDGET_H

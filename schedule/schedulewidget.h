#ifndef SCHEDULEWIDGET_H
#define SCHEDULEWIDGET_H

#include <QTableView>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QScrollBar>
#include "database/databaseholder.h"
#include "scheduledelegate.h"
#include "schedulesortfilterproxymodel.h"

class ScheduleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScheduleWidget(QWidget *parent = nullptr);

signals:

public slots:
    void adjustView();

private:
    DataBaseHolder * db;
    ScheduleSortFilterProxyModel * model;
    QTableView * view;
    QPushButton * add_record_button;
    QGroupBox * schedule_box;

    void initModel();
    void initView();
    void initLayout();
    void adjustViewHeight();
    void adjustViewWidth();
};

#endif // SCHEDULEWIDGET_H

#include "schedulewidget.h"

ScheduleWidget::ScheduleWidget(QWidget *parent) : QWidget(parent)
{
    initModel();
    initView();
}

void ScheduleWidget::initModel() {
    db = new DataBaseHolder();
    model = new QSqlTableModel(nullptr, db->getDB());
    model->setTable(TABLE_NAME);
    model->select();
}

void ScheduleWidget::initView() {
    view = new QTableView();
    view->setModel(model);
    view->show();
}

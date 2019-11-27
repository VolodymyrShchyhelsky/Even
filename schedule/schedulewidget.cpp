#include "schedulewidget.h"

ScheduleWidget::ScheduleWidget(QWidget *parent) : QWidget(parent)
{
    initModel();
    initView();
    initLayout();
    qDebug() << "initialized layout";
    qDebug() << "adjusted view";
}

void ScheduleWidget::initModel() {
    db = DataBaseHolder::getDbHolder();
    QSqlTableModel * sql_model = new QSqlTableModel(nullptr, db->getDB());
    sql_model->setTable(SCHEDULE_TABLE);
    model = new ScheduleSortFilterProxyModel(this);
    sql_model->select();
    model->setSourceModel(sql_model);
    model->sortByDateTime();
}

void ScheduleWidget::initView() {
    view = new QTableView(this);
    view->setModel(model);
    view->setItemDelegate(new ScheduleDelegate);
    view->setColumnHidden(0, true);
    view->resize(parentWidget()->size());
    view->resizeColumnsToContents();
    //view->verticalHeader()->setVisible(false);
    view->show();
    qDebug() << this->size();
}

void ScheduleWidget::initLayout() {
    add_record_button = new QPushButton("Add record", this);
    connect(add_record_button, &QPushButton::clicked,
            model, &ScheduleSortFilterProxyModel::createRecord);

    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(view);
    layout->addWidget(add_record_button);
    setLayout(layout);
}

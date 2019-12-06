#include "schedulewidget.h"

ScheduleWidget::ScheduleWidget(QWidget *parent) : QWidget(parent)
{
    initModel();
    initView();
    initLayout();
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
    adjustTableView();
    view->show();
}

void ScheduleWidget::adjustTableView() {
    if (view->verticalHeader()->count()) {
        view->resizeColumnsToContents();
    }
    view->horizontalHeader()->setStretchLastSection(true);
}

void ScheduleWidget::initLayout() {
    add_record_button = new QPushButton("Add record", this);
    connect(add_record_button, SIGNAL(clicked()),
            model, SLOT(createRecord()));
    delete_records_button = new QPushButton("Delete records", this);
    connect(delete_records_button, SIGNAL(clicked()),
            this, SLOT(deleteRecords()));
    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(view);
    layout->addWidget(add_record_button);
    layout->addWidget(delete_records_button);
    setLayout(layout);
}

void ScheduleWidget::deleteRecords() {
    QItemSelectionModel* selection_model = view->selectionModel();
    const QModelIndexList indexes = selection_model->selectedIndexes();
    model->deleteRecords(indexes);
    adjustTableView();
}

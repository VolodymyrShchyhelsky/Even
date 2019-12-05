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
    view->resizeColumnsToContents();
    //view->verticalHeader()->setVisible(false);
    view->show();
}

void ScheduleWidget::initLayout() {
    add_record_button = new QPushButton("Add record", this);
    connect(add_record_button, &QPushButton::clicked,
            model, &ScheduleSortFilterProxyModel::createRecord);
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
    qDebug() << "delete widget" << indexes.at(0).row()  << indexes.back().row() - indexes.at(0).row() + 1;
    model->deleteRecords(indexes.at(0).row() , indexes.back().row() - indexes.at(0).row() + 1);
//    for (const QModelIndex &index : indexes) {
//        qDebug() << QString("(%1)").arg(index.row());
//        //QString text = QString("(%1,%2)").arg(index.row()).arg(index.column());
//        //model->setData(index, text);
//    }
}

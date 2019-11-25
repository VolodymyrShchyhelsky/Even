#include "schedulesortfilterproxymodel.h"

ScheduleSortFilterProxyModel::ScheduleSortFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent) {
    connect(this, &ScheduleSortFilterProxyModel::dataChanged,
            this, &ScheduleSortFilterProxyModel::sortByDateTime);
}


bool ScheduleSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const {
    QPair<QDateTime, QDateTime> left_from_and_to = ScheduleTools::get_from_and_to(left);
    QPair<QDateTime, QDateTime> right_from_and_to = ScheduleTools::get_from_and_to(right);

    return left_from_and_to.first == right_from_and_to.first ?
                left_from_and_to.second < left_from_and_to.second :
                left_from_and_to.first < right_from_and_to.first;
}

void ScheduleSortFilterProxyModel::sortByDateTime() {
    sort(0);
}

void ScheduleSortFilterProxyModel::createRecord() {
    QSqlTableModel * model = static_cast<QSqlTableModel*>(sourceModel());
    QSqlRecord record = model->record();
    record.setValue(SCHEDULE_DESCRIPTION_COLUMN, "");
    record.setValue(SCHEDULE_FROM_COLUMN, QDateTime::currentDateTime().toString(DATETIME_FORMAT));
    record.setValue(SCHEDULE_TO_COLUMN, QDateTime::currentDateTime().toString(DATETIME_FORMAT));
    qDebug() << model->insertRecord(-1, record);
    model->submitAll();
    model->select();

}

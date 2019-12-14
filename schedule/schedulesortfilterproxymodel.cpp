#include "schedulesortfilterproxymodel.h"

ScheduleSortFilterProxyModel::ScheduleSortFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent) {
    connect(this, &ScheduleSortFilterProxyModel::dataChanged,
            this, &ScheduleSortFilterProxyModel::sortByDateTime);
}


bool ScheduleSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const {
    const QSqlTableModel* model = static_cast<const QSqlTableModel*>(sourceModel());
    QPair<QDateTime, QDateTime> left_from_and_to = ScheduleTools::getFromAndTo(left, model);
    QPair<QDateTime, QDateTime> right_from_and_to = ScheduleTools::getFromAndTo(right, model);

    return left_from_and_to.first == right_from_and_to.first ?
                left_from_and_to.second < left_from_and_to.second :
                left_from_and_to.first < right_from_and_to.first;
}

void ScheduleSortFilterProxyModel::sortByDateTime() {
    sort(0);
}

QDateTime ScheduleSortFilterProxyModel::getStartTime() {
    sort(0);
    QModelIndex start_time_cell = index(0, 1);
    QDateTime start_time;
    if (start_time_cell.isValid()) {
        start_time = ScheduleTools::variantToDateTime(start_time_cell.data());
    }
    return start_time;
}

void ScheduleSortFilterProxyModel::createRecord() {
    QSqlTableModel * model = static_cast<QSqlTableModel*>(sourceModel());
    QSqlRecord record = model->record();
    record.setValue(SCHEDULE_DESCRIPTION_COLUMN, "");
    record.setValue(SCHEDULE_FROM_COLUMN, QDateTime::currentDateTime().toString(DATETIME_FORMAT));
    record.setValue(SCHEDULE_TO_COLUMN, QDateTime::currentDateTime().toString(DATETIME_FORMAT));
    model->insertRecord(-1, record);
    model->submitAll();
    model->select();
}

void ScheduleSortFilterProxyModel::deleteRecords(const QModelIndexList &indexes) {
    QSqlTableModel * model = static_cast<QSqlTableModel*>(sourceModel());
    QSet<int> rows;
    for(QModelIndex index : indexes) {
        QModelIndex actual_index = mapToSource(index);
        int row = actual_index.row();
        rows.insert(row);
    }
    QList<int> rows_to_sort = rows.toList();
    qSort(rows_to_sort);
    for (QList<int>::reverse_iterator it = rows_to_sort.rbegin(); it != rows_to_sort.rend(); ++it) {
        model->removeRow(*it);
    }
    model->database().commit();
    model->submitAll();
    model->select();
}

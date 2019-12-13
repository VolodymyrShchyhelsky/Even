#include "scheduletools.h"

ScheduleTools::ScheduleTools()
{

}

QPair<QDateTime, QDateTime> ScheduleTools::get_from_and_to(const QModelIndex &index, const QSqlTableModel * model) {
    int row = index.row();

    int from_column = model->fieldIndex(SCHEDULE_FROM_COLUMN);
    int to_column = model->fieldIndex(SCHEDULE_TO_COLUMN);

    QModelIndex from_index = model->index(row, from_column);
    QModelIndex to_index = model->index(row, to_column);

    QDateTime from = variantToDateTime(from_index.data());
    QDateTime to = variantToDateTime(to_index.data());

    return qMakePair(from, to);
}

QSqlDatabase ScheduleTools::getDatabase() {
    return DataBaseHolder::getDbHolder()->getDB();
}

QDateTime ScheduleTools::variantToDateTime(QVariant variant) {
    QString date_as_string = variant.toString();
    return QDateTime::fromString(date_as_string, DATETIME_FORMAT);
}

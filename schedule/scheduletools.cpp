#include "scheduletools.h"

ScheduleTools::ScheduleTools()
{

}

QPair<QDateTime, QDateTime> ScheduleTools::get_from_and_to(const QModelIndex &index) {
    const QSqlTableModel * model = static_cast<const QSqlTableModel*>(index.model());

    int from_column = model->fieldIndex(SCHEDULE_FROM_COLUMN);
    int to_column = model->fieldIndex(SCHEDULE_TO_COLUMN);

    int row = index.row();
    QModelIndex from_index = model->index(row, from_column);
    QModelIndex to_index = model->index(row, to_column);

    QDateTime from = from_index.data().toDateTime();
    QDateTime to = to_index.data().toDateTime();

    return qMakePair(from, to);
}

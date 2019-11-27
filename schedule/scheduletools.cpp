#include "scheduletools.h"

ScheduleTools::ScheduleTools()
{

}

QPair<QDateTime, QDateTime> ScheduleTools::get_from_and_to(const QModelIndex &index, const QSqlTableModel * model) {
    //const QSqlTableModel * model = static_cast<const QSqlTableModel*>(index.model());
    qDebug() << model->metaObject()->className();
    int row = index.row();

    int from_column = model->fieldIndex(SCHEDULE_FROM_COLUMN);
    int to_column = model->fieldIndex(SCHEDULE_TO_COLUMN);

    QModelIndex from_index = model->index(row, from_column);
    QModelIndex to_index = model->index(row, to_column);

    QDateTime from = QDateTime::fromString(from_index.data().toString(), DATETIME_FORMAT);
    QDateTime to = QDateTime::fromString(to_index.data().toString(), DATETIME_FORMAT);

    return qMakePair(from, to);


    /*
    qDebug() << index.isValid() << index.data().toString();

    int row = index.row();
    qDebug() << row << "ROW";
    qDebug() << index.data().toString() << "id";

    QSqlDatabase db = getDatabase();
    QSqlQuery query("SELECT " + SCHEDULE_FROM_COLUMN + ", " + SCHEDULE_TO_COLUMN +
                    " FROM " + SCHEDULE_TABLE +
                    " WHERE id==" + index.data().toString());
    query.next();
    QDateTime from = QDateTime::fromString(query.value(0).toString(), DATETIME_FORMAT);
    QDateTime to = QDateTime::fromString(query.value(1).toString(), DATETIME_FORMAT);

    return qMakePair(from, to);*/
}

QSqlDatabase ScheduleTools::getDatabase() {
    return DataBaseHolder::getDbHolder()->getDB();
}

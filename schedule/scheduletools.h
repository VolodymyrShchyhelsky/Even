#ifndef SCHEDULETOOLS_H
#define SCHEDULETOOLS_H

#include <QDateTime>
#include <QModelIndex>
#include <QSqlTableModel>
#include "database/databaseconstants.h"
#include "database/databaseholder.h"

class ScheduleTools
{

public:
    static QPair<QDateTime, QDateTime> get_from_and_to(const QModelIndex &index, const QSqlTableModel * model);
    static QDateTime variantToDateTime(QVariant variant);

private:
    ScheduleTools();
    static QSqlDatabase getDatabase();
};

#endif // SCHEDULETOOLS_H

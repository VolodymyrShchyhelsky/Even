#ifndef SCHEDULETOOLS_H
#define SCHEDULETOOLS_H

#include <QDateTime>
#include <QModelIndex>
#include <QSqlTableModel>
#include "database/databaseconstants.h"

class ScheduleTools
{

public:
    static QPair<QDateTime, QDateTime> get_from_and_to(const QModelIndex &index);

private:
    ScheduleTools();
};

#endif // SCHEDULETOOLS_H

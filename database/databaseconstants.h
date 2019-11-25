#ifndef DATABASECONSTANTS_H
#define DATABASECONSTANTS_H

#include <QString>
#include <QDebug>

const QString SCHEDULE_TABLE = "schedule";
const QString SCHEDULE_DESCRIPTION_COLUMN = "description";
const QString SCHEDULE_FROM_COLUMN = "start";
const QString SCHEDULE_TO_COLUMN = "end";
const QString DATETIME_FORMAT = "dd/MM/yyyy HH:mm";


const QString GUEST_TABLE = "guest";
const QString TABLEGUEST_TABLE = "tableguest";

const QString TABLES_TABLE = "tables";
const QString TABLES_X_COLUMN = "x";
const QString TABLES_Y_COLUMN = "y";
const QString TABLES_BASE_CAPACITY_COLUMN = "base_capacity";
const QString TABLES_SECONDARY_CAPACITY_COLUMN = "secondary_capacity";

#endif // DATABASECONSTANTS_H

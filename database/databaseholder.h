#ifndef DATABASE_H
#define DATABASE_H

#include "sqlqueries.h"
#include <QSql>
#include <QSqlDatabase>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QList>
#include <QPair>
#include "databaseconstants.h"
#include <QCoreApplication>
#include <QApplication>

class DataBaseHolder
{
public:
    QSqlDatabase getDB();
    static DataBaseHolder* getDbHolder();

    void getSchedule();

private:
    static DataBaseHolder* instance;
    DataBaseHolder();

    void createTables();
    void connectToDB();
//    const QString PATH = QApplication::applicationDirPath() + "/dataBase.db";
    const QString PATH = "C:/Qt/WorkSpace/Even/dataBase.db";

    QSqlDatabase db;

    typedef void(DataBaseHolder::*fp)();
    QList< QPair<QString, fp> > tables;
    void initTables();
    void createGuestTable();
    void createScheduleTable();
    void createTableTable();
    void createTagTable();
    void createTableToGuestTable();
    void createTagToGuestTable();
    void createTodoTable();
    void add(int id, int name);
};

#endif // DATABASE_H

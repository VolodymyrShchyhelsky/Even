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

    QString insertNewTable(QString base_capacity, QString secondary_capacity);
    void changeTableCoordinates(QString table_id, QString x, QString y);
    void deleteTable(QString table_id);
    void deleteTableGuestEntriesByTableId(QString table_id);

    QString getNameByGuestId(QString guest_id);

    void addTableGuestEntry(QString table_id, QString guest_id);

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

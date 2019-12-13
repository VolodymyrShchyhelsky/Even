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
#include <QVector4D>

class DataBaseHolder
{
public:
    QSqlDatabase getDB();
    static DataBaseHolder* getDbHolder();

    int insertNewTable(int base_capacity, int secondary_capacity);
    void changeTableCoordinates(int table_id, int x, int y);
    void deleteTable(int table_id);
    void deleteTableGuestEntriesByTableId(int table_id);
    QVector< QMap<QString, int> > getAllTables();

    QString getNameByGuestId(QString guest_id);

    void addTableGuestEntry(int table_id, QString guest_id);
    QStringList getNamesOfGuestsOnTable(int table_id);

private:
    static DataBaseHolder* instance;
    DataBaseHolder();

    void createTables();
    void connectToDB();
    const QString PATH = QApplication::applicationDirPath() + "/dataBase.db";
//    const QString PATH = "C:/Qt/WorkSpace/Even/dataBase.db";

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

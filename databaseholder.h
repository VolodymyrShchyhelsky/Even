#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSql>
#include <QSqlDatabase>
#include <QVariant>
#include "sqlqueries.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>

class DataBaseHolder
{
public:
    DataBaseHolder();
    QSqlDatabase getDB() const;

private:
    void createTables();
    void connectToDB();

    const QString PATH = "C://Qt//WorkSpace//Even//dataBase.db";
    QSqlDatabase db;

    void add(int id, int name);
};

#endif // DATABASE_H

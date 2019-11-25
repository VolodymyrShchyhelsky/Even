#include "databaseholder.h"

DataBaseHolder* DataBaseHolder::instance = nullptr;

DataBaseHolder::DataBaseHolder()
{
    qDebug() <<"path"<<  PATH ;
    connectToDB();
}

DataBaseHolder* DataBaseHolder::getDbHolder() {
    if (instance == nullptr) {
        instance = new DataBaseHolder();
    }
    return instance;
}

QSqlDatabase DataBaseHolder::getDB() {
    return db;
}
void DataBaseHolder::connectToDB() {
    QFile file( PATH );
    qDebug() << "File exists:" << file.exists();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(PATH);
    if(!db.open()) {
        qDebug() <<"last er "<< db.lastError();
    } else {
        createTables();
//        QString name = "TEXT";
//        QSqlQuery insert_tag = QSqlQuery("insert into tag (name) values (" + name + ")", db);
//        qDebug() << "AAAAAA exe" << insert_tag.exec();
//        QString tag_id = insert_tag.lastInsertId().toString();
//            qDebug() << "ASASS save" << tag_id;
    }

}

void DataBaseHolder::createTables()
{
    initTables();
    QStringList db_tables = db.tables();
    qDebug() << "query " <<db_tables;
    for (int i = 0; i < tables.size(); ++i) {
        auto table = tables[i];
        if(!db_tables.contains(table.first)) {
            //TODO test it
            (this->*tables[i].second)();
        }
    }
    QStringList db_tables1 = db.tables();
    qDebug() << "query1 " << db_tables1;
}

void DataBaseHolder::initTables()
{
    tables.append(qMakePair<QString, fp>("guest",&DataBaseHolder::createGuestTable));
    tables.append(qMakePair<QString, fp>("schedule",&DataBaseHolder::createScheduleTable));
    tables.append(qMakePair<QString, fp>("table",&DataBaseHolder::createTableTable));
    tables.append(qMakePair<QString, fp>("tag",&DataBaseHolder::createTagTable));
    tables.append(qMakePair<QString, fp>("tabletoguest",&DataBaseHolder::createTableToGuestTable));
    tables.append(qMakePair<QString, fp>("tagtoguest",&DataBaseHolder::createTagToGuestTable));
    tables.append(qMakePair<QString, fp>(GUEST_TABLE, &DataBaseHolder::createGuestTable));
    tables.append(qMakePair<QString, fp>(SCHEDULE_TABLE, &DataBaseHolder::createScheduleTable));
}

void DataBaseHolder::createGuestTable() {
    QSqlQuery create_table = QSqlQuery(
            "create table guest"
            "(id integer primary key AUTOINCREMENT, "
            "surname varchar(20))", db);
    create_table.exec();
    QSqlQuery* addIntoTableQ1 = new QSqlQuery(
            "insert into guest (id, surname)"
            "values (?, ?)"
            );
    addIntoTableQ1->bindValue(0, 15);
    addIntoTableQ1->bindValue(1, "test sur");
    addIntoTableQ1->exec();

}

void DataBaseHolder::createScheduleTable() {
    qDebug() << "cre here";
    QSqlQuery create_table = QSqlQuery(
            "create table " + SCHEDULE_TABLE +
            "(id integer primary key autoincrement, " +
            SCHEDULE_FROM_COLUMN + " varchar(20), " +
            SCHEDULE_TO_COLUMN + " varchar(20), " +
            SCHEDULE_DESCRIPTION_COLUMN + " varchar(20))", db);
    create_table.exec();
}

void DataBaseHolder::createTableTable() {
    QSqlQuery create_table = QSqlQuery(
            "create table table"
            "(id integer primary key AUTOINCREMENT, "
            "x integer, "
            "y integer, "
            "is_round integer, "
            "capacity integer)", db);
    create_table.exec();
}

void DataBaseHolder::createTagTable() {
    QSqlQuery create_table = QSqlQuery(
            "create table tag"
            "(id integer primary key AUTOINCREMENT , "
            "name varchar(20))", db);
    create_table.exec();
}

void DataBaseHolder::createTableToGuestTable() {
    QSqlQuery create_table = QSqlQuery(
            "create table tabletoguest"
            "(table_id integer, "
            "guest_id integer)", db);
    create_table.exec();
}

void DataBaseHolder::createTagToGuestTable() {
    QSqlQuery create_table = QSqlQuery(
            "create table tagtoguest"
            "(tag_id integer , "
            "guest_id integer)", db);
    create_table.exec();
}





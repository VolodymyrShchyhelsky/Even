#include "databaseholder.h"

DataBaseHolder* DataBaseHolder::instance = nullptr;

DataBaseHolder::DataBaseHolder()
{
    connectToDB();
}

DataBaseHolder* DataBaseHolder::getDbHolder() {
    if(instance == nullptr) {
        instance = new DataBaseHolder();
    }
    return instance;
}

QSqlDatabase DataBaseHolder::getDB() {
    return db;
}


void DataBaseHolder::add(int id, int age) {
    qDebug() << "AAAA";
    QSqlQuery* query = new QSqlQuery(ADD_Q, db);
    query->bindValue(0, id);
    query->bindValue(1, age);
    query->exec();
}

void DataBaseHolder::connectToDB() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(PATH);
    if(!db.open()) {

        qDebug() <<"last er "<< db.lastError();

    } else {
            createTables();

     //   QSqlQuery* query = new QSqlQuery(ADD_Q, db);





    }

}

void DataBaseHolder::createTables()
{
    initTables();
    QStringList db_tables = db.tables();
    qDebug() << "query " <<db_tables;
    for(int i = 0; i < tables.size(); ++i) {
        auto table = tables[i];
        if(!db_tables.contains(table.first)) {
            //TODO test it
            (this->*tables[i].second)();
        }
    }
    QStringList db_tables1 = db.tables();
    qDebug() << "query1 " <<db_tables1;
}

void DataBaseHolder::initTables()
{
    tables.append(qMakePair<QString, fp>("guest",&DataBaseHolder::createGuestTable));
    tables.append(qMakePair<QString, fp>("schedule",&DataBaseHolder::createScheduleTable));
}

void DataBaseHolder::createGuestTable() {
    QSqlQuery create_table = QSqlQuery(
            "create table guest"
            "(id integer primary key, "
            "age integer)", db);
    create_table.exec();
    QSqlQuery* addIntoTableQ1 = new QSqlQuery(
            "insert into guest (id, age)"
            "values (?, ?)"
            );
    addIntoTableQ1->bindValue(0, 15);
    addIntoTableQ1->bindValue(1, 15);
    addIntoTableQ1->exec();

}

void DataBaseHolder::createScheduleTable() {
    qDebug() << "cre here";
    QSqlQuery create_table = QSqlQuery(
            "create table schedule"
            "(id integer primary key, "
            "start varchar(20), "
            "end varchar(20), "
            "description varchar(20))", db);
    create_table.exec();
}





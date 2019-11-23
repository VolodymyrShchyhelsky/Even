#include "databaseholder.h"

DataBaseHolder::DataBaseHolder()
{
    connectToDB();
}

QSqlDatabase DataBaseHolder::getDB() const {
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

        qDebug() << db.lastError();

    } else {
//        QSqlQuery* createVisitorsTableQ1 = new QSqlQuery(
//                "create table person"
//                "(id integer primary key, "
//                "age integer)", db);
//        createVisitorsTableQ1->exec();

     //   QSqlQuery* query = new QSqlQuery(ADD_Q, db);



        QSqlQuery* addIntoTableQ1 = new QSqlQuery(
                "insert into person (id, age)"
                "values (?, ?)"
                );
        addIntoTableQ1->bindValue(0, 15);
        addIntoTableQ1->bindValue(1, 15);
        addIntoTableQ1->exec();
//        QSqlQuery query("SELECT * FROM person", db);
//        query.exec();
//        int fieldNo = query.value("age").toInt();


//        qDebug() << "AAAA1";
        //qDebug() << fieldNo;
    }
    createTables();
}

void DataBaseHolder::createTables()
{

    //RM
       add(99, 99);
       add(96, 98);
    //
   // QSqlQuery query
}





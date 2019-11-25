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
    tables.append(qMakePair<QString, fp>("todo", &DataBaseHolder::createTodoTable));
}

void DataBaseHolder::createTodoTable() {
    QSqlQuery create_table = QSqlQuery(
            "create table todo"
            "(id integer primary key AUTOINCREMENT, "
            "father_id integer not null, "
            "name varchar(20) default \"enter_name\", "
            "status integer default 0)" , db);
    qDebug() << "create table" << create_table.exec();
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
            "create table " + TABLES_TABLE +
            "(id integer primary key AUTOINCREMENT, " +
            TABLES_X_COLUMN + " integer DEFAULT 0, " +
            TABLES_Y_COLUMN + " integer DEFAULT 0, " +
            TABLES_BASE_CAPACITY_COLUMN + " integer, " +
            TABLES_SECONDARY_CAPACITY_COLUMN + " integer DEFAULT 0)", db);
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
            "(tag_id integer, "
            "guest_id integer)", db);
    create_table.exec();
}

QString DataBaseHolder::getNameByGuestId(QString guest_id) {
    QSqlQuery get_name = QSqlQuery(
                "select surname "
                "from guest "
                "where id=" + guest_id,
                db);
    get_name.next();
    return get_name.value(0).toString();
}

QString DataBaseHolder::insertNewTable(QString base_capacity, QString secondary_capacity) {
    QSqlQuery insert_new_table = QSqlQuery(
            "insert into " + TABLES_TABLE +
            "(" + TABLES_BASE_CAPACITY_COLUMN + ", " +
            TABLES_SECONDARY_CAPACITY_COLUMN + ")"
            "values ('?', '?')",
            db);
    insert_new_table.bindValue(0, base_capacity);
    insert_new_table.bindValue(1, secondary_capacity);
    return insert_new_table.lastInsertId().toString();
}

void DataBaseHolder::deleteTable(QString table_id) {
    QSqlQuery delete_table = QSqlQuery(
                "delete from " + TABLES_TABLE +
                " where id=" + table_id,
                db);
    delete_table.exec();
    deleteTableGuestEntriesByTableId(table_id);
}

void DataBaseHolder::deleteTableGuestEntriesByTableId(QString table_id) {
    QSqlQuery delete_tableguest_entries = QSqlQuery(
                "delete from " + TABLEGUEST_TABLE +
                " where table_id=" + table_id,
                db);
    delete_tableguest_entries.exec();
}

void DataBaseHolder::addTableGuestEntry(QString table_id, QString guest_id) {
    QSqlQuery insert_new_entry = QSqlQuery(
            "insert into " + TABLEGUEST_TABLE +
            "(table_id, guest_id) "
            "values ('?', '?')",
            db);
    insert_new_entry.bindValue(0, table_id);
    insert_new_entry.bindValue(1, guest_id);
    insert_new_entry.exec();
}

void DataBaseHolder::changeTableCoordinates(QString table_id, QString x, QString y) {
    QSqlQuery change_coordinates = QSqlQuery(
                "update " + TABLES_TABLE +
                " set " +
                TABLES_X_COLUMN + "=?, " +
                TABLES_Y_COLUMN + "=? " +
                "where id=?",
                db);
    change_coordinates.bindValue(0, x);
    change_coordinates.bindValue(1, y);
    change_coordinates.bindValue(2, table_id);
}




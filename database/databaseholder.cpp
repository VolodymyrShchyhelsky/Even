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
    }

}

void DataBaseHolder::createTables()
{
    initTables();
    QStringList db_tables = db.tables();
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
    tables.append(qMakePair<QString, fp>(GUEST_TABLE, &DataBaseHolder::createGuestTable));
    tables.append(qMakePair<QString, fp>(SCHEDULE_TABLE, &DataBaseHolder::createScheduleTable));
    tables.append(qMakePair<QString, fp>(TABLES_TABLE, &DataBaseHolder::createTableTable));
    tables.append(qMakePair<QString, fp>("tag",&DataBaseHolder::createTagTable));
    tables.append(qMakePair<QString, fp>(TABLEGUEST_TABLE, &DataBaseHolder::createTableToGuestTable));
    tables.append(qMakePair<QString, fp>("tagtoguest",&DataBaseHolder::createTagToGuestTable));
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
            "create table " + TABLEGUEST_TABLE +
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
                "where id=?",
                db);
    get_name.addBindValue(guest_id);
    get_name.exec();
    get_name.next();
    return get_name.value(0).toString();
}

int DataBaseHolder::insertNewTable(int base_capacity, int secondary_capacity) {
    QSqlQuery insert_new_table = QSqlQuery(
            "insert into " + TABLES_TABLE +
            "(" + TABLES_BASE_CAPACITY_COLUMN + ", " +
            TABLES_SECONDARY_CAPACITY_COLUMN + ")"
            " values (?, ?)",
            db);
    insert_new_table.addBindValue(base_capacity);
    insert_new_table.addBindValue(secondary_capacity);
    insert_new_table.exec();
    return insert_new_table.lastInsertId().toInt();
}

void DataBaseHolder::deleteTable(int table_id) {
    QSqlQuery delete_table = QSqlQuery(
                "delete from " + TABLES_TABLE +
                " where id=?",
                db);
    delete_table.addBindValue(table_id);
    delete_table.exec();
    deleteTableGuestEntriesByTableId(table_id);
}

void DataBaseHolder::deleteTableGuestEntriesByTableId(int table_id) {
    QSqlQuery delete_tableguest_entries = QSqlQuery(
                "delete from " + TABLEGUEST_TABLE +
                " where table_id=?",
                db);
    delete_tableguest_entries.addBindValue(table_id);
    delete_tableguest_entries.exec();
}

void DataBaseHolder::addTableGuestEntry(int table_id, QString guest_id) {
    QSqlQuery insert_new_entry = QSqlQuery(
            "insert into " + TABLEGUEST_TABLE +
            "(table_id, guest_id) "
            "values (?, ?)",
            db);
    insert_new_entry.addBindValue(table_id);
    insert_new_entry.addBindValue(guest_id);
    qDebug() << "guest to table" << insert_new_entry.exec() << table_id << guest_id;
}

void DataBaseHolder::changeTableCoordinates(int table_id, int x, int y) {
    QSqlQuery change_coordinates = QSqlQuery(
                "update " + TABLES_TABLE +
                " set " +
                TABLES_X_COLUMN + "=?, " +
                TABLES_Y_COLUMN + "=? " +
                "where id=?",
                db);
    change_coordinates.addBindValue(x);
    change_coordinates.addBindValue(y);
    change_coordinates.addBindValue(table_id);
    change_coordinates.exec();

}

QVector< QMap<QString, int> > DataBaseHolder::getAllTables() {
    QSqlQuery select_tables = QSqlQuery(
                "select id," + TABLES_X_COLUMN + "," + TABLES_Y_COLUMN + "," + TABLES_BASE_CAPACITY_COLUMN + "," + TABLES_SECONDARY_CAPACITY_COLUMN +
                " from "+ TABLES_TABLE,
                db);
    QSqlRecord empty_record = select_tables.record();
    int id = empty_record.indexOf("id");
    int x = empty_record.indexOf(TABLES_X_COLUMN);
    int y = empty_record.indexOf(TABLES_Y_COLUMN);
    int base_capacity = empty_record.indexOf(TABLES_BASE_CAPACITY_COLUMN);
    int secondary_capacity = empty_record.indexOf(TABLES_SECONDARY_CAPACITY_COLUMN);
    QVector< QMap<QString, int> > tables_data;
    while (select_tables.next()) {
        QMap<QString, int> table;
        table["id"] = select_tables.value(id).toInt();
        table[TABLES_X_COLUMN] = select_tables.value(x).toInt();
        table[TABLES_Y_COLUMN] = select_tables.value(y).toInt();
        table[TABLES_BASE_CAPACITY_COLUMN] = select_tables.value(base_capacity).toInt();
        table[TABLES_SECONDARY_CAPACITY_COLUMN] = select_tables.value(secondary_capacity).toInt();
        tables_data.append(table);
    }
    return tables_data;
}

QStringList DataBaseHolder::getNamesOfGuestsOnTable(int table_id) {
    QSqlQuery get_names_of_guests_on_table = QSqlQuery(
                "select surname "
                "from " + GUEST_TABLE +
                " join " + TABLEGUEST_TABLE +
                " on " + GUEST_TABLE + ".id=" + TABLEGUEST_TABLE + ".guest_id "
                "where " + TABLEGUEST_TABLE + ".table_id=?",
                db);
    get_names_of_guests_on_table.addBindValue(table_id);
    get_names_of_guests_on_table.exec();
    QStringList guest_names;
    while (get_names_of_guests_on_table.next()) {
        guest_names.append(get_names_of_guests_on_table.value(0).toString());
    }
    return guest_names;
}



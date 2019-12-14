#include "testschedulesortfilterproxymodel.h"

void TestScheduleSortFilterProxyModel::createRecord() {
    QSqlTableModel sql_model(nullptr, DataBaseHolder::getDbHolder()->getDB());
    sql_model.setTable(SCHEDULE_TABLE);
    sql_model.select();

    ScheduleSortFilterProxyModel model;
    model.setSourceModel(&sql_model);

    int entries_count_before = DataBaseHolder::getDbHolder()->getRecordCount(SCHEDULE_TABLE);
    model.createRecord();
    int entries_count_after = DataBaseHolder::getDbHolder()->getRecordCount(SCHEDULE_TABLE);
    QCOMPARE(entries_count_after, entries_count_before + 1);
}

void TestScheduleSortFilterProxyModel::deleteRecords() {
    QSqlTableModel sql_model(nullptr, DataBaseHolder::getDbHolder()->getDB());
    sql_model.setTable(SCHEDULE_TABLE);
    sql_model.select();

    ScheduleSortFilterProxyModel model;
    model.setSourceModel(&sql_model);
    model.sortByDateTime();

    int entries_count_before = DataBaseHolder::getDbHolder()->getRecordCount(SCHEDULE_TABLE);
    while (entries_count_before <= 5) {
        model.createRecord();
        entries_count_before = DataBaseHolder::getDbHolder()->getRecordCount(SCHEDULE_TABLE);
    }

    QModelIndexList index_list;
    index_list.append(model.index(0, 0));
    index_list.append(model.index(0, 1));
    index_list.append(model.index(2, 0));
    index_list.append(model.index(5, 0));

    model.deleteRecords(index_list);
    int entries_count_after = DataBaseHolder::getDbHolder()->getRecordCount(SCHEDULE_TABLE);
    QCOMPARE(entries_count_after, entries_count_before - 3);
}

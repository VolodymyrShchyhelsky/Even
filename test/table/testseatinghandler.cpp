#include "testseatinghandler.h"

void TestSeatingHandler::addTable() {
    int entries_count_before = DataBaseHolder::getDbHolder()->getRecordCount(TABLES_TABLE);

    SeatingHandler handler;
    RoundTable table(1);
    handler.addTable(&table);

    int entries_count_after = DataBaseHolder::getDbHolder()->getRecordCount(TABLES_TABLE);
    QVERIFY(entries_count_after - entries_count_before == 1);
}

void TestSeatingHandler::loadTablesFromDatabase() {
    int entries_count = DataBaseHolder::getDbHolder()->getRecordCount(TABLES_TABLE);

    SeatingHandler handler;
    QWidget widget;
    handler.loadTablesFromDatabase(&widget);

    // for each table entry a QWidget parents a Table and a TableView
    int num_of_tables = widget.children().length() / 2;
    QVERIFY(num_of_tables == entries_count);
}

void TestSeatingHandler::seatGuestWithoutChosenTable() {
    SeatingHandler handler;

    QString message_box_text;
    QTimer::singleShot(0, [&]() {
        QMessageBox * box = dynamic_cast<QMessageBox*>(QApplication::activeModalWidget());
        message_box_text = box->text();
        box->close();
    });

    handler.seatGuest("1");
    QVERIFY(message_box_text == "You didn't choose a table.");
}

void TestSeatingHandler::seatGuestOnFullTable() {
    SeatingHandler handler;

    RoundTable table(1);
    table.addGuest("1");

    TableView view(&table);
    handler.setCurrentTable(&view);

    QString message_box_text;
    QTimer::singleShot(0, [&]() {
        QMessageBox * box = dynamic_cast<QMessageBox*>(QApplication::activeModalWidget());
        message_box_text = box->text();
        box->close();
    });

    handler.seatGuest("2");
    QVERIFY(message_box_text == "The table you chose doesn't have any free seats.");
}

void TestSeatingHandler::seatGuest() {
    int entries_count_before = DataBaseHolder::getDbHolder()->getRecordCount(TABLEGUEST_TABLE);
    SeatingHandler handler;

    RoundTable table(1);
    handler.addTable(&table);

    TableView view(&table);
    handler.setCurrentTable(&view);

    handler.seatGuest("3");

    int entries_count_after = DataBaseHolder::getDbHolder()->getRecordCount(TABLEGUEST_TABLE);
    QCOMPARE(entries_count_after, entries_count_before + 1);
}

void TestSeatingHandler::deleteCurrentTableWithoutChosenTable() {
    SeatingHandler handler;

    QString message_box_text;
    QTimer::singleShot(0, [&]() {
        QMessageBox * box = dynamic_cast<QMessageBox*>(QApplication::activeModalWidget());
        message_box_text = box->text();
        box->close();
    });

    handler.deleteCurrentTable();
    QVERIFY(message_box_text == "You didn't choose a table.");
}

void TestSeatingHandler::deleteCurrentTable() {
    SeatingHandler handler;

    RoundTable table(1);
    handler.addTable(&table);
    int table_entries_count_before = DataBaseHolder::getDbHolder()->getRecordCount(TABLES_TABLE);

    TableView * view = new TableView(&table);
    handler.setCurrentTable(view);

    handler.seatGuest("4");
    int tableguest_entries_count_before = DataBaseHolder::getDbHolder()->getRecordCount(TABLEGUEST_TABLE);

    handler.deleteCurrentTable();

    int table_entries_count_after = DataBaseHolder::getDbHolder()->getRecordCount(TABLES_TABLE);
    QCOMPARE(table_entries_count_after, table_entries_count_before - 1);

    int tableguest_entries_count_after = DataBaseHolder::getDbHolder()->getRecordCount(TABLEGUEST_TABLE);
    QCOMPARE(tableguest_entries_count_after, tableguest_entries_count_before - 1);
}

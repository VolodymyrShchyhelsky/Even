#include "testroundtablecreationwidget.h"

void TestRoundTableCreationWidget::createTableNegativeCapacity() {
    RoundTableCreationWidget widget;
    QTest::keyClick(widget.num_of_guests_box, Qt::Key_Right);
    QTest::keyClick(widget.num_of_guests_box, Qt::Key_Backspace);
    QTest::keyClicks(widget.num_of_guests_box, "-1");
    verifyTable(widget, 1);
}

void TestRoundTableCreationWidget::createTablePositiveCapacity() {
    RoundTableCreationWidget widget;
    QTest::keyClick(widget.num_of_guests_box, Qt::Key_Right);
    QTest::keyClick(widget.num_of_guests_box, Qt::Key_Backspace);
    QTest::keyClick(widget.num_of_guests_box, '2');
    verifyTable(widget, 2);
}

void TestRoundTableCreationWidget::createTableValidCapacityThenBackspaceThenInvalidSymbol() {
    RoundTableCreationWidget widget;
    QTest::keyClick(widget.num_of_guests_box, Qt::Key_Right);
    QTest::keyClick(widget.num_of_guests_box, Qt::Key_Backspace);
    QTest::keyClick(widget.num_of_guests_box, '3');
    QTest::keyClick(widget.num_of_guests_box, Qt::Key_Backspace);
    QTest::keyClick(widget.num_of_guests_box, 'j');
    verifyTable(widget, 3);
}

void TestRoundTableCreationWidget::createTableValidCapacityThenInvalidSymbol() {
    RoundTableCreationWidget widget;
    QTest::keyClick(widget.num_of_guests_box, Qt::Key_Right);
    QTest::keyClick(widget.num_of_guests_box, Qt::Key_Backspace);
    QTest::keyClick(widget.num_of_guests_box, '4');
    QTest::keyClick(widget.num_of_guests_box, 'm');
    verifyTable(widget, 4);
}

void TestRoundTableCreationWidget::verifyTable(RoundTableCreationWidget &widget, int capacity) {
    RoundTable * actual_table = dynamic_cast<RoundTable*>(widget.createTable());
    RoundTable expected_table(capacity);
    QVERIFY(*actual_table == expected_table);
}


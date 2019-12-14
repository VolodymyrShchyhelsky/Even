#include "testrectangulartablecreationwidget.h"

void TestRectangularTableCreationWidget::createTableNegativeWidth() {
    RectangularTableCreationWidget widget;
    QTest::keyClick(widget.width_box, Qt::Key_Right);
    QTest::keyClick(widget.width_box, Qt::Key_Backspace);
    QTest::keyClicks(widget.width_box, "-1");
    verifyTable(widget, 1, 1);
}

void TestRectangularTableCreationWidget::createTablePositiveHeight() {
    RectangularTableCreationWidget widget;
    QTest::keyClick(widget.height_box, Qt::Key_Right);
    QTest::keyClick(widget.height_box, Qt::Key_Backspace);
    QTest::keyClick(widget.height_box, '2');
    verifyTable(widget, 1, 2);
}

void TestRectangularTableCreationWidget::createTableValidHeightThenBackspaceThenInvalidSymbol() {
    RectangularTableCreationWidget widget;
    QTest::keyClick(widget.height_box, Qt::Key_Right);
    QTest::keyClick(widget.height_box, Qt::Key_Backspace);
    QTest::keyClick(widget.height_box, '3');
    QTest::keyClick(widget.height_box, Qt::Key_Backspace);
    QTest::keyClick(widget.height_box, 'j');
    verifyTable(widget, 1, 3);
}

void TestRectangularTableCreationWidget::createTableValidWidthThenInvalidSymbol() {
    RectangularTableCreationWidget widget;
    QTest::keyClick(widget.width_box, Qt::Key_Right);
    QTest::keyClick(widget.width_box, Qt::Key_Backspace);
    QTest::keyClick(widget.width_box, '4');
    QTest::keyClick(widget.width_box, 'm');
    verifyTable(widget, 4, 1);
}

void TestRectangularTableCreationWidget::verifyTable(RectangularTableCreationWidget &widget, int width, int height) {
    RectangularTable * actual_table = dynamic_cast<RectangularTable*>(widget.createTable());
    RectangularTable expected_table(width, height);
    QVERIFY(*actual_table == expected_table);
}


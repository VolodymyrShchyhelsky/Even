#ifndef TESTRECTANGULARTABLECREATIONWIDGET_H
#define TESTRECTANGULARTABLECREATIONWIDGET_H

#include <QtTest>
#include "table/rectangulartablecreationwidget.h"

class TestRectangularTableCreationWidget : public QObject
{
    Q_OBJECT

private slots:
    void createTableNegativeWidth();
    void createTablePositiveHeight();
    void createTableValidWidthThenInvalidSymbol();
    void createTableValidHeightThenBackspaceThenInvalidSymbol();

private:
    void verifyTable(RectangularTableCreationWidget &widget, int width, int height);
};

#endif // TESTRECTANGULARTABLECREATIONWIDGET_H

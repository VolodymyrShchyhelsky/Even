#ifndef TESTROUNDTABLECREATIONWIDGET_H
#define TESTROUNDTABLECREATIONWIDGET_H

#include <QTest>
#include <table/roundtablecreationwidget.h>

class TestRoundTableCreationWidget : public QObject
{
    Q_OBJECT

private slots:
    void createTableNegativeCapacity();
    void createTablePositiveCapacity();
    void createTableValidCapacityThenInvalidSymbol();
    void createTableValidCapacityThenBackspaceThenInvalidSymbol();

private:
    void verifyTable(RoundTableCreationWidget &widget, int capacity);
};

#endif // TESTROUNDTABLECREATIONWIDGET_H

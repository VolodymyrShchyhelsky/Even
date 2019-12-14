#ifndef TESTSEATINGHANDLER_H
#define TESTSEATINGHANDLER_H

#include <QtTest>
#include "table/seatinghandler.h"

class TestSeatingHandler : public QObject
{
    Q_OBJECT

private slots:
    void loadTablesFromDatabase();
    void addTable();
    void seatGuestWithoutChosenTable();
    void seatGuestOnFullTable();
    void seatGuest();
    void deleteCurrentTableWithoutChosenTable();
    void deleteCurrentTable();
};

#endif // TESTSEATINGHANDLER_H

#ifndef TESTGUESTFILTER_H
#define TESTGUESTFILTER_H

#include <QtTest>
#include "guest/guestfilter.h"
#include "guest/guestmainlist.h"

class TestGuestFilter : public QObject
{
    Q_OBJECT
public:
    GuestFilter* filter;
    GuestMainList* list;


private slots:
    void initTestCase();
    void search();

};

#endif // TESTGUESTFILTER_H

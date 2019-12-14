#ifndef TESTGUESTLISTWINDOW_H
#define TESTGUESTLISTWINDOW_H

#include "testtagwindow.h"

class TestGuestListWindow : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void addGuest();
    void addTag();


public:
    std::unique_ptr<GuestListWindow> test_obj;

};

#endif // TESTGUESTLISTWINDOW_H

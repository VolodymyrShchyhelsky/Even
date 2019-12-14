#ifndef TESTTAGWINDOW_H
#define TESTTAGWINDOW_H

#include <QtTest>
#include <guest/guestlistwindow.h>
#include <memory>
#include <QSignalSpy>

class TestTagWindow : public QObject
{
    Q_OBJECT
public:
    TestTagWindow();

    const QString TEST_NAME = "test_name";

private slots:
    void enterName();
    void save();
//    void withTag();
//    void withoutTag();

public:
    TagWindow* test_obj;
};

#endif // TESTTAGWINDOW_H

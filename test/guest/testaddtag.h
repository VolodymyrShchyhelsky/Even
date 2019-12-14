#ifndef TESTADDTAG_H
#define TESTADDTAG_H

#include <QtTest>
#include "guest/addtagwindow.h"

class TestAddTag : public QObject
{
    Q_OBJECT
public:

signals:

private slots:
    void initTestCase();
    void addTag();

private:
    const QString TEST_ID = "1";

    AddTagWindow* obj;
};

#endif // TESTADDTAG_H

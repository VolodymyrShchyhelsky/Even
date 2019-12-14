#ifndef TESTSCHEDULESORTFILTERPROXYMODEL_H
#define TESTSCHEDULESORTFILTERPROXYMODEL_H

#include <QtTest>
#include "schedule/schedulesortfilterproxymodel.h"

class TestScheduleSortFilterProxyModel : public QObject
{
    Q_OBJECT

private slots:
    void createRecord();
    void deleteRecords();

};

#endif // TESTSCHEDULESORTFILTERPROXYMODEL_H

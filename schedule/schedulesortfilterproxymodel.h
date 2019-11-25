#ifndef SCHEDULESORTFILTERPROXYMODEL_H
#define SCHEDULESORTFILTERPROXYMODEL_H

#include "scheduletools.h"
#include <QSortFilterProxyModel>
#include <QSqlRecord>

class ScheduleSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ScheduleSortFilterProxyModel(QObject *parent = nullptr);

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

public slots:
    void sortByDateTime();
    void createRecord();
};

#endif // SCHEDULESORTFILTERPROXYMODEL_H

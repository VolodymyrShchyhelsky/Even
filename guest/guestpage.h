#ifndef GUESTPAGE_H
#define GUESTPAGE_H

#include <QWidget>
#include <QString>
#include <QTableView>
#include <QSqlTableModel>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QLineEdit>
#include <QDataWidgetMapper>
#include "database/databaseholder.h"

class GuestPage : public QWidget
{
    Q_OBJECT
public:
    explicit GuestPage(QWidget *parent = nullptr, QString id = 0);

signals:

public slots:

private:
    QTableView* user_list_view;
    QSqlTableModel* user_list_model;
    DataBaseHolder* db;
    QString id;

    void initListView();
    void initListModel();
};

#endif // GUESTPAGE_H

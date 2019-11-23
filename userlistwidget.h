#ifndef USERLISTWIDGET_H
#define USERLISTWIDGET_H

#include "guestpage.h"

class UserListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UserListWidget(QWidget *parent = nullptr);

signals:

public slots:

    void getIndex(const QModelIndex &index);

private:
    QTableView* user_list_view;
    QSqlTableModel* user_list_model;
    DataBaseHolder* db;

    void initListView();
    void initListModel();
};

#endif // USERLISTWIDGET_H

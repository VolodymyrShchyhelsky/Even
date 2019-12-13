#ifndef GUESTLISTBASE_H
#define GUESTLISTBASE_H

#include <QObject>
#include <QWidget>
#include "guestpage.h"

class GuestListBase : public QWidget
{
    Q_OBJECT
public:
    explicit GuestListBase(QWidget *parent = nullptr);
    QString getId(const QModelIndex &index);
    void init();
    QSqlTableModel* guest_model;
    QStringList visible_columns;
    void applyFilters(QString filter = "");
    virtual ~GuestListBase() {}
    QTableView* guest_view;
signals:

public slots:


protected:
    QString basic_filter = "";

    DataBaseHolder* db = DataBaseHolder::getDbHolder();

    void configureView();
    void initListView();
    void initModel();
};

#endif // GUESTLISTBASE_H

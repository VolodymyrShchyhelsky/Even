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
    virtual ~GuestListBase() {};
signals:

public slots:


protected:
    const QString basic_filter = "";
    QTableView* guest_view;

    DataBaseHolder* db = DataBaseHolder::getDbHolder();

    void configureView();
    void initListView();
    void initModel();
};

#endif // GUESTLISTBASE_H

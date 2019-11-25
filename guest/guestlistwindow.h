#ifndef GUESTLIST_H
#define GUESTLIST_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QTableView>
#include <QSqlTableModel>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QLineEdit>
#include <QDataWidgetMapper>
#include <QLayout>
#include <memory>
#include "database/databaseholder.h"
#include "userlistwidget.h"
#include "guestlisttablew.h"
#include "guestmainlist.h"
#include "guestfilter.h"
#include <QPushButton>

class GuestListWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GuestListWindow(QWidget *parent = nullptr);

public slots:
    void addNewGest();
    void addTag();

private:
    int w,h;

    QGridLayout* layout;
    GuestFilter* filter;
    GuestMainList* guest_list;
    QPushButton* add_new_guest_b;
    QPushButton* add_new_tag_b;
};

#endif // GUESTLIST_H
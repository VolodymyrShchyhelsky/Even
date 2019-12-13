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
#include "guestlisttablew.h"
#include "guestmainlist.h"
#include "guestfilter.h"
#include <QPushButton>
#include "tagwindow.h"

class GuestListWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GuestListWindow(QDateTime start_time, QWidget *parent = nullptr);

public slots:
    void addNewGest();
    void addTag();
    void updateTag();
    void showLayout();

private:
    QHBoxLayout* layout = nullptr;
    GuestFilter* filter;
    GuestMainList* guest_list;
    QPushButton* add_new_guest_b;
    QPushButton* add_new_tag_b;
};

#endif // GUESTLIST_H

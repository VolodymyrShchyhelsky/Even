#ifndef SEATINGHANDLER_H
#define SEATINGHANDLER_H

#include "tableview.h"
#include <QMessageBox>
#include <database/databaseholder.h>

class SeatingHandler : public QObject
{
    Q_OBJECT
public:
    explicit SeatingHandler(QObject *parent = nullptr);

private:
    TableView * current_table_view = nullptr;

    void createMessageBox(QString text, QString informative_text);
    void askToChooseTable();
    void askToChooseTableWithFreeSeats();

signals:

public slots:
    void addTable(Table * table);
    void setCurrentTable(TableView * table_view);
    void deleteCurrentTable();
    void updateTableLocation(TableView * table_view);
    void seatGuest(QString guest_id);
};

#endif // SEATINGHANDLER_H

/*
guestwidget -> selected guest id signal
handler - accepts id
          gets name
          checks if there are free spaces at the table
          updates tabletoguest / shows warning
          ? updates view
tablewidget -> delete table signal
handler - accepts table id (?)
          updates tables table
          updates tabletoguest
          ? updates view
tablewidget -> add table signal
handler - updates tables table


*/

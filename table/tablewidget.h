#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QGroupBox>
#include "roundtablecreationwidget.h"
#include "rectangulartablecreationwidget.h"
#include "tableview.h"
#include "seatinghandler.h"
#include "guest/guestfilter.h"
#include "guest/guestlisttablew.h"

class TableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TableWidget(QWidget *parent = nullptr);

private:
    QRadioButton * round_table_button;
    QRadioButton * rectangular_table_button;
    QPushButton * add_table_button;
    QPushButton * delete_table_button;
    RoundTableCreationWidget * round_table_creation_widget;
    RectangularTableCreationWidget * rectangular_table_creation_widget;
    QStackedWidget * table_creation_widgets;
    QGroupBox * table_box;
    QWidget * table_graphics_widget;
    SeatingHandler * seating_handler;

    void initTableBox();
    void initLayout();

signals:
    void addTable(Table * table);
    void deleteCurrentTable();

public slots:
    void rectangularTableChosen();
    void roundTableChosen();
    void addTable();
};

#endif // TABLEWIDGET_H

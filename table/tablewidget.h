#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QGraphicsView>
#include <QGroupBox>
#include <QMessageBox>
#include "roundtablecreationwidget.h"
#include "rectangulartablecreationwidget.h"
#include "tableview.h"

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
    QPushButton * save_layout_button;
    RoundTableCreationWidget * round_table_creation_widget;
    RectangularTableCreationWidget * rectangular_table_creation_widget;
    QStackedWidget * table_creation_widgets;
    QGroupBox * table_box;
    QVector<TableView*> table_views;
    TableView * current_table_view;

    void askToChooseTable();

signals:

public slots:
    void rectangularTableChosen();
    void roundTableChosen();
    void addTable();
    void deleteTable();
    void saveLayout();
    void setCurrentTable(TableView * current_table_view);
};

#endif // TABLEWIDGET_H

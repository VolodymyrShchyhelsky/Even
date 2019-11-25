#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QGraphicsView>
#include "table.h"
#include <QKeyEvent>
#include <QFocusEvent>

class TableView : public QWidget
{
    Q_OBJECT
public:
    explicit TableView(Table *table, QWidget *parent=nullptr);
    Table* get_table();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

private:
    QGraphicsView *view;
    Table *table;
    const int move_step = 10;

signals:
    void tableChosen(TableView * this_table);
    void tableUnchosen(TableView * this_table);

public slots:
};

#endif // TABLEVIEW_H

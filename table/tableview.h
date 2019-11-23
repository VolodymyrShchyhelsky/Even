#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QGraphicsView>
#include "table.h"
#include <QKeyEvent>

class TableView : public QWidget
{
    Q_OBJECT
public:
    explicit TableView(Table *table, QWidget *parent=nullptr);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QGraphicsView *view;
    Table *table;
    const int move_step = 10;

signals:

public slots:
};

#endif // TABLEVIEW_H

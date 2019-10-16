#include "tableview.h"

TableView::TableView(Table *table, QWidget *parent) : QWidget(parent), table(table)
{
    view = new QGraphicsView(this);
    view->setScene(table);
    view->setFrameStyle(0);
    view->setStyleSheet("background-color: transparent;");
    table->draw();
    view->setMinimumSize(table->width(), table->height());
    view->setFocusPolicy(Qt::NoFocus);
    view->show();
    setFocusPolicy(Qt::ClickFocus);
}

void TableView::keyPressEvent(QKeyEvent *event) {
    qDebug()<<"press"<<event->text();
    int dx = 0, dy = 0;
    switch (event->key()) {
        case Qt::Key_Left:
            dx = -move_step;
            break;
        case Qt::Key_Right:
            dx = move_step;
            break;
        case Qt::Key_Up:
            dy = -move_step;
            break;
        case Qt::Key_Down:
            dy = move_step;
            break;
        default:
            break;
    }
    move(x() + dx, y() + dy);
}

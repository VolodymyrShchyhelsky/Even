#include "tableview.h"

TableView::TableView(Table *table, QWidget *parent) : QWidget(parent), table(table)
{
    setFocus();
    setFocusPolicy(Qt::ClickFocus);
    setMouseTracking(false);
    setAttribute(Qt::WA_Hover, false);
    view = new QGraphicsView(this);
    view->setScene(table);
    view->setFrameStyle(QFrame::NoFrame);
    view->setStyleSheet("background-color: transparent;");
    table->draw();
    view->setFixedSize(table->width() + 2, table->height() + 2);
    view->setFocusPolicy(Qt::NoFocus);
    view->show();
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

void TableView::focusInEvent(QFocusEvent *event) {
    table->clear();
    table->draw(true);
    emit tableChosen(this);
}

void TableView::focusOutEvent(QFocusEvent *event) {
    emit tableUnchosen(this);
}

Table* TableView::get_table() {
    return table;
}

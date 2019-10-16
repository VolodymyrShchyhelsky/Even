#include "table.h"

Table::Table(QObject *parent) : QGraphicsScene(parent)
{
}

void Table::move(int dx, int dy) {
    x += dx;
    y += dy;
}

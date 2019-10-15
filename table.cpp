#include "table.h"

Table::Table(QObject *parent) : QGraphicsScene(parent)
{
}

void Table::setNumOfGuests(int num_of_guests) {
    if (num_of_guests >= 1) {
        guests = num_of_guests;
        recalculateTableRadius();
    }
}

void Table::recalculateTableRadius() {
    if (guests > 2) {
        table_radius = chair_radius / qTan( M_PI / (double) guests );
        if (table_radius < default_table_radius)
            table_radius = default_table_radius;
    }
    else {
        table_radius = default_table_radius;
    }
}

void Table::draw() {
    int table_coord = 0;
    addEllipse(QRectF(table_coord, table_coord, 2 * table_radius, 2 * table_radius));
    double rotation_angle = 2.0 * M_PI / guests;
    int radius_sum = table_radius + chair_radius;
    int base = table_coord + table_radius - chair_radius;
    for(int i = 0; i < guests; ++i) {
        addEllipse(QRectF(base + radius_sum * qSin(rotation_angle * i),
                          base + radius_sum * qCos(rotation_angle * i),
                          2 * chair_radius, 2 * chair_radius));
    }
}

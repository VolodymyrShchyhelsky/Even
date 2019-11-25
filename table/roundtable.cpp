#include "roundtable.h"

RoundTable::RoundTable(int num_of_guests, QObject *parent) : Table(parent), guests(num_of_guests)
{
    recalculateTableRadius();
}

void RoundTable::recalculateTableRadius() {
    if (guests > 2) {
        table_radius = chair_radius / qTan( M_PI / static_cast<double>(guests) );
        if (table_radius < default_table_radius)
            table_radius = default_table_radius;
    }
    else {
        table_radius = default_table_radius;
    }
}

void RoundTable::draw(bool active) {
    QRectF table_rect = QRectF(x, y, 2 * table_radius, 2 * table_radius);
    if (active) {
        addEllipse(table_rect, QPen(), active_brush);
    }
    else {
        addEllipse(table_rect);
    }
    double rotation_angle = 2.0 * M_PI / guests;
    int radius_sum = table_radius + chair_radius;
    int base_x = x + table_radius - chair_radius;
    int base_y = y + table_radius - chair_radius;
    int chair_diameter = 2 * chair_radius;
    for(int i = 0; i < guests; ++i) {
        QGraphicsEllipseItem * chair = addEllipse(QRectF(base_x + radius_sum * qSin(rotation_angle * i),
                                                         base_y + radius_sum * qCos(rotation_angle * i),
                                                         chair_diameter, chair_diameter));
        if (i < guest_names.length()) {
            QGraphicsTextItem * guest_name = new QGraphicsTextItem(guest_names.at(i), chair);
        }
    }
}

QPair<int, int> RoundTable::get_capacity() {
    return qMakePair(guests, 0);
}

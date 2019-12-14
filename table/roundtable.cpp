#include "roundtable.h"

RoundTable::RoundTable(int num_of_guests, QObject *parent) : Table(parent), capacity(num_of_guests)
{
    recalculateTableRadius();
}

void RoundTable::recalculateTableRadius() {
    if (capacity > 2) {
        table_radius = chair_radius / qTan( M_PI / static_cast<double>(capacity) );
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
    double rotation_angle = 2.0 * M_PI / capacity;
    int radius_sum = table_radius + chair_radius;
    int base_x = x + table_radius - chair_radius;
    int base_y = y + table_radius - chair_radius;
    int chair_diameter = 2 * chair_radius;
    for(int i = 0; i < capacity; ++i) {
        qreal chair_x = base_x + radius_sum * qSin(rotation_angle * i);
        qreal chair_y = base_y + radius_sum * qCos(rotation_angle * i);
        addEllipse(QRectF(chair_x, chair_y, chair_diameter, chair_diameter));
        if (i < guest_names.length()) {
            showGuestName(chair_x, chair_y, i);
        }
    }
}

QPair<int, int> RoundTable::get_capacity() {
    return qMakePair(capacity, 0);
}

int RoundTable::get_total_capacity() {
    return capacity;
}

bool RoundTable::operator==(const RoundTable &other) {
    return (this->capacity == other.capacity
            && this->table_radius == other.table_radius);
}

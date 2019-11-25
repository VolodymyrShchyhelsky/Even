#include "table.h"

Table::Table(QObject *parent) : QGraphicsScene(parent)
{
}

void Table::move(int dx, int dy) {
    x += dx;
    y += dy;
}

void Table::set_id(QString id) {
    this->id = id;
}

QString Table::get_id() {
    return id;
}

void Table::add_guest(QString guest_name) {
    guest_names.append(guest_name);
}

bool Table::can_seat() {
    QPair<int, int> capacity = get_capacity();
    int total_capacity = capacity.first * (capacity.second ? capacity.second : 1);
    return guest_names.length() < total_capacity;
}

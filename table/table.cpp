#include "table.h"

Table::Table(QObject *parent) : QGraphicsScene(parent) {
}

void Table::move(int dx, int dy) {
    x += dx;
    y += dy;
}

void Table::setId(int id) {
    this->id = id;
}

int Table::getId() {
    return id;
}

void Table::addGuest(QString guest_name) {
    guest_names.append(guest_name);
}

void Table::setGuests(QStringList guest_names) {
    this->guest_names = guest_names;
}

bool Table::canSeat() {
    return guest_names.length() < get_total_capacity();
}

void Table::showGuestName(int chair_x, int chair_y, int guest_number) {
    QGraphicsTextItem * guest_name_item = new QGraphicsTextItem();
    guest_name_item->setPos(chair_x, chair_y);
    guest_name_item->setTextWidth(chair_radius*2);
    guest_name_item->setHtml("<center>" + guest_names.at(guest_number) + "</center>");
    addItem(guest_name_item);
}

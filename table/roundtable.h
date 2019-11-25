#ifndef ROUNDTABLE_H
#define ROUNDTABLE_H

#include "table.h"
#include <QGraphicsEllipseItem>

class RoundTable : public Table
{
public:
    explicit RoundTable(int num_of_guests, QObject *parent = nullptr);
    void draw(bool active) override;
    QPair<int, int> get_capacity() override;

private:
    const int default_table_radius = chair_radius + 10;
    int table_radius = default_table_radius;
    int guests;

    void recalculateTableRadius();
};

#endif // ROUNDTABLE_H

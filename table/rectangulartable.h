#ifndef RECTANGULARTABLE_H
#define RECTANGULARTABLE_H

#include "table.h"

class RectangularTable : public Table
{
public:
    explicit RectangularTable(int width, int height, QObject *parent = nullptr);
    void draw(bool active) override;
    QPair<int, int> get_capacity() override;

private:
    int width;
    int height;
};

#endif // RECTANGULARTABLE_H

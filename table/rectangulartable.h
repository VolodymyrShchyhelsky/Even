#ifndef RECTANGULARTABLE_H
#define RECTANGULARTABLE_H

#include "table.h"

class RectangularTable : public Table
{
public:
    explicit RectangularTable(int width, int height, QObject *parent = nullptr);
    void draw();

private:
    int width;
    int height;
};

#endif // RECTANGULARTABLE_H

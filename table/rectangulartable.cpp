#include "rectangulartable.h"

RectangularTable::RectangularTable(int width, int height, QObject *parent) : Table(parent), width(width), height(height)
{  
}

void RectangularTable::draw(bool active) {
    int chair_diameter = 2 * chair_radius;
    int width_in_pixels = width * chair_diameter;
    int height_in_pixels = height * chair_diameter;
    QRectF table_rect = QRectF(x, y, width_in_pixels, height_in_pixels);
    if (active) {
        addRect(table_rect, QPen(), active_brush);
    }
    else {
        addRect(table_rect);
    }
    addRect(QRectF(x, y, width_in_pixels, height_in_pixels));
    int base_x_left = x - chair_diameter;
    int base_x_right = x + width_in_pixels;
    for (int i = 0; i < height; ++i) {
        addEllipse(QRectF(base_x_left, y + i * chair_diameter, chair_diameter, chair_diameter));
        addEllipse(QRectF(base_x_right, y + i * chair_diameter, chair_diameter, chair_diameter));
    }
    int base_y_top = y - chair_diameter;
    int base_y_bottom = x + height_in_pixels;
    for (int i = 0; i < width; ++i) {
        addEllipse(QRectF(x + i * chair_diameter, base_y_top, chair_diameter, chair_diameter));
        addEllipse(QRectF(x + i * chair_diameter, base_y_bottom, chair_diameter, chair_diameter));
    }
}

QPair<int, int> RectangularTable::get_capacity() {
    return qMakePair(width, height);
}

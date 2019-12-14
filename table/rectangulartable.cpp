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
    int seated_guest_count = 0;
    for (int i = 0; i < height; ++i) {
        int left_chair_y = y + i * chair_diameter;
        addEllipse(QRectF(base_x_left, left_chair_y, chair_diameter, chair_diameter));
        if (seated_guest_count < guest_names.length()) {
            showGuestName(base_x_left, left_chair_y, seated_guest_count++);
        }
        int right_chair_y = y + i * chair_diameter;
        addEllipse(QRectF(base_x_right, right_chair_y, chair_diameter, chair_diameter));
        if (seated_guest_count < guest_names.length()) {
            showGuestName(base_x_right, right_chair_y, seated_guest_count++);
        }
    }
    int base_y_top = y - chair_diameter;
    int base_y_bottom = x + height_in_pixels;
    for (int i = 0; i < width; ++i) {
        int top_chair_x = x + i * chair_diameter;
        addEllipse(QRectF(top_chair_x, base_y_top, chair_diameter, chair_diameter));
        if (seated_guest_count < guest_names.length()) {
            showGuestName(top_chair_x, base_y_top, seated_guest_count++);
        }
        int bottom_chair_x = x + i * chair_diameter;
        addEllipse(QRectF(bottom_chair_x, base_y_bottom, chair_diameter, chair_diameter));
        if (seated_guest_count < guest_names.length()) {
            showGuestName(bottom_chair_x, base_y_bottom, seated_guest_count++);
        }
    }
}

QPair<int, int> RectangularTable::get_capacity() {
    return qMakePair(width, height);
}

int RectangularTable::get_total_capacity() {
    return width * 2 + height * 2;
}

bool RectangularTable::operator==(const RectangularTable &other) {
    return (this->width == other.width
            && this->height == other.height);
}

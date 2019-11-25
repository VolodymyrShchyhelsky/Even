#include "scheduledelegate.h"

void ScheduleDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyleOptionViewItem option_copy(option);
    if (shouldPaint(index)) {
        painter->fillRect(option_copy.rect, HAPPENING_NOW_PALETTE.window());
    }
    QStyledItemDelegate::paint(painter, option_copy, index);
}

bool ScheduleDelegate::shouldPaint(const QModelIndex &index) const {
    QPair<QDateTime, QDateTime> from_and_to = ScheduleTools::get_from_and_to(index);

    QDateTime current_time = QDateTime::currentDateTime();

    return from_and_to.first <= current_time && from_and_to.second >= current_time;
}

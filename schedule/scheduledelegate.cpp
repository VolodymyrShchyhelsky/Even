#include "scheduledelegate.h"

void ScheduleDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (index.data().canConvert<QDateTime>())
}

#include "scheduledelegate.h"

void ScheduleDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyleOptionViewItem option_copy(option);
    if (shouldPaint(index)) {
        painter->fillRect(option_copy.rect, HAPPENING_NOW_PALETTE.window());
    }
    QStyledItemDelegate::paint(painter, option_copy, index);
}

bool ScheduleDelegate::shouldPaint(const QModelIndex &index) const {
    const QSortFilterProxyModel* proxy_model = static_cast<const QSortFilterProxyModel*>(index.model());
    const QSqlTableModel * model = static_cast<const QSqlTableModel*>(proxy_model->sourceModel());
    QPair<QDateTime, QDateTime> from_and_to = ScheduleTools::get_from_and_to(proxy_model->mapToSource(index), model);

    QDateTime current_time = QDateTime::currentDateTime();

    return from_and_to.first <= current_time && from_and_to.second >= current_time;
}

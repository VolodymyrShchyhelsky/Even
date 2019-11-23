#ifndef SCHEDULEDELEGATE_H
#define SCHEDULEDELEGATE_H

#include <QStyledItemDelegate>

class ScheduleDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;
};

#endif // SCHEDULEDELEGATE_H

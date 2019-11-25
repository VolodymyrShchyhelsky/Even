#ifndef SCHEDULEDELEGATE_H
#define SCHEDULEDELEGATE_H

#include "scheduletools.h"
#include <QStyledItemDelegate>
#include <QPainter>
#include <QPalette>

class ScheduleDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    const QPalette HAPPENING_NOW_PALETTE = QPalette(QColor(128, 255, 229));

    bool shouldPaint(const QModelIndex &index) const;


};

#endif // SCHEDULEDELEGATE_H

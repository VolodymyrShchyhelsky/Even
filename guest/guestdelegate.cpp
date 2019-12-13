#include "guestdelegate.h"

GuestDelegate::GuestDelegate(QObject *parent) : QItemDelegate (parent) {

}

void GuestDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (isPresentColumn(index)) {
        drawCheck(painter, option, option.rect, index.data().toBool() ? Qt::Checked : Qt::Unchecked);
        drawFocus(painter, option, option.rect);
    }
    else {
        QItemDelegate::paint(painter, option, index);
    }
}

bool GuestDelegate::isPresentColumn(const QModelIndex &index) const {
    const QSqlTableModel * model = static_cast<const QSqlTableModel*>(index.model());
    int present_column = model->fieldIndex("present");
    return index.column() == present_column;
}

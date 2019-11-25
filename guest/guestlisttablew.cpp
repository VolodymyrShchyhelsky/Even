#include "guestlisttablew.h"

GuestListTableW::GuestListTableW(QWidget *parent) : GuestListBase(parent)
{
    visible_columns << "surname";
    GuestListBase::init();
    guest_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(guest_view, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(emitGuestId(const QModelIndex &)));
}

void GuestListTableW::emitGuestId(const QModelIndex & index) {
    QString guest_id = getId(index);
    emit seatGuest(guest_id);
}

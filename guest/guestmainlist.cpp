#include "guestmainlist.h"

GuestMainList::GuestMainList(QWidget *parent) : GuestListBase(parent)
{
    visible_columns << "id" << "surname";
    GuestListBase::init();
    connect(guest_view, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(goToGuestPage(const QModelIndex &)));
}

void GuestMainList::goToGuestPage(const QModelIndex & index) {
   // GuestPage* guest_page = new GuestPage(nullptr, getId(index));
}

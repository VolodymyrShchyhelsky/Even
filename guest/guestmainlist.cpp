#include "guestmainlist.h"

GuestMainList::GuestMainList(QWidget* guest_window, QWidget *parent) : GuestListBase(parent)
{
    this->guest_window = guest_window;
    visible_columns << "id" << "name" << "surname" << "email" << "phone";
    GuestListBase::init();
    //guest_view->setEditTriggers(QAbstractItemView::);
    connect(guest_view, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(goToGuestPage(const QModelIndex &)));
}

void GuestMainList::goToGuestPage(const QModelIndex & index) {
   GuestPage* guest_page = new GuestPage(getId(index));
   connect(guest_page, SIGNAL (guestInfoSaved()),guest_window, SLOT (showLayout()));
}

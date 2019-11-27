#include "guestmainlist.h"

GuestMainList::GuestMainList(QWidget* guest_window, QWidget *parent) : GuestListBase(parent)
{
    this->guest_window = guest_window;
    visible_columns << "id" << "surname";
    GuestListBase::init();
    //guest_view->setEditTriggers(QAbstractItemView::);
    connect(guest_view, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(goToGuestPage(const QModelIndex &)));
}

void GuestMainList::goToGuestPage(const QModelIndex & index) {
  // guest_window->hide();
  // guest_window->layout.h
   GuestPage* guest_page = new GuestPage(getId(index));
}

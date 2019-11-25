#include "guestlisttablew.h"

GuestListTableW::GuestListTableW(QWidget *parent) : GuestListBase(parent)
{
    visible_columns << "surname";
    guest_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    GuestListBase::init();
    connect(guest_view, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(getLastId(const QModelIndex &)));
}

void GuestListTableW::getLastId(const QModelIndex & index) {
    last_id = getId(index);
}
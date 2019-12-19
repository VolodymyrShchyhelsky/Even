#include "guestmainlist.h"

GuestMainList::GuestMainList(QDateTime start_time, QWidget* guest_window, QWidget *parent) : GuestListBase(parent)
{
    this->guest_window = guest_window;
    visible_columns << "id" << "name" << "surname" << "email" << "phone";
    if (start_time.isValid() && QDateTime::currentDateTime() >= start_time) {
        qDebug() << "g m l";
        if(unplaned_tag_id.isEmpty()) {
            unplaned_tag_id = DataBaseHolder::getDbHolder()->addTagEntry("Unplaned");
        }
        visible_columns << "present";
        GuestListBase::init();
        guest_view->setItemDelegate(new GuestDelegate);
    }
    else {
        qDebug() << "g m l1" << start_time;
        GuestListBase::init();
    }
    connect(guest_view, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(goToGuestPage(const QModelIndex &)));
}

GuestPage* GuestMainList::goToGuestPage(const QModelIndex & index) {
    if(index.column() != 5) {
        GuestPage* guest_page = new GuestPage(getId(index));
        connect(guest_page, SIGNAL (guestInfoUpdated()),guest_window, SLOT (showLayout()));
        return guest_page;
    } else {
        guest_model->setData(index, !index.data().toInt());
        guest_model->database().commit();
        guest_model->submitAll();
        guest_model->select();
        return nullptr;
    }
}

#include "guestlisttag.h"

GuestListTag::GuestListTag(QWidget *tagwindow ,QWidget *parent) : GuestListBase(parent)
{
    this->tagwindow = tagwindow;
    visible_columns << "surname" << "name";
    GuestListBase::init();
    guest_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(guest_view, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(getLastId(const QModelIndex &)));
}

void GuestListTag::getLastId(const QModelIndex & index) {
    QString id = getId(index);
    emit passId(id);
}

void GuestListTag::applyHide() {
    for(int i = 0; i < guest_model->rowCount(); i++) {
        QSqlRecord record = guest_model->record(i);
        QString cur_id = record.value(0).toString();
        if(hide_list.indexOf(cur_id) != -1)
            guest_view->hideRow(i);
        else
            guest_view->showRow(i);
    }
    guest_view->update();
    //guest_view->setModel(guest_model);
   // guest_view->resizeColumnsToContents();
    //TODO apply
}

#include "guestlistwindow.h"

GuestListWindow::GuestListWindow(QDateTime start_time_, QWidget *parent) : QWidget(parent), start_time(start_time_)
{
    add_new_guest_b = new QPushButton();
    add_new_guest_b->setText("Add guest");
    add_new_tag_b = new QPushButton();
    add_new_tag_b->setText("Add tag");
    connect(add_new_guest_b, SIGNAL (released()),this, SLOT (addNewGest()));
    connect(add_new_tag_b, SIGNAL (released()),this, SLOT (addTag()));

    guest_list = new GuestMainList(start_time, this);
    filter = new GuestFilter(guest_list, this);

    showLayout();
}

void GuestListWindow::showLayout() {
    guest_list->guest_model->select();
    delete layout;
    layout = new QHBoxLayout;
    QVBoxLayout* buttons_layout = new QVBoxLayout;
    buttons_layout->addWidget(filter->search_line);
    buttons_layout->addWidget(filter->search_parameter);
    buttons_layout->addWidget(filter->search_b);
    buttons_layout->addWidget(add_new_guest_b);
    buttons_layout->addWidget(add_new_tag_b);
    buttons_layout->addWidget(filter->tags_widget);
    QVBoxLayout* guest_layout = new QVBoxLayout;
    guest_layout->addWidget(guest_list->guest_view);
    layout->addLayout(guest_layout, 3);
    layout->addLayout(buttons_layout, 1);
    this->setLayout(layout);
    this->show();
}

TagWindow* GuestListWindow::addTag() {
    TagWindow* tg = new TagWindow();
    connect(tg, SIGNAL (newTagAdded()),this, SLOT (updateTag()));
    return tg;
}

void GuestListWindow::updateTag() {
    filter->initTags();
    showLayout();
}

void GuestListWindow::addNewGest() {
    QSqlTableModel * model = static_cast<QSqlTableModel*>(guest_list->guest_model);
    QSqlRecord record = model->record();
    model->insertRecord(-1, record);
    model->submitAll();
    model->select();

    if(start_time < QDateTime::currentDateTime()) {
        QModelIndex index = model->index(model->rowCount()-1,5);
        QString guest_id = model->index(model->rowCount()-1,1).data().toString();
        model->setData(index, !index.data().toInt());
        model->database().commit();
        QSqlQuery insert_tag_to_guest = QSqlQuery("insert into tagtoguest (tag_id, guest_id) values (" + guest_list->unplaned_tag_id + ", " + guest_id + ")",DataBaseHolder::getDbHolder()->getDB());
    }

    model->submitAll();
    model->select();
    emit guest_list->guest_view->clicked(model->index(model->rowCount()-1,1));
}

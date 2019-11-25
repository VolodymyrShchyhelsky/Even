#include "guestlistwindow.h"

GuestListWindow::GuestListWindow(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(600, 600);
    add_new_guest_b = new QPushButton();
    add_new_guest_b->setText("Add guest");
    add_new_tag_b = new QPushButton();
    add_new_tag_b->setText("Add tag");
    connect(add_new_guest_b, SIGNAL (released()),this, SLOT (addNewGest()));
    connect(add_new_tag_b, SIGNAL (released()),this, SLOT (addTag()));

    guest_list = new GuestMainList(this);
    filter = new GuestFilter(guest_list, this);

    showLayout();
}

void GuestListWindow::showLayout() {
    delete layout;
    layout = new QGridLayout;
    layout->addWidget(filter->search_line,0,0,1,4);
    layout->addWidget(filter->search_parameter,0,4,1,3);
    layout->addWidget(filter->search_b,0,7);
    layout->addWidget(add_new_guest_b,0,8);
    layout->addWidget(add_new_tag_b,0,9);
    layout->addWidget(guest_list, 1, 0, 5, 9);
    layout->addWidget(filter->tags_widget,1,9,5,1);
    this->setLayout(layout);
    this->show();
}

void GuestListWindow::addTag() {
    TagWindow* tg = new TagWindow();
    connect(tg, SIGNAL (newTagAdded()),this, SLOT (updateTag()));
}

void GuestListWindow::updateTag() {
   // filter->initTags();
   // layout->update();
    showLayout();
}

void GuestListWindow::addNewGest() {
    QSqlTableModel * model = static_cast<QSqlTableModel*>(guest_list->guest_model);
    QSqlRecord record = model->record();
    record.setValue("surname", "empty_surname");
    model->insertRecord(-1, record);
    model->submitAll();
    model->select();
}

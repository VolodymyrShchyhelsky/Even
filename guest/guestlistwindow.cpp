#include "guestlistwindow.h"

GuestListWindow::GuestListWindow(QWidget *parent) : QWidget(parent)
{
    add_new_guest_b = new QPushButton();
    add_new_guest_b->setText("Add guest");
    add_new_tag_b = new QPushButton();
    add_new_tag_b->setText("Add tag");

    connect(add_new_guest_b, SIGNAL (released()),this, SLOT (addNewGest()));
    connect(add_new_tag_b, SIGNAL (released()),this, SLOT (addTag()));

    this->setFixedSize(800, 1200);
    h = this->height();
    w = this->width();
    layout = new QGridLayout;
    qDebug() << "GuestListWindow 9";
    guest_list = new GuestMainList(this);
    qDebug() << "GuestListWindow 11";
    filter = new GuestFilter(guest_list, this);
    qDebug() << "GuestListWindow 13";
    //guest_list->resize(h*0.7, w*0.7);
    //guest_list->move(10, h*0.2);

    qDebug() << "GuestListWindow 15";
    layout->addWidget(filter->search_line,0,0,1,4);
    layout->addWidget(filter->search_parameter,0,4,1,3);
    layout->addWidget(filter->search_b,0,7);
    layout->addWidget(add_new_guest_b,0,8);
    layout->addWidget(add_new_tag_b,0,9);
    layout->addWidget(guest_list, 1, 0, 5, 9);
    //layout->addWidget(filter->tags_widget,1,9,5,1);
    this->setLayout(layout);
    this->show();
   // guest_list->show();
}

void GuestListWindow::addTag() {

}

void GuestListWindow::addNewGest() {
    QSqlTableModel * model = static_cast<QSqlTableModel*>(guest_list->guest_model);
    QSqlRecord record = model->record();
    record.setValue("surname", "empty_surname");
    qDebug() << model->insertRecord(-1, record);
    model->submitAll();
    model->select();
}

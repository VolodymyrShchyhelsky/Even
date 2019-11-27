#include "guestpage.h"

GuestPage::GuestPage(QString id, QWidget *parent) : QWidget(nullptr), id(id)
{
    qDebug() << "id" << id;
   // this->setFixedSize(600, 600);
    initListModel();
    initButtons();
    initTags();
    showLayout();
}

void GuestPage::initEditLayout() {
    tags_buttons = new QVBoxLayout();
    tags_buttons->addWidget(add_tag_b);
    tags_buttons->addWidget(tags_widget);
    tags_buttons->addWidget(delete_b);
}

void GuestPage::initButtons() {
    qDebug() << __func__;
    delete_b = new QPushButton("delete");
    connect(delete_b, SIGNAL (released()),this, SLOT (deleteGuest()));
    add_tag_b = new QPushButton();
    add_tag_b->setText("add_tag_b");
    connect(add_tag_b, SIGNAL (released()),this, SLOT (addTag()));
}

void GuestPage::initInfo() {
    qDebug() << __func__;
    info = new QVBoxLayout();

    QHBoxLayout* hbox;
    surname = new QLineEdit;
    surname_title = new QLineEdit;
    surname_title->setText("Surname: ");
    surname_title->setReadOnly(true);
    hbox = new QHBoxLayout();
    hbox->addWidget(surname_title);
    hbox->addWidget(surname);
    info->addLayout(hbox);

    initDataMapper();
}

void GuestPage::initTags() {
     qDebug() << __func__;
    QScrollArea* tag_scroll_area = new QScrollArea();
    qDebug() << __func__;
    tags_widget = new QWidget(tag_scroll_area);
    qDebug() << __func__;
    QVBoxLayout* tags_layout = new QVBoxLayout(tags_widget);
    tags_layout->setAlignment(Qt::AlignTop);
    QSqlQuery get_tag = QSqlQuery("select tag_id from tagtoguest where guest_id = " + id, DataBaseHolder::getDbHolder()->getDB());
    qDebug() << __func__;
    while(get_tag.next()) {
         qDebug() << "in while 1";
         QString tag_id = get_tag.value(0).toString();
         QSqlQuery get_tag_name = QSqlQuery("select name from tag where id = " + tag_id, DataBaseHolder::getDbHolder()->getDB());
         get_tag_name.next();
         qDebug() << "in while 1";
         QString tag_name = get_tag_name.value(0).toString();
         DescriptionButton* del = new DescriptionButton(tag_id, "del");
         connect(del, SIGNAL(descriptionSignal(QString)),
                 this, SLOT(deleteTag(QString)));
         qDebug() << "in while 1";
         QHBoxLayout* hbox = new QHBoxLayout();
         QLineEdit* tag_name_line = new QLineEdit();
         tag_name_line->setText(tag_name);
         tag_name_line->setReadOnly(true);
         hbox->addWidget(tag_name_line);
         hbox->addWidget(del);
         tags_layout->addLayout(hbox);
         qDebug() << "in while 1";
    }
}

void GuestPage::deleteTag(QString tag_id) {
    qDebug() << __func__;
    QSqlQuery del_tag = QSqlQuery("delete from tagtoguest where guest_id = " + id + " and tag_id = " + tag_id, DataBaseHolder::getDbHolder()->getDB());
    delete tags_widget;
    qDebug() << __func__;
    initTags();
    showLayout();

}

void GuestPage::showLayout() {
    qDebug() << __func__;
    delete layout;
    layout = new QHBoxLayout;
    initEditLayout();
    initInfo();
    layout->addLayout(info);
    layout->addLayout(tags_buttons);
    qDebug() << __func__;
    this->setLayout(layout);
    qDebug() << __func__;
    this->show();
}

void GuestPage::initDataMapper() {
    qDebug() << __func__;
    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(user_list_model);
    mapper->addMapping(surname, 1);
    mapper->toFirst();
}

void GuestPage::initListModel() {
    qDebug() << __func__;
    user_list_model = new QSqlTableModel(nullptr, DataBaseHolder::getDbHolder()->getDB());
    user_list_model->setTable("guest");
    user_list_model->setFilter(QString("id = %1").arg(id));
    user_list_model->select();
}

void GuestPage::deleteGuest() {
    qDebug() << __func__;
    QSqlQuery del = QSqlQuery("delete from guest where id = " + id, DataBaseHolder::getDbHolder()->getDB());
    del.exec();
    del = QSqlQuery("delete from tagtoguest where guest_id = " + id, DataBaseHolder::getDbHolder()->getDB());
    del.exec();
    del = QSqlQuery("delete from tabletoguest where guest_id = " + id, DataBaseHolder::getDbHolder()->getDB());
    del.exec();
    this->close();
}

void GuestPage::addTag() {
    AddTagWindow* tag_w = new AddTagWindow(id);
    //initTags();
    //showLayout();
}


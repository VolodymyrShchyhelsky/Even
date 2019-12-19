#include "guestpage.h"
#include <QMessageBox>

GuestPage::GuestPage(QString id, QWidget *parent) : QWidget(parent), id(id)
{
    this->setFixedSize(600, 300);
    initListModel();
    initButtons();
    initTags();
    showLayout();
}

void GuestPage::initEditLayout() {
    tags_buttons = new QVBoxLayout();
    tags_buttons->addWidget(add_tag_b);
    tags_buttons->addWidget(tag_scroll_area);
    tags_buttons->addWidget(save_b);
    tags_buttons->addWidget(delete_b);
}

void GuestPage::initButtons() {
    delete_b = new QPushButton("Delete");
    connect(delete_b, SIGNAL (released()),this, SLOT (deleteGuest()));
    add_tag_b = new QPushButton("Add tag");
    connect(add_tag_b, SIGNAL (released()),this, SLOT (addTag()));
    save_b = new QPushButton("Save");
    connect(save_b, SIGNAL (released()),this, SLOT (save()));
}

bool GuestPage::save() {
    QString error_message = "";
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    QRegExp phoneREX("^\\+[1-9]{1}[0-9]{3,14}$");

    if(!mailREX.exactMatch(email->text())) {
        error_message = "Invalid email";
    }
    if(!phoneREX.exactMatch(phone->text())) {
        error_message = "Invalid phone";
    }
    if(name->text().isEmpty()) {
        error_message = "Name is empty";
    }
    if(surname->text().isEmpty()) {
        error_message = "Surname is empty";
    }
    if(!error_message.isEmpty()) {
        QMessageBox::warning(nullptr, "Fail", error_message);
        return false;
    }

    mapper->submit();
    this->close();
    emit guestInfoUpdated();
    return true;
}

void GuestPage::initInfo() {

    info = new QVBoxLayout();
    QSpacerItem* spacer = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QHBoxLayout* hbox_name = new QHBoxLayout();
    name_title = new QLabel("Name: ");
    info->addWidget(name_title);
    info->addWidget(name);

    QHBoxLayout* hbox_surname = new QHBoxLayout();
    surname_title = new QLabel("Surname: ");
    info->addWidget(surname_title);
    info->addWidget(surname);

    QHBoxLayout* hbox_phone = new QHBoxLayout();
    phone_title = new QLabel("Phone: ");
    info->addWidget(phone_title);
    info->addWidget(phone);

    QHBoxLayout* hbox_email = new QHBoxLayout();
    email_title = new QLabel("Email: ");
    info->addWidget(email_title);
    info->addWidget(email);
    info->addSpacerItem(spacer);
    initDataMapper();
}

void GuestPage::initTags() {
    tag_scroll_area = new QScrollArea();
    tags_widget = new QWidget();
    QVBoxLayout* tags_layout = new QVBoxLayout(tags_widget);
    tag_scroll_area->setWidget(tags_widget);
    tag_scroll_area->setWidgetResizable(true);

    //tags_layout->setAlignment(Qt::AlignTop);
    QSqlQuery get_tag = QSqlQuery("select tag_id from tagtoguest where guest_id = " + id, DataBaseHolder::getDbHolder()->getDB());
    while(get_tag.next()) {
         QString tag_id = get_tag.value(0).toString();
         QSqlQuery get_tag_name = QSqlQuery("select name from tag where id = " + tag_id, DataBaseHolder::getDbHolder()->getDB());
         get_tag_name.next();
         QString tag_name = get_tag_name.value(0).toString();
         DescriptionButton* del = new DescriptionButton(tag_id, "del");
         connect(del, SIGNAL(descriptionSignal(QString)),
                 this, SLOT(deleteTag(QString)));
         QHBoxLayout* hbox = new QHBoxLayout();
         //hbox->setS
         QLineEdit* tag_name_line = new QLineEdit();
         tag_name_line->setText(tag_name);
         tag_name_line->setReadOnly(true);
         hbox->addWidget(tag_name_line);
         hbox->addWidget(del);
         tags_layout->addLayout(hbox);
    }
}

void GuestPage::deleteTag(QString tag_id) {
    QSqlQuery del_tag = QSqlQuery("delete from tagtoguest where guest_id = " + id + " and tag_id = " + tag_id, DataBaseHolder::getDbHolder()->getDB());
    updateTags();
}

void GuestPage::updateTags() {
    delete tags_widget;
    initTags();
    showLayout();
}

void GuestPage::showLayout() {

    delete layout;
    layout = new QHBoxLayout;
    initEditLayout();
    initInfo();
    layout->addLayout(info);
    layout->addLayout(tags_buttons);

    this->setLayout(layout);

    this->show();
}

void GuestPage::initDataMapper() {

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    mapper->setModel(user_list_model);
    mapper->addMapping(name, 1);
    mapper->addMapping(surname, 2);
    mapper->addMapping(email, 3);
    mapper->addMapping(phone, 4);
    mapper->toFirst();
}

void GuestPage::initListModel() {

    user_list_model = new QSqlTableModel(nullptr, DataBaseHolder::getDbHolder()->getDB());
    user_list_model->setTable("guest");
    user_list_model->setFilter(QString("id = %1").arg(id));
    user_list_model->select();
}

void GuestPage::deleteGuest() {

    QSqlQuery del = QSqlQuery("delete from guest where id = " + id, DataBaseHolder::getDbHolder()->getDB());
    del.exec();
    del = QSqlQuery("delete from tagtoguest where guest_id = " + id, DataBaseHolder::getDbHolder()->getDB());
    del.exec();
    del = QSqlQuery("delete from tabletoguest where guest_id = " + id, DataBaseHolder::getDbHolder()->getDB());
    del.exec();
    this->close();
    emit guestInfoUpdated();
}

void GuestPage::addTag() {
    AddTagWindow* tag_w = new AddTagWindow(id, this);
    tag_w->setAttribute( Qt::WA_DeleteOnClose );
    connect( tag_w, SIGNAL(destroyed(QObject*)), this, SLOT(updateTags()) );
    //initTags();
    //showLayout();
}


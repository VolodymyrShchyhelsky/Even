#include "tagwindow.h"

TagWindow::TagWindow(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(800, 800);
    name_l = new QLineEdit;
    initButtons();
    initLists();
    showTagW();
}

void TagWindow::showTagW() {
    layout = new QGridLayout;
    layout->addWidget(save_b, 0 ,0);
    layout->addWidget(name_l, 0, 1, 1, 4);
    layout->addWidget(discard_b, 0 ,4);
    layout->addWidget(without_tag, 1 ,0, 4, 4);
    layout->addWidget(with_tag, 1 ,4, 4, 4);
    this->setLayout(layout);
    this->show();
}

void TagWindow::initButtons() {
    save_b = new QPushButton;
    save_b->setText("save");
    discard_b = new QPushButton;
    discard_b->setText("discard");
    connect(save_b, SIGNAL (released()),this, SLOT (save()));
    connect(discard_b, SIGNAL (released()),this, SLOT (discard()));
}

void TagWindow::applyHide() {
    with_tag->applyHide();
    without_tag->applyHide();
}

void TagWindow::initLists() {
    with_tag = new GuestListTag(this);
    without_tag = new GuestListTag(this);
    QSqlQuery get_ids = QSqlQuery("select id from guest", DataBaseHolder::getDbHolder()->getDB());
    get_ids.exec();
    QStringList ids;
    while (get_ids.next()) {
         QString id = get_ids.value(0).toString();
         ids.append(id);
    }
    with_tag->hide_list = ids;
    connect(with_tag, SIGNAL (passId(QString)),this, SLOT (getIdFromWith(QString)));
    connect(without_tag, SIGNAL (passId(QString)),this, SLOT (getIdFromWithout(QString)));
    applyHide();
}

void TagWindow::getIdFromWith(QString id) {
    without_tag->hide_list.removeOne(id);
    with_tag->hide_list.append(id);
    applyHide();
}

void TagWindow::getIdFromWithout(QString id) {
    with_tag->hide_list.removeOne(id);
    without_tag->hide_list.append(id);
    applyHide();
}

void TagWindow::save() {
    QString name = name_l->text();
    if(name.isEmpty()) {
        return;
    }
    QSqlQuery insert_tag = QSqlQuery("insert into tag (name) values('" + name + "')", DataBaseHolder::getDbHolder()->getDB());
    QString tag_id = insert_tag.lastInsertId().toString();
    for(auto guest_id : without_tag->hide_list) {
        QSqlQuery insert_tag_to_guest = QSqlQuery("insert into tagtoguest (tag_id, guest_id) values (" + tag_id + ", " + guest_id + ")",DataBaseHolder::getDbHolder()->getDB());
    }
    this->close();
    emit newTagAdded();
}

void TagWindow::discard() {
    this->close();
}



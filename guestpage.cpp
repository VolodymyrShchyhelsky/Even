#include "guestpage.h"

GuestPage::GuestPage(QWidget *parent, QString id) : QWidget(parent), id(id)
{
    this->setFixedSize(600, 600);
    initListModel();
    initListView();
    this->show();
//    QString str = age_text->text();
//    qDebug() << "HERE " << str;
}

void GuestPage::initListView() {

    for(int i = 1; i< 5; ++i) {
        QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
        mapper->setModel(user_list_model);
        QLineEdit* age_text = new QLineEdit(this);
        //age_text->setFixedSize(100, 100);
        age_text->move(20, i * 20);
        mapper->addMapping(age_text, 0);
        age_text->show();
       // mapper->toFirst();
        mapper->setCurrentIndex(i);
//        mapper->submit();
//        mapper->toNext();
    }

//    user_list_view = new QTableView();
//    user_list_view->setModel(proxy_model);
//    user_list_view->show();
}

void GuestPage::initListModel() {
    db = new DataBaseHolder();
    user_list_model = new QSqlTableModel(nullptr, db->getDB());
    user_list_model->setTable("person");
   // user_list_model->setFilter(QString("id = %1").arg(id));
    user_list_model->select();
//    proxy_model = new Horizontal_proxy_model();
//    proxy_model->setSourceModel(user_list_model);
}


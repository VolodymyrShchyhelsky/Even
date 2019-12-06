#include "addtagwindow.h"

AddTagWindow::AddTagWindow(QString id, QWidget *parent) : QWidget(nullptr)
{
    this->id = id;
    model = new QSqlTableModel(nullptr, DataBaseHolder::getDbHolder()->getDB());
    model->setTable("tag");
    initListModel();
    initListView();
    this->show();
}

void AddTagWindow::initListModel() {
    model->setFilter("id not in (select tag_id from tagtoguest where guest_id =" + id + ")");
    model->select();
}

void AddTagWindow::initListView() {
    view = new QTableView(this);
    view->setModel(model);
    view->show();
    connect(view, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(addTag(const QModelIndex &)));
}

void AddTagWindow::addTag(const QModelIndex & index) {
    int idColumn = model->fieldIndex("id");
    if(index.isValid()) {
        int row = index.row();
        QModelIndex id_index = model->index(row, idColumn);
        if(id_index.isValid()) {
            QString tag_id = id_index.data().toString();
            QSqlQuery insert_tag_to_guest = QSqlQuery("insert into tagtoguest (tag_id, guest_id) values (" + tag_id + ", " + id + ")",DataBaseHolder::getDbHolder()->getDB());
            initListModel();
        }
    }
}

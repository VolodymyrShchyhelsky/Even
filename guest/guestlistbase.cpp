#include "guestlistbase.h"

GuestListBase::GuestListBase(QWidget *parent) : QWidget(parent)
{
}

void GuestListBase::init() {
    initModel();
    initListView();
}

void GuestListBase::initListView() {
    guest_view = new QTableView(this);
    guest_view->setModel(guest_model);
    configureView();
}

void GuestListBase::configureView() {
    QList< int > visible_indexes;
    for(auto str : visible_columns) {
        visible_indexes.append(guest_model->fieldIndex(str));
    }
    for(int i = 0; i < guest_model->columnCount(); ++i) {
        if(visible_indexes.indexOf(i) == -1) {
            guest_view->hideColumn(i);
        }
    }
}

void GuestListBase::initModel() {
    guest_model = new QSqlTableModel(nullptr, db->getDB());
    guest_model->setTable("guest");
//    int surnameColumn = guest_model->fieldIndex("surname");
//    guest_model->sort(surnameColumn, Qt::AscendingOrder);
    applyFilters();
}

void GuestListBase::applyFilters(QString filter) {
    if (basic_filter != "") {
        if(filter != "") {
            filter += " and ";
        }
        filter += basic_filter;
    }
    guest_model->setFilter(filter);
    guest_model->select();
}

QString GuestListBase::getId(const QModelIndex &index) {
    int idColumn = guest_model->fieldIndex("id");
    if(index.isValid()) {
        int row = index.row();
        QModelIndex id_index = guest_model->index(row, idColumn);
        if(id_index.isValid()) {
            QString cellText = id_index.data().toString();
            return cellText;
        }
    }
    return "";
}

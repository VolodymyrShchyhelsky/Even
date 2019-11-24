#include "userlistwidget.h"

UserListWidget::UserListWidget(QWidget *parent) : QWidget(parent)
{
    initListModel();
    initListView();
}

void UserListWidget::initListView() {
    user_list_view = new QTableView();
    user_list_view->setModel(user_list_model);
    user_list_view->show();

    connect(user_list_view, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(getIndex(const QModelIndex &)));
}

void UserListWidget::initListModel() {
    db = DataBaseHolder::getDbHolder();
    user_list_model = new QSqlTableModel(nullptr, db->getDB());
    user_list_model->setTable("guest");
    user_list_model->select();
}

void UserListWidget::getIndex(const QModelIndex &index) {
    int idColumn = user_list_model->fieldIndex("id");
    if(index.isValid()) {
        int row = index.row();

        QModelIndex id_index = user_list_model->index(row, idColumn);
        if(id_index.isValid()) {
            QString cellText = id_index.data().toString();
            GuestPage* guest_page = new GuestPage(nullptr, cellText);
            qDebug() << cellText << " <<<<";
        } else  {
            qDebug() << "Jopa";
        }
    }
}

#include "todowindow.h"

Todo::Todo(QString id, QString father_id, QString name, QString is_active) {
    this->id = id;
    this->father_id = father_id;
    this->name = name;
    this->is_active = is_active;
}

TodoWindow::TodoWindow(QWidget *parent) : QWidget(parent)
{
    this->setMinimumSize(600,600);
    active_b = new QCheckBox("Show complete todos");
    not_active_b = new QCheckBox("Show incomplete todos");
    active_b->setCheckState(Qt::Checked);
    not_active_b->setCheckState(Qt::Checked);
    connect(active_b, SIGNAL(stateChanged(int)), this, SLOT(initLayout()));
    connect(not_active_b, SIGNAL(stateChanged(int)), this, SLOT(initLayout()));
    initLayout();
}

void TodoWindow::initLayout() {
    delete layout;
    layout = new QVBoxLayout();
    initButtons();
    initView();
    layout->addLayout(buttons_layout);
    layout->addWidget(view);
    this->setLayout(layout);
    this->show();
}

void TodoWindow::initButtons() {
    add_b = new QPushButton("Add sub task");
    add_global_todo = new QPushButton("Add global todo");
    remove_b = new QPushButton("Delete todo");
    connect(add_b, SIGNAL (released()),this, SLOT (addNew()));
    connect(remove_b, SIGNAL (released()),this, SLOT (remove()));
    connect(add_global_todo, SIGNAL (released()),this, SLOT (addGlobalTodo()));
    buttons_layout = new QHBoxLayout;
    buttons_layout->addWidget(add_b);
    buttons_layout->addWidget(add_global_todo);
    buttons_layout->addWidget(remove_b);
    buttons_layout->addWidget(active_b);
    buttons_layout->addWidget(not_active_b);
}

void TodoWindow::addGlobalTodo() {
    QSqlQuery insert = QSqlQuery("insert into todo(father_id) values(0)", DataBaseHolder::getDbHolder()->getDB());
    initLayout();
}

void TodoWindow::addNew() {
    QTreeWidgetItem * cur_item = view->currentItem();
    if(cur_item) {
        QString futher_id = cur_item->text(0);
        QSqlQuery insert = QSqlQuery("insert into todo(father_id) values(" + futher_id + ")", DataBaseHolder::getDbHolder()->getDB());
        initLayout();
    }
}

void TodoWindow::remove() {
    QTreeWidgetItem * cur_item = view->currentItem();
    if(cur_item) {
        QString id = cur_item->text(0);
        QSqlQuery remove = QSqlQuery("delete from todo where id == " + id);
        initLayout();
    }
}

void TodoWindow::finishEditing() {
    QTreeWidgetItem * cur_item = view->currentItem();
    if(cur_item) {
        QString id = cur_item->text(0);
        QLineEdit* line_edit = dynamic_cast<QLineEdit*>(view->itemWidget(cur_item, 1));
        QString new_name = line_edit->text();
        QSqlQuery update_name = QSqlQuery("update todo set name='" + new_name + "'where id=" + id, DataBaseHolder::getDbHolder()->getDB());
        initLayout();
    }
}

void TodoWindow::initView() {
    getTodosFromDb();
    view = new QTreeWidget();
    view->setMouseTracking(true);
//    connect(view, SIGNAL(itemEntered(QTreeWidgetItem*, int)),
//            this, SLOT(setActive(QTreeWidgetItem*)));
    QStringList columnNames;
    columnNames << "Id" << "Name" << "Status";
    view->setHeaderLabels(columnNames);
    //view->hideColumn(0);
    view->addTopLevelItems(getTodoChildren("0"));
    view->expandAll();
    initItemsStatus();
}

void TodoWindow::setActive(QTreeWidgetItem *item) {
    qDebug() << "in set active";
    view->setCurrentItem(item);
}

void TodoWindow::initItemsStatus() {
    for(QTreeWidgetItem * item : all_todo_items) {
        QLineEdit* name_line = new QLineEdit(item->text(1));
        connect(name_line, SIGNAL(editingFinished()), this, SLOT(finishEditing()));
        view->setItemWidget(item, 1, name_line);
        QCheckBox* check_box = new QCheckBox();
        if(item->text(2) == "0") {
            check_box->setCheckState(Qt::Unchecked);
        } else {
            check_box->setCheckState(Qt::Checked);
        }
        connect(check_box, SIGNAL(stateChanged(int)), this, SLOT(changeState(int)));
        view->setItemWidget(item, 2, check_box);
    }
}

void TodoWindow::changeState(int state) {
    QTreeWidgetItem * cur_item = view->currentItem();
    QString id = cur_item->text(0);
    QSqlQuery get_todos = QSqlQuery("update todo set status=" + QString::number(state) + " where id=" + id, DataBaseHolder::getDbHolder()->getDB());
    initLayout();
}

QList<QTreeWidgetItem *> TodoWindow::getTodoChildren(QString db_id) {
    QList<QTreeWidgetItem *> children_list;
    for(Todo todo : todos) {
        if(todo.father_id == db_id) {
            QTreeWidgetItem* item = new QTreeWidgetItem(QStringList{todo.id, todo.name, todo.is_active});
            QList<QTreeWidgetItem *> cur_todo_children = getTodoChildren(todo.id);
            item->addChildren(cur_todo_children);
            if(cur_todo_children.length() || (todo.is_active == "0" && not_active_b->checkState() == Qt::Checked) ||
                (todo.is_active == "2" && active_b->checkState() == Qt::Checked))
                children_list.append(item);
            all_todo_items.append(item);
        }
    }
    return children_list;
}

void TodoWindow::getTodosFromDb() {
    todos.clear();
    all_todo_items.clear();
    QSqlQuery get_todos = QSqlQuery("select * from todo", DataBaseHolder::getDbHolder()->getDB());
    while(get_todos.next()) {
        QString id = get_todos.value(0).toString();
        QString father_id = get_todos.value(1).toString();
        QString name = get_todos.value(2).toString();
        QString status = get_todos.value(3).toString();
        todos.append(Todo(id, father_id, name, status));
    }
}

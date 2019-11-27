#ifndef TODOWINDOW_H
#define TODOWINDOW_H

#include <QObject>
#include <QWidget>
#include <QTreeWidget>
#include <QWidget>
#include <QString>
#include <QTableView>
#include <QSqlTableModel>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QLineEdit>
#include <QDataWidgetMapper>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QScrollArea>
#include <database/databaseholder.h>

class Todo {
public:
    Todo(QString, QString, QString, QString);
    QString id;
    QString father_id;
    QString name;
    QString is_active;
};

class TodoWindow : public QWidget
{
    Q_OBJECT
public:
    explicit TodoWindow(QWidget *parent = nullptr);

signals:

public slots:
    void addNew();
    void addGlobalTodo();
    void editName();
    void finishEditing();
    void changeState(int);
    void initLayout();

private:
    QVBoxLayout* layout = nullptr;
    QHBoxLayout* buttons_layout = nullptr;

    QList<QTreeWidgetItem *> all_todo_items;
    QList< Todo > todos;
    void getTodosFromDb();
    void initItemsStatus();
    QList<QTreeWidgetItem *> getTodoChildren(QString db_id);
    void initView();
    void initButtons();
    QTreeWidget* view = nullptr;

    QPushButton* add_b;
    QPushButton* add_global_todo;
    QPushButton* edit;
    QCheckBox* active_b;
    QCheckBox* not_active_b;
};

#endif // TODOWINDOW_H

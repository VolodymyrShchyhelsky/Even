#ifndef ADDTAGWINDOW_H
#define ADDTAGWINDOW_H

#include <QWidget>
#include <QWidget>
#include <QString>
#include <QTableView>
#include <QSqlTableModel>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QLineEdit>
#include <QDataWidgetMapper>
#include "database/databaseholder.h"
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QScrollArea>

#include "database/databaseholder.h"

class AddTagWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AddTagWindow(QString id, QWidget *parent = nullptr);

signals:


public slots:
    void addTag(const QModelIndex &index);

private:
    QString id;
    QTableView* view;
    QSqlTableModel* model;

    void initListView();
    void initListModel();
};

#endif // ADDTAGWINDOW_H
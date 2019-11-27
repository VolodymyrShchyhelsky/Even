#ifndef GUESTPAGE_H
#define GUESTPAGE_H

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
#include "addtagwindow.h"
#include "general/descriptionbutton.h"

class GuestPage : public QWidget
{
    Q_OBJECT
public:
    explicit GuestPage(QString id, QWidget *parent = nullptr);

signals:

public slots:
    void deleteGuest();
    void addTag();
    void deleteTag(QString id);

private:
    QTableView* user_list_view;
    QSqlTableModel* user_list_model;
    QVBoxLayout* info;
    QString id;
    QList< QPair<QPushButton*, QString> > tags;
    QPushButton* delete_b;
    QPushButton* add_tag_b;
    QWidget* tags_widget = nullptr;
    QHBoxLayout* layout = nullptr;
    QVBoxLayout* tags_buttons = nullptr;
    QLineEdit* surname_title;
    QLineEdit* surname;

    void initDataMapper();
    void initListModel();
    void initEditLayout();

    void initButtons();
    void initInfo();
    void initTags();
    void showLayout();
};

#endif // GUESTPAGE_H

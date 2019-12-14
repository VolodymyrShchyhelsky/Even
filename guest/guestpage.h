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
#include <QLabel>
#include "addtagwindow.h"
#include "general/descriptionbutton.h"

class GuestPage : public QWidget
{
    Q_OBJECT
public:
    explicit GuestPage(QString id, QWidget *parent = nullptr);

signals:
    void guestInfoUpdated();

public slots:
    void deleteGuest();
    void addTag();
    void deleteTag(QString id);
    void save();
    void updateTags();

private:
    QDataWidgetMapper *mapper;
    QSqlTableModel* user_list_model;
    QVBoxLayout* info;
    QString id;
    QList< QPair<QPushButton*, QString> > tags;
    QPushButton* delete_b;
    QPushButton* add_tag_b;
    QPushButton* save_b;
    QWidget* tags_widget = nullptr;
    QHBoxLayout* layout = nullptr;
    QVBoxLayout* tags_buttons = nullptr;
    QScrollArea* tag_scroll_area;

    //QLineEdit* surname_title;
    QLabel* surname_title;
    QLabel* name_title;
    QLabel* phone_title;
    QLabel* email_title;

    QLineEdit* surname = new QLineEdit;
    QLineEdit* name = new QLineEdit;
    QLineEdit* phone = new QLineEdit;
    QLineEdit* email = new QLineEdit;

    void initDataMapper();
    void initListModel();
    void initEditLayout();

    void initButtons();
    void initInfo();
    void initTags();
    void showLayout();
};

#endif // GUESTPAGE_H

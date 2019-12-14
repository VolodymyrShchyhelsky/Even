#ifndef GuestFilter_H
#define GuestFilter_H

#include <QObject>
#include <QWidget>
#include "guestlistbase.h"
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QScrollArea>

class GuestFilter : public QWidget
{
    Q_OBJECT
public:
    explicit GuestFilter(GuestListBase* guest_list, QWidget *parent = nullptr);
    QHBoxLayout* createTableWLayout();
    GuestListBase* guest_list;

    QComboBox* search_parameter;
    QLineEdit* search_line;
    QPushButton* uncheck_b;
    QPushButton* search_b;

    QWidget* tags_widget = nullptr;
    QList< QPair<QCheckBox*, QString> > tags;
    void initTags();
   // void init();
signals:

public slots:
    void search();
    void deleteTag(QString tag_id);
private:
    void initSearchLine();
    friend class TestGuestFilter;


};

#endif // GuestFilter_H

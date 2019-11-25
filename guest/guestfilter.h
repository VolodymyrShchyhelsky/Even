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
    GuestListBase* guest_list;

    QComboBox* search_parameter;
    QLineEdit* search_line;
    QPushButton* uncheck_b;
    QPushButton* search_b;

    QScrollArea* tag_scroll_area;
    QWidget* tags_widget;
    QVBoxLayout* tags_layout;
    QList< QPair<QCheckBox*, QString> > tags;
   // void init();
signals:

public slots:
    void search();
private:
    void initSearchLine();
    void initTags();


};

#endif // GuestFilter_H

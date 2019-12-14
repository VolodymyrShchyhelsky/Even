#ifndef TAGWINDOW_H
#define TAGWINDOW_H

#include "guestlisttag.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class TagWindow : public QWidget
{
    Q_OBJECT
public:
    explicit TagWindow(QWidget *parent = nullptr);

signals:
    void newTagAdded();

public slots:
    void getIdFromWith(QString);
    void getIdFromWithout(QString);
    void save();
    void discard();

private:
    friend class TestTagWindow;

    void showTagW();
    void initButtons();
    void initLists();
    void applyHide();

    QPushButton* save_b;
    QPushButton* discard_b;
    QLineEdit* name_l;
    GuestListTag* with_tag;
    GuestListTag* without_tag;
    QGridLayout* layout;
};

#endif // TAGWINDOW_H

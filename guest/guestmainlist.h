#ifndef GUESTMAINLIST_H
#define GUESTMAINLIST_H

#include "guestlistbase.h"

class GuestMainList : public GuestListBase
{
    Q_OBJECT
public:
    virtual ~GuestMainList() {};
    explicit GuestMainList(QWidget* guest_window, QWidget *parent = nullptr);

signals:

public slots:
    void goToGuestPage(const QModelIndex &index);

private:
    QWidget* guest_window;
};

#endif // GUESTMAINLIST_H

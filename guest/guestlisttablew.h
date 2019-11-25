#ifndef GUESTLISTTABLEW_H
#define GUESTLISTTABLEW_H

#include "guestlistbase.h"

class GuestListTableW : public GuestListBase
{
    Q_OBJECT
public:
    virtual ~GuestListTableW() {}
    explicit GuestListTableW(QWidget *parent = nullptr);

signals:
    void seatGuest(QString guest_id);

public slots:
    void emitGuestId(const QModelIndex &index);

private:
    const QString basic_filter = "id in (select guest_id from tabletoguest)";
};


#endif // GUESTLISTTABLEW_H

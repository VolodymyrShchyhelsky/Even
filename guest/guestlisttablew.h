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
    void updateModel();

};


#endif // GUESTLISTTABLEW_H

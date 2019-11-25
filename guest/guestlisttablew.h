#ifndef GUESTLISTTABLEW_H
#define GUESTLISTTABLEW_H

#include "guestlistbase.h"

class GuestListTableW : public GuestListBase
{
    Q_OBJECT
public:
    virtual ~GuestListTableW() {};
    explicit GuestListTableW(QWidget *parent = nullptr);

    QString last_id;

signals:

public slots:
    void getLastId(const QModelIndex &index);

private:
    const QString basic_filter = "id in (select guest_id from tabletoguest)";
};


#endif // GUESTLISTTABLEW_H

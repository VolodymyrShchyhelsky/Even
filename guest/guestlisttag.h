#ifndef GUESTLISTTAG_H
#define GUESTLISTTAG_H

#include "guestlistbase.h"

class GuestListTag : public GuestListBase
{
    Q_OBJECT
public:
    virtual ~GuestListTag() {};
    explicit GuestListTag(QWidget* tagwindow, QWidget *parent = nullptr);

    QStringList hide_list = {};
    QWidget* tagwindow;
    void applyHide();

signals:
    void passId(QString id);

public slots:
    void getLastId(const QModelIndex &index);
};

#endif // GUESTLISTTAG_H

#ifndef TABLECREATIONWIDGET_H
#define TABLECREATIONWIDGET_H

#include <QWidget>
#include <QFormLayout>
#include "table.h"

class TableCreationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TableCreationWidget(QWidget *parent = nullptr);
    virtual Table* createTable() = 0;

signals:

public slots:
};

#endif // TABLECREATIONWIDGET_H

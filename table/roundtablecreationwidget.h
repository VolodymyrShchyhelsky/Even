#ifndef ROUNDTABLECREATIONWIDGET_H
#define ROUNDTABLECREATIONWIDGET_H

#include "tablecreationwidget.h"
#include <QSpinBox>
#include "roundtable.h"

class RoundTableCreationWidget : public TableCreationWidget
{
public:
    explicit RoundTableCreationWidget(QWidget *parent = nullptr);
    Table* createTable();

private:
    QSpinBox * num_of_guests_box;
};

#endif // ROUNDTABLECREATIONWIDGET_H

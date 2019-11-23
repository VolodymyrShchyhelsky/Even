#ifndef RECTANGULARTABLECREATIONWIDGET_H
#define RECTANGULARTABLECREATIONWIDGET_H

#include "tablecreationwidget.h"
#include <QSpinBox>
#include "rectangulartable.h"

class RectangularTableCreationWidget : public TableCreationWidget
{
public:
    explicit RectangularTableCreationWidget(QWidget *parent = nullptr);
    Table* createTable();

private:
    QSpinBox * width_box;
    QSpinBox * height_box;
};

#endif // RECTANGULARTABLECREATIONWIDGET_H

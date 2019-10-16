#include "rectangulartablecreationwidget.h"

RectangularTableCreationWidget::RectangularTableCreationWidget(QWidget *parent) : TableCreationWidget(parent)
{
    width_box = new QSpinBox(this);
    width_box->setMinimum(1);
    height_box = new QSpinBox(this);
    height_box->setMinimum(1);
    QFormLayout * layout = new QFormLayout;
    layout->addRow("Width:", width_box);
    layout->addRow("Height:", height_box);
    setLayout(layout);
}

Table* RectangularTableCreationWidget::createTable() {
    return new RectangularTable(width_box->value(), height_box->value(), parent());
}

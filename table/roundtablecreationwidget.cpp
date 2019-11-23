#include "roundtablecreationwidget.h"

RoundTableCreationWidget::RoundTableCreationWidget(QWidget *parent) : TableCreationWidget(parent)
{
    num_of_guests_box = new QSpinBox(this);
    num_of_guests_box->setMinimum(1);
    QFormLayout * layout = new QFormLayout;
    layout->addRow("Number of seats:", num_of_guests_box);
    setLayout(layout);
}

Table* RoundTableCreationWidget::createTable() {
    return new RoundTable(num_of_guests_box->value(), parent());
}

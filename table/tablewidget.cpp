#include "tablewidget.h"

TableWidget::TableWidget(QWidget *parent) : QWidget(parent)
{
    seating_handler = new SeatingHandler(this);

    round_table_button = new QRadioButton("Round", this);
    round_table_button->setChecked(true);
    connect(round_table_button, SIGNAL(clicked()), this, SLOT(roundTableChosen()));
    rectangular_table_button = new QRadioButton("Rectangular", this);
    connect(rectangular_table_button, SIGNAL(clicked()), this, SLOT(rectangularTableChosen()));

    round_table_creation_widget = new RoundTableCreationWidget(this);
    rectangular_table_creation_widget = new RectangularTableCreationWidget(this);
    table_creation_widgets = new QStackedWidget(this);
    table_creation_widgets->addWidget(round_table_creation_widget);
    table_creation_widgets->addWidget(rectangular_table_creation_widget);

    add_table_button = new QPushButton("ADD TABLE", this);
    connect(add_table_button, SIGNAL(clicked()),
            seating_handler, SLOT(addTable()));
    delete_table_button = new QPushButton("DELETE TABLE", this);
    connect(delete_table_button, SIGNAL(clicked()),
            seating_handler, SLOT(deleteTable()));
    save_layout_button = new QPushButton("SAVE LAYOUT", this);
    connect(save_layout_button, SIGNAL(clicked()), this, SLOT(saveLayout()));

    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(round_table_button);
    layout->addWidget(rectangular_table_button);
    layout->addWidget(table_creation_widgets);
    layout->addWidget(add_table_button);
    layout->addWidget(delete_table_button);
    layout->addWidget(save_layout_button);

    table_box = new QGroupBox(this);
    table_box->setLayout(layout);

    connect(this, SIGNAL(addTable(Table*)),
            seating_handler, SLOT(addTable(Table*)));
}

void TableWidget::roundTableChosen() {
    table_creation_widgets->setCurrentWidget(round_table_creation_widget);
}

void TableWidget::rectangularTableChosen() {
    table_creation_widgets->setCurrentWidget(rectangular_table_creation_widget);
}

void TableWidget::addTable() {
    TableCreationWidget * table_creation_widget = dynamic_cast<TableCreationWidget*>(table_creation_widgets->currentWidget());
    Table * table = table_creation_widget->createTable();
    emit addTable(table);
    TableView * view = new TableView(table, this);
    connect(view, SIGNAL(tableChosen(TableView*)),
            seating_handler, SLOT(setCurrentTable(TableView*)));
    view->move(table_box->width(), 0);
    view->show();
    //table_views.push_back(view);
}

void TableWidget::saveLayout() {
    // TO DO
}










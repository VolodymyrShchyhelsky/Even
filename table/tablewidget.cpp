#include "tablewidget.h"

TableWidget::TableWidget(QWidget *parent) : QWidget(parent)
{
    seating_handler = new SeatingHandler(this);
    connect(this, SIGNAL(addTable(Table*)),
            seating_handler, SLOT(addTable(Table*)));
    initTableBox();
    initLayout();
    seating_handler->loadTablesFromDatabase(table_graphics_widget);
}

void TableWidget::initTableBox() {
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
            this, SLOT(addTable()));
    delete_table_button = new QPushButton("DELETE TABLE", this);
    connect(delete_table_button, SIGNAL(clicked()),
            seating_handler, SLOT(deleteCurrentTable()));

    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(round_table_button);
    layout->addWidget(rectangular_table_button);
    layout->addWidget(table_creation_widgets);
    layout->addWidget(add_table_button);
    layout->addWidget(delete_table_button);

    table_box = new QGroupBox;
    table_box->setLayout(layout);
}

void TableWidget::initLayout() {
    GuestListTableW * userList = new GuestListTableW(this);
    connect(userList, SIGNAL(seatGuest(QString)),
            seating_handler, SLOT(seatGuest(QString)));
    connect(seating_handler, SIGNAL(seatingUpdated()),
            userList, SLOT(updateModel()));
    GuestFilter * filter = new GuestFilter(userList, this);
    QHBoxLayout * userListLayout = filter->createTableWLayout();
    QHBoxLayout * layout = new QHBoxLayout;
    table_graphics_widget = new QWidget(this);
    table_box->setParent(table_graphics_widget);
    layout->addWidget(table_graphics_widget, 3);
    layout->addLayout(userListLayout, 1);
    setLayout(layout);
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

    TableView * view = new TableView(table, table_graphics_widget);
    seating_handler->connectTableView(view);
    view->move(table_box->width(), 0);
    view->setFocus();
    view->show();
}










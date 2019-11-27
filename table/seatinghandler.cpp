#include "seatinghandler.h"

SeatingHandler::SeatingHandler(QObject *parent) : QObject(parent), current_table_view(nullptr)
{

}

void SeatingHandler::loadTablesFromDatabase(QWidget *parent_widget) {
    QVector< QMap<QString, int> > tables_data = DataBaseHolder::getDbHolder()->getAllTables();
    QVector<TableView*> views;
    for (auto table_data = tables_data.begin(); table_data != tables_data.end(); ++table_data) {
        qDebug() << "load table" << *table_data;
        int base_capacity = (*table_data)[TABLES_BASE_CAPACITY_COLUMN], secondary_capacity = (*table_data)[TABLES_SECONDARY_CAPACITY_COLUMN];
        Table * table;
        if (secondary_capacity) {
            table = new RectangularTable(base_capacity, secondary_capacity, parent_widget);
        }
        else {
            table = new RoundTable(base_capacity, parent_widget);
        }
        int table_id = (*table_data)["id"];
        table->set_id(table_id);
        QStringList guest_names = DataBaseHolder::getDbHolder()->getNamesOfGuestsOnTable(table_id);
        table->set_guests(guest_names);
        TableView * view = new TableView(table, parent_widget);
        connectTableView(view);
        view->move((*table_data)[TABLES_X_COLUMN], (*table_data)[TABLES_Y_COLUMN]);
    }
}

void SeatingHandler::addTable(Table * table) {
    QPair<int, int> capacity = table->get_capacity();
    int table_id = DataBaseHolder::getDbHolder()->insertNewTable(capacity.first, capacity.second);
    qDebug() << "INSERTED" << table_id;
    table->set_id(table_id);
}

void SeatingHandler::createMessageBox(QString text, QString informative_text) {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText(text);
    msgBox.setInformativeText(informative_text);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void SeatingHandler::askToChooseTable() {
    createMessageBox("You didn't choose a table.",
                     "Click on a table to choose it.");
}

void SeatingHandler::askToChooseTableWithFreeSeats() {
    createMessageBox("The table you chose doesn't have any free seats.",
                     "Choose another table.");
}

void SeatingHandler::setCurrentTable(TableView * active_table_view) {
    if (current_table_view != nullptr && current_table_view != active_table_view) {
        current_table_view->get_table()->clear();
        current_table_view->get_table()->draw();
    }
    current_table_view = active_table_view;
}

void SeatingHandler::deleteCurrentTable() {
    if (current_table_view == nullptr) {
        askToChooseTable();
        return;
    }
    TableView * table_to_delete = current_table_view;
    current_table_view = nullptr;
    DataBaseHolder::getDbHolder()->deleteTable(table_to_delete->get_table()->get_id());
    delete table_to_delete;
    emit seatingUpdated();
}

void SeatingHandler::updateTableLocation(TableView * table_view) {
    DataBaseHolder::getDbHolder()->changeTableCoordinates(table_view->get_table()->get_id(), table_view->x(), table_view->y());
}

void SeatingHandler::seatGuest(QString guest_id) {
    if (current_table_view == nullptr) {
        askToChooseTable();
        return;
    }
    Table * table = current_table_view->get_table();
    if (!table->can_seat()) {
        askToChooseTableWithFreeSeats();
        return;
    }
    DataBaseHolder::getDbHolder()->addTableGuestEntry(table->get_id(), guest_id);

    QString guest_name = DataBaseHolder::getDbHolder()->getNameByGuestId(guest_id);
    table->add_guest(guest_name);
    table->draw(true);
    current_table_view->setFocus();
    emit seatingUpdated();
}

void SeatingHandler::connectTableView(TableView *view) {
    connect(view, SIGNAL(tableChosen(TableView*)),
            this, SLOT(setCurrentTable(TableView*)));
    connect(view, SIGNAL(coordinatesChanged(TableView*)),
            this, SLOT(updateTableLocation(TableView*)));
}

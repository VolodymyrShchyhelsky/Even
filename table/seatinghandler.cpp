#include "seatinghandler.h"

SeatingHandler::SeatingHandler(QObject *parent) : QObject(parent)
{

}

void SeatingHandler::addTable(Table * table) {
    QPair<int, int> capacity = table->get_capacity();
    QString base_capacity = QString::number(capacity.first);
    QString secondary_capacity = QString::number(capacity.second);
    QString table_id = DataBaseHolder::getDbHolder()->insertNewTable(base_capacity, secondary_capacity);
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
    current_table_view->get_table()->clear();
    current_table_view->get_table()->draw();
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
}

void SeatingHandler::updateTableLocation(TableView * table_view) {
    QString x = QString::number(table_view->x());
    QString y = QString::number(table_view->y());
    DataBaseHolder::getDbHolder()->changeTableCoordinates(table_view->get_table()->get_id(), x, y);
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
}

#include "descriptionmenuaction.h"
#include "QDebug"
#include "database/databaseholder.h"

DescriptionMenuAction::DescriptionMenuAction(QString description, MainWindow* parent_widget, QObject* parent)
    : QAction(description, parent), description(description), parent_widget(parent_widget)
{
    connect(this, SIGNAL(triggered()), this, SLOT(openDatabase()));
}

void DescriptionMenuAction::openDatabase() {
    DataBaseHolder::getDbHolder()->setPath(description);
    parent_widget->showTodos();
}

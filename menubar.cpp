#include "menubar.h"
#include "general/descriptionmenuaction.h"
#include <QInputDialog>
#include <QFile>
#include "database/databaseholder.h"
#include <QMessageBox>
#include <QDir>

MenuBar::MenuBar(MainWindow* parent_widget, QObject *parent) : QObject(parent), parent_widget(parent_widget)
{
    menu_bar = new QMenuBar;
    init();
}

void MenuBar::init() {
    file_m = menu_bar->addMenu("File");
    open_m = menu_bar->addMenu("Open");
    initOpenMenu();
    initFileMenu();
}

void MenuBar::initFileMenu() {
    remove_a = new QAction(tr("Remove"), parent_widget);
    create_a = new QAction(tr("New"), parent_widget);
    file_m->addAction(create_a);
    file_m->addAction(remove_a);
    connect(create_a, SIGNAL(triggered()), this, SLOT(create()));
    connect(remove_a, SIGNAL(triggered()), this, SLOT(remove()));
}

void MenuBar::create() {
    qDebug() << "create";
    bool ok;
    QString name = QInputDialog::getText(nullptr, tr("Enter name"),
                                         tr("Name:"), QLineEdit::Normal,
                                         "", &ok);

    if (ok && !name.isEmpty()) {
        QString path = QApplication::applicationDirPath() + "/" + name + ".db";
        if (QFile::exists(path)) {
            QMessageBox::warning(nullptr, "Fail", "Event already exist");
        }
        QFile file(path);
        file.open(QIODevice::ReadWrite);
        file.close();
        initOpenMenu();
        DataBaseHolder::getDbHolder()->setPath(name);
        parent_widget->showTodos();
    }
}

void MenuBar::remove() {
    qDebug() << "remove";
    QString path = DataBaseHolder::getDbHolder()->getPath();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Remove event", "Are you sure?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes && !path.isEmpty()) {
        QFile file (path);
        DataBaseHolder::getDbHolder()->setPath("");
        qDebug() << "remove" << file.remove();
        initOpenMenu();
        parent_widget->showTodos();
    }
}

void MenuBar::initOpenMenu() {
    open_m->clear();
    QStringList events = getEvents();
    for(auto event : events) {
        DescriptionMenuAction* action = new DescriptionMenuAction(event, parent_widget);
        open_m->addAction(action);
    }
}

QStringList MenuBar::getEvents() {
    QDir directory(QApplication::applicationDirPath());
    QStringList events = directory.entryList(QStringList() << "*.db", QDir::Files);
    for(QString& event : events) {
        event = event.left(event.lastIndexOf(QChar('.')));
    }
    return events;
}



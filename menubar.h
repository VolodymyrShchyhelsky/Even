#ifndef MENUBAR_H
#define MENUBAR_H

#include <QObject>
#include <QMenu>
#include <QMenuBar>
#include <QWidget>
#include "mainwindow.h"

class MenuBar : public QObject
{
    Q_OBJECT
public:
    explicit MenuBar(MainWindow* parent_widget, QObject *parent = nullptr);
    void init();
    QMenuBar* menu_bar;
signals:

public slots:
    void create();
    void remove();
    void initOpenMenu();

private:
    void initFileMenu();
    QStringList getEvents();
    MainWindow* parent_widget;
    QMenu* file_m ;
    QMenu* open_m;
    QAction *remove_a;
    QAction *create_a;
};

#endif // MENUBAR_H

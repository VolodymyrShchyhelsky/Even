#ifndef DESCRIPTIONMENUACTION_H
#define DESCRIPTIONMENUACTION_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QAction>
#include "mainwindow.h"

class DescriptionMenuAction : public QAction
{
    Q_OBJECT
public:
    virtual ~DescriptionMenuAction() {};
    DescriptionMenuAction(QString description, MainWindow* parent_widget, QObject* parent = nullptr );

public slots:
//    void sendDescriptionSlot();
    void openDatabase();
signals:


private:
    QString description;
    MainWindow* parent_widget;
};

#endif // DESCRIPTIONMENUACTION_H

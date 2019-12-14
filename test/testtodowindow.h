#ifndef TESTTODOWINDOW_H
#define TESTTODOWINDOW_H

#include <QObject>
#include "todowindow.h"
#include <memory>

class TestTodoWindow : public QObject
{
    Q_OBJECT
public:
    std::unique_ptr<TodoWindow> obj;

private slots:
    void initTestCase();
    void addGlobalTask();
    void addSubTask();
    void deleteTask();
    void configureShow();
};

#endif // TESTTODOWINDOW_H

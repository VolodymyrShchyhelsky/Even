#include "testtodowindow.h"
#include <QTest>
#include <QTestEventList>
#include <QRandomGenerator>

void TestTodoWindow::initTestCase() {
    obj.reset(new TodoWindow);
}

void TestTodoWindow::addGlobalTask(){
    int global_counts_before = obj->getTodoChildren("0").length();
    obj->addGlobalTodo();
    int global_counts_after = obj->getTodoChildren("0").length();
    QVERIFY(global_counts_after == global_counts_before + 1);
}

void TestTodoWindow::addSubTask() {
    int y = QRandomGenerator::global()->bounded(obj->view->width());
    int x = QRandomGenerator::global()->bounded(obj->view->height());

    QTestEventList events;
    events.addMouseMove(QPoint(x,y));
    events.simulate(obj->view);
}

void TestTodoWindow::deleteTask() {

}

void TestTodoWindow::configureShow() {

}

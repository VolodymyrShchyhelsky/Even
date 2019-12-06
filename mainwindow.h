#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "table/tablewidget.h"
#include <QScreen>
#include "schedule/schedulewidget.h"
#include "guest/guestlistwindow.h"
#include "todowindow.h"
#include <QDockWidget>
#include "todowindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton * guests_button;
    QPushButton * tables_button;
    QPushButton * schedule_button;
    QPushButton * todos_button;
    QWidget * page_choice_widget;

    void initDockWidget();
    void updateCentralWidget(QWidget * new_central_widget);

public slots:
    void showGuests();
    void showTables();
    void showSchedule();
    void showTodos();
};

#endif // MAINWINDOW_H

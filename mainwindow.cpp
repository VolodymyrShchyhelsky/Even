#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    UserListWidget* u = new UserListWidget(this);
    u->show();
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    TableWidget * table_widget = new TableWidget(this);
    table_widget->adjustSize();
    setCentralWidget(table_widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

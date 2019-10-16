#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //windowHandle()->setFlags(Qt::FramelessWindowHint);
    setWindowState(Qt::WindowMaximized);
    TableWidget * table_widget = new TableWidget(this);
    table_widget->adjustSize();
    setCentralWidget(table_widget);
    //table_widget->setGeometry(0, 0, width(), height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

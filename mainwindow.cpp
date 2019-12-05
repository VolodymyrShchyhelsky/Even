#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    resize(QGuiApplication::primaryScreen()->size());
    showTodos();
    initDockWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initDockWidget() {
    QDockWidget * dock_widget = new QDockWidget(this);

    guests_button = new QPushButton("GUESTS");
    connect(guests_button, SIGNAL(clicked()),
            this, SLOT(showGuests()));
    tables_button = new QPushButton("TABLES");
    connect(tables_button, SIGNAL(clicked()),
            this, SLOT(showTables()));
    schedule_button = new QPushButton("SCHEDULE");
    connect(schedule_button, SIGNAL(clicked()),
            this, SLOT(showSchedule()));
    todos_button = new QPushButton("TO-DO");
    connect(todos_button, SIGNAL(clicked()),
            this, SLOT(showTodos()));

    QHBoxLayout * layout = new QHBoxLayout;
    layout->addWidget(guests_button);
    layout->addWidget(tables_button);
    layout->addWidget(schedule_button);
    layout->addWidget(todos_button);

    page_choice_widget = new QWidget(dock_widget);
    page_choice_widget->setLayout(layout);

    dock_widget->setWidget(page_choice_widget);
    dock_widget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    //dock_widget->setWindowTitle("WELCOME ");

    addDockWidget(Qt::DockWidgetArea::TopDockWidgetArea, dock_widget);
}

void MainWindow::updateCentralWidget(QWidget * new_central_widget) {
    QWidget * current_central_widget = centralWidget();
    delete current_central_widget;
    new_central_widget->resize(QGuiApplication::primaryScreen()->size()*0.8);
    setCentralWidget(new_central_widget);
}


void MainWindow::showGuests() {
    updateCentralWidget(new GuestListWindow(this));
}

void MainWindow::showTables() {
    updateCentralWidget(new TableWidget(this));
}

void MainWindow::showSchedule() {
    updateCentralWidget(new ScheduleWidget(this));
}

void MainWindow::showTodos() {
    updateCentralWidget(new TodoWindow(this));
}

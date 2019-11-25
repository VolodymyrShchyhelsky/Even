#include "schedulewidget.h"

ScheduleWidget::ScheduleWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumHeight(parent->height() * 0.8);
    setMinimumWidth(parent->width() * 0.9);
    initModel();
    initView();
    initLayout();
    qDebug() << "initialized layout";
    adjustView();
    qDebug() << "adjusted view";
}

void ScheduleWidget::initModel() {
    db = DataBaseHolder::getDbHolder();
    QSqlTableModel * sql_model = new QSqlTableModel(nullptr, db->getDB());
    sql_model->setTable(SCHEDULE_TABLE);
    model = new ScheduleSortFilterProxyModel(this);
    sql_model->select();
    model->setSourceModel(sql_model);
    model->sortByDateTime();
}

void ScheduleWidget::initView() {
    view = new QTableView(this);
    view->setModel(model);
    view->setItemDelegate(new ScheduleDelegate);
    view->setColumnHidden(0, true);
    //view->verticalHeader()->setVisible(false);
    view->show();
    qDebug() << this->size();
}

void ScheduleWidget::initLayout() {
    add_record_button = new QPushButton("Add record", this);
    connect(add_record_button, &QPushButton::released,
            model, &ScheduleSortFilterProxyModel::createRecord);
    connect(model, SIGNAL(dataChanged()),
            this, SLOT(adjustView()));

    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(view);
    layout->addWidget(add_record_button);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setMargin(0);

    schedule_box = new QGroupBox(this);
    schedule_box->setLayout(layout);
    qDebug() << schedule_box->size();
}

void ScheduleWidget::adjustView() {
    view->resizeColumnsToContents();
    //view->resizeRowsToContents();
    adjustViewHeight();
    adjustViewWidth();
    adjustSize();
}

void ScheduleWidget::adjustViewHeight() {
    int total_height = 0;
    int column_count = view->verticalHeader()->count();
    for (int i = 0; i < column_count; ++i) {
        if (!view->verticalHeader()->isSectionHidden(i)) {
            total_height += view->verticalHeader()->sectionSize(i);
        }
    }
    if (!view->horizontalScrollBar()->isHidden()) {
         total_height += view->horizontalScrollBar()->height();
    }
    if (!view->horizontalHeader()->isHidden()) {
         total_height += view->horizontalHeader()->height();
    }
    int top, bottom, tmp;
    schedule_box->getContentsMargins(&tmp, &top, &tmp, &bottom);
    total_height += top + bottom;
    schedule_box->setMinimumHeight(total_height + 2*add_record_button->height() < height() ?
                                      total_height + 2*add_record_button->height() :
                                      height());
}

void ScheduleWidget::adjustViewWidth() {
    int total_width = 0;
    int row_count = view->horizontalHeader()->count();
    for (int i = 0; i < row_count; ++i) {
        if (!view->horizontalHeader()->isSectionHidden(i)) {
            total_width += view->horizontalHeader()->sectionSize(i);
        }
    }
    if (!view->verticalScrollBar()->isHidden()) {
         total_width += view->verticalScrollBar()->width();
    }
    if (!view->verticalHeader()->isHidden()) {
         total_width += view->verticalHeader()->width();
    }
    int left, right, tmp;
    schedule_box->getContentsMargins(&left, &tmp, &right, &tmp);
    total_width += (left + right);
    //total_width += (row_count + 1)*2;
    schedule_box->setMinimumWidth(total_width < width() ? total_width : width());
}









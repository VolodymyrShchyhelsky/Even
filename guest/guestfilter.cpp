#include "guestfilter.h"

GuestFilter::GuestFilter(GuestListBase* guest_list, QWidget *parent) : QWidget(parent)
{
    search_parameter = new QComboBox();
    search_line = new QLineEdit();
    uncheck_b = new QPushButton();
    search_b = new QPushButton();
    search_b->setText("Search");
    this->guest_list = guest_list;
    initSearchLine();
    initTags();
}

QGridLayout* GuestFilter::createTableWLayout() {
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(search_line,0,0,1,3);
    layout->addWidget(search_parameter,1,0,1,3);
    layout->addWidget(search_b,0,3,2,2);
    layout->addWidget(guest_list, 2, 0, 6, 3);
    layout->addWidget(tags_widget,2,3,6,2);
    return layout;
}

void GuestFilter::initSearchLine() {
    for(auto str : guest_list->visible_columns) {
        search_parameter->addItem(str);
    }
    connect(search_b, SIGNAL (released()),this, SLOT (search()));
}

void GuestFilter::search() {
    QString filter;
    QString text = search_line->text();
    if(text != "") {
        QString param = search_parameter->currentText();
        filter = text + " = " + param + " and ";
    }
    for(auto tag = tags.begin(); tag != tags.end(); ++tag) {
        if(tag->first->checkState() == Qt::Checked) {
            QString tag_id = tag->second;
            filter += " id in (select guest_id from tagtoguest where tag_id = " + tag_id + ") and ";
        }
    }
    filter = filter.left(filter.length() - 4);
    guest_list->applyFilters(filter);
}

void GuestFilter::initTags() {
    tags.clear();
    QScrollArea* tag_scroll_area = new QScrollArea(this);
    delete tags_widget;
    tags_widget = new QWidget(tag_scroll_area);
    QVBoxLayout* layout = new QVBoxLayout(tags_widget);
    layout->setAlignment(Qt::AlignTop);
    QSqlQuery get_tag = QSqlQuery("select * from tag", DataBaseHolder::getDbHolder()->getDB());
    //TODO
    while(get_tag.next()) {
         QString tag_id = get_tag.value(0).toString();
         QString tag_name = get_tag.value(1).toString();
         QCheckBox* check = new QCheckBox(tag_name,tags_widget);
         tags.append(QPair<QCheckBox*, QString>(check, tag_id));
         layout->addWidget(check);
    }
}

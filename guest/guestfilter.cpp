#include "guestfilter.h"

GuestFilter::GuestFilter(GuestListBase* guest_list, QWidget *parent) : QWidget(parent)
{
    search_parameter = new QComboBox();
    search_line = new QLineEdit();
    uncheck_b = new QPushButton();
    search_b = new QPushButton();
    search_b->setText("Search");

    show_attend = new QCheckBox("Show attend");
    show_not_attend = new QCheckBox("Show attend");
    show_attend->setCheckState(Qt::Checked);
    show_not_attend->setCheckState(Qt::Checked);

    this->guest_list = guest_list;
    initSearchLine();
    initTags();
}

QHBoxLayout* GuestFilter::createTableWLayout() {
    QHBoxLayout* layout = new QHBoxLayout;

    QVBoxLayout* buttons_layout = new QVBoxLayout;
    buttons_layout->addWidget(search_parameter);
    buttons_layout->addWidget(search_line);
    buttons_layout->addWidget(search_b);
    buttons_layout->addWidget(tags_widget);

    layout->addWidget(guest_list->guest_view, 2);
    layout->addLayout(buttons_layout, 1);
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
        filter = param + " like '%" + text + "%' and ";
    }
    for(auto tag = tags.begin(); tag != tags.end(); ++tag) {
        if(tag->first->checkState() == Qt::Checked) {
            QString tag_id = tag->second;
            filter += " id in (select guest_id from tagtoguest where tag_id = " + tag_id + ") and ";
        }
    }
//    if(true) { //time for check
//        if show_attend.
//        filter += " is_present in " +
//    } else {
//
//    }
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

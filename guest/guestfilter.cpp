#include "guestfilter.h"

GuestFilter::GuestFilter(GuestListBase* guest_list, QWidget *parent) : QWidget(parent)
{
    qDebug() << "GuestFilter 5";
    search_parameter = new QComboBox();
    search_line = new QLineEdit();
    uncheck_b = new QPushButton();
    search_b = new QPushButton();
    search_b->setText("Search");
    this->guest_list = guest_list;
    initSearchLine();
    qDebug() << "GuestFilter 7";
    initTags();
    qDebug() << "GuestFilter 9";
}

void GuestFilter::initSearchLine() {
    for(auto str : guest_list->visible_columns) {
        qDebug() << "GuestFilter 15" << str;
        search_parameter->addItem(str);
    }
    connect(search_b, SIGNAL (released()),this, SLOT (search()));
}

void GuestFilter::search() {
    QString filter;
    QString text = search_line->text();
    if(text != "") {
        QString param = search_parameter->currentText();
        filter = text + " = " + param;
    }
    for(auto tag = tags.begin(); tag != tags.end(); ++tag) {
        if(tag->first->checkState() == Qt::Checked) {
            QString tag_id = tag->second;
            filter += " and id in (select guest_id from tagtoguest where tag_id = " + tag_id + ") ";
        }
    }
    guest_list->applyFilters(filter);
}

void GuestFilter::initTags() {
    tag_scroll_area = new QScrollArea(this);
    tags_widget = new QWidget(tag_scroll_area);
    QVBoxLayout* layout = new QVBoxLayout(tags_widget);
    QSqlQuery get_tag = QSqlQuery("select * from tag", DataBaseHolder::getDbHolder()->getDB());
    while(get_tag.next()) {
         QString tag_id = get_tag.value(0).toString();
         QString tag_name = get_tag.value(1).toString();
         //qDebug() << "tags 49" << tag_
         QCheckBox* check = new QCheckBox(tag_name,tags_widget);
         tags.append(QPair<QCheckBox*, QString>(check, tag_id));
         layout->addWidget(check);
    }
    tag_scroll_area->setWidget(tags_widget);
}
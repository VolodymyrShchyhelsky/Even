#include "testguestfilter.h"


void TestGuestFilter::initTestCase() {
    QDateTime start_time = QDateTime::currentDateTime();
    list = new GuestMainList(start_time, nullptr);
    filter = new GuestFilter(list);
}

void TestGuestFilter::search() {
    QString TEST_SEARCH = "1";
    int all = list->guest_view->verticalHeader()->count();
    auto count_table = [&]() -> int {
        int count = 0;
        for(int row = 0; row < list->guest_view->verticalHeader()->count(); ++row) {
            int column = list->guest_model->fieldIndex("id");
            QModelIndex id_index = list->guest_model->index(row, column);
            QString cellText = id_index.data().toString();
            if(cellText.indexOf(TEST_SEARCH) != -1) {
                count++;
            }
        }
        return count;
    };
    int before = count_table();
    filter->search_line->setText(TEST_SEARCH);
    filter->search();
    QCOMPARE(list->guest_view->verticalHeader()->count(), before);
    QCOMPARE(before, count_table());
}


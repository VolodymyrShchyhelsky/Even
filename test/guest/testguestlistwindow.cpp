#include "testguestlistwindow.h"

void TestGuestListWindow::initTestCase() {
    QDateTime start_time = QDateTime::currentDateTime();
    test_obj.reset(new GuestListWindow(start_time));
}

void TestGuestListWindow::addGuest() {
    int before = DataBaseHolder::getDbHolder()->getRecordCount("guest");
    test_obj->addNewGest();
    int after = DataBaseHolder::getDbHolder()->getRecordCount("guest");
    QCOMPARE(before + 1, after);
}

void TestGuestListWindow::addTag() {
//    TagWindow* tg = test_obj->addTag();
//    TestTagWindow test_tag_window(tg);
//    int before = test_obj->filter->tags.size();
////    QTest::qExec(&test_tag_window);
//    QCOMPARE(before + 1, test_obj->filter->tags.size());
}



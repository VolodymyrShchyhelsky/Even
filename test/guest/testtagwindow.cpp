#include "testtagwindow.h"

TestTagWindow::TestTagWindow()
{
    test_obj = new TagWindow();
}

void TestTagWindow::enterName() {
    QSignalSpy spy(test_obj, SIGNAL(newTagAdded()));
    QTest::keyClicks(test_obj->name_l, "");
    test_obj->save();
    QCOMPARE(spy.count(), 0);
}

void TestTagWindow::save() {
    QSignalSpy spy(test_obj, SIGNAL(newTagAdded()));
    QTest::keyClicks(test_obj->name_l, TEST_NAME);
    int before = DataBaseHolder::getDbHolder()->getRecordCount("tagtoguest");
    test_obj->save();
    QCOMPARE(DataBaseHolder::getDbHolder()->getRecordCount("tag", TEST_NAME), 1);
    QCOMPARE(before + test_obj->without_tag->hide_list.size(), DataBaseHolder::getDbHolder()->getRecordCount("tagtoguest"));
    QCOMPARE(spy.count(), 1);
}

//void TestTagWindow::withTag() {

//}

//void TestTagWindow::withoutTag() {

//}

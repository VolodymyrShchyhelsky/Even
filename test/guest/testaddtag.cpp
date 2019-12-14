#include "testaddtag.h"
#include <QSignalSpy>
#include <QTest>
#include <QRandomGenerator>

void TestAddTag::initTestCase() {
    obj = new AddTagWindow(TEST_ID);
}

void TestAddTag::addTag() {
    int before = DataBaseHolder::getDbHolder()->getRecordCount("tagtoguest", TEST_ID, "guest_id");
    int tag_added_count = 0;
    for(int it = 0; it < 10; ++it) {
        int y = QRandomGenerator::global()->bounded(10);
        int xPos = obj->view->columnViewportPosition( 0 ) + 5;
        int yPos = obj->view->rowViewportPosition( y ) + 10;
        QPoint p(xPos, yPos);
        QModelIndex index = obj->view->indexAt(p);
        if(index.isValid()) {
            tag_added_count++;
        }
        obj->addTag(index);
    }
    QCOMPARE(before + tag_added_count, DataBaseHolder::getDbHolder()->getRecordCount("tagtoguest", TEST_ID, "guest_id"));

}

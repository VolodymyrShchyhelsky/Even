#ifndef TABLE_H
#define TABLE_H

#include <QGraphicsScene>
#include <QtMath>

class Table : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Table(QObject *parent = nullptr);
    void setNumOfGuests(int num_of_guests);
    void draw();

private:
    const int chair_radius = 30;
    const int freeSpace = 3;
    const int default_table_radius = 50;
    int table_radius = default_table_radius;
    int guests = 1;

    void recalculateTableRadius();

signals:

public slots:
};

#endif // TABLE_H

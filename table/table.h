#ifndef TABLE_H
#define TABLE_H

#include <QGraphicsScene>
#include <QtMath>
#include <QDebug>

class Table : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Table(QObject *parent = nullptr);
    virtual void draw() = 0;
    void move(int dx, int dy);

protected:
    const int chair_radius = 20;
    int x = 0;
    int y = 0;

signals:

public slots:
};

#endif // TABLE_H

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
    virtual void draw(bool active = false) = 0;
    virtual QPair<int, int> get_capacity() = 0;

    void move(int dx, int dy);
    void set_id(QString id);
    QString get_id();
    void add_guest(QString guest_name);
    bool can_seat();

protected:
    const int chair_radius = 20;
    const QBrush active_brush = QBrush(QColor(250,128,114));
    int x = 0;
    int y = 0;
    QString id;
    QStringList guest_names;

signals:

public slots:
};

#endif // TABLE_H

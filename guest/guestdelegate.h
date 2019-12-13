#ifndef GUESTDELEGATE_H
#define GUESTDELEGATE_H

#include <QItemDelegate>
#include <QPainter>
#include <QSqlTableModel>

class GuestDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    GuestDelegate(QObject *parent=nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
//    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
//    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
//    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
//    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    bool isPresentColumn(const QModelIndex &index) const;

};

#endif // GUESTDELEGATE_H


#ifndef DESCRIPTIONBUTTON_H
#define DESCRIPTIONBUTTON_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QString>

class DescriptionButton : public QPushButton
{
    Q_OBJECT
public:
    virtual ~DescriptionButton() {};
    DescriptionButton(QString description, const QString&, QWidget* parent = 0 );

public slots:
    void sendDescriptionSlot();

signals:
    void descriptionSignal(QString);

private:
    QString description;
};

#endif // DESCRIPTIONBUTTON_H

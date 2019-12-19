#include "descriptionbutton.h"

DescriptionButton::DescriptionButton(QString description, const QString& text, QWidget* parent)
    : QPushButton(text, parent), description(description)
{
    connect(this, SIGNAL(clicked()), this, SLOT(sendDescriptionSlot()));
}

void DescriptionButton::sendDescriptionSlot() {
    emit descriptionSignal(description);
}

#include "view.h"

View::View(QWidget *parent)
    : QGraphicsView(parent)
{
    // Postavljamo velicinu
    this->setFixedSize(1280, 760);

    // Iskljucujemo skrol
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    title = new Title(this);

    setScene(title);
}

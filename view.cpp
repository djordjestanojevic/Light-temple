#include "view.h"

View::View() {
    this->setFixedSize(QSize(1280, 760));
    // Iskljucujemo prikaz skrolova
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

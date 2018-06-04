#include "view.h"

View::View(QWidget *parent)
    : QGraphicsView(parent)
{

    // Iskljucujemo skrol
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    title = new Title(this);

    setScene(title);
    if(QApplication::desktop()->screenGeometry().width() <= 1366 && QApplication::desktop()->screenGeometry().height() <= 768) {
        setFixedSize(QApplication::desktop()->screenGeometry().width() - QApplication::desktop()->screenGeometry().width()/20, QApplication::desktop()->screenGeometry().height() - QApplication::desktop()->screenGeometry().height()/14);
        scale((QApplication::desktop()->screenGeometry().width() - QApplication::desktop()->screenGeometry().width()/20)/1280.0,  (QApplication::desktop()->screenGeometry().height() - QApplication::desktop()->screenGeometry().height()/14)/760.0);
    }
    else
        setFixedSize(1280, 760);
}

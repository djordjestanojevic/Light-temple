#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QPushButton>
#include <QGraphicsScene>

#include "title.h"

class View: public QGraphicsView {
    Q_OBJECT
public:
    View(QWidget *parent = 0);

private:
    QGraphicsScene *title;

    void begin();

};

#endif // VIEW_H

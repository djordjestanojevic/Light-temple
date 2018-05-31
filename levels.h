#ifndef LEVELS_H
#define LEVELS_H
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QApplication>
#include <QGraphicsView>

#include "view.h"
#include "level01.h"

class View;
class Title;

class Levels: public QGraphicsScene {
    Q_OBJECT
public:
    Levels(View *v, Title *t, QWidget *parent = 0);

    QPushButton * mainMenu;

    QPushButton *button01;



private:
    QGraphicsPixmapItem *background;

    View *view;
    Title *title;

public slots:
    void startProgram();
    void nextLevel();
    void exitLevel();
};


#endif // LEVELS_H

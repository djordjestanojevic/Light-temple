#ifndef LEVELS_H
#define LEVELS_H
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QApplication>
#include <QGraphicsView>

#include <fstream>
#include <string>

#include "view.h"
#include "level01.h"

class View;
class Title;

class Levels: public QGraphicsScene {
    Q_OBJECT
public:
    Levels(View *v, Title *t, QWidget *parent = 0);

    QPushButton * mainMenu;

    QPushButton *button[5];


    static int currentLevel;
    static int lastUnlocked;
    static int levelStars[5];


private:
    QGraphicsPixmapItem *background;

    View *view;
    Title *title;

public slots:
    void startLevel1();
    void startLevel2();
    void startLevel3();
    void startLevel4();
    void startLevel5();
    void nextLevel();
    void exitLevel();
};


#endif // LEVELS_H

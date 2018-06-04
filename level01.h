#ifndef LEVEL01_H
#define LEVEL01_H

#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QKeyEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStyle>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "player.h"


class Levels;

class Level01: public QGraphicsScene {
    Q_OBJECT
public:
    Level01(QString str, Levels *l, QWidget *parent = 0);

    void timerEvent(QTimerEvent *event);
private:
    Levels *levels;
    QWidget *endWindow;

    void initPlayers();
    void MakeMap(QString str);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void levelEnd();
    void gameOver();
    void pause();

    Player *fireboy;
    Player *watergirl;

    QGraphicsRectItem *background;

    struct lever {
        QGraphicsPixmapItem *button;
        QGraphicsPixmapItem *elevator;
        int buttonPos;
        int elevatorPos;
        int onOff;
    };

    struct pusher {
        QGraphicsPixmapItem *button1;
        QGraphicsPixmapItem *button2;
        QGraphicsPixmapItem *elevator;
        int pos;
    };

    QList<QGraphicsPixmapItem *> blocks;
    QList<QGraphicsPixmapItem *> lava;
    QList<QGraphicsPixmapItem *> water;
    QList<QGraphicsPixmapItem *> acid;
    QList<lever> levers;
    QList<pusher> pushers;
    QList<QGraphicsPixmapItem *> boxes;
    QList<QGraphicsPixmapItem *> diamonds;
    QList<QGraphicsPixmapItem *> redGems;
    QList<QGraphicsPixmapItem *> blueGems;
    QList<QGraphicsPixmapItem *> doors;

    QList<QPointF> boxPosition;

    QTimer timerFireboy;
    QTimer timerWatergirl;

    QTimer timerElevator;

    int gravityTimerID;
    int run;

    float velocityFireboy;
    float velocityWatergirl;
    QList<float> velocityBox;

    int directionFireboy;
    int directionWatergirl;

    QPushButton *nextLevel;
    QPushButton *exitToMenu;
    QPushButton *repeatThisLevel;
    QPushButton *resume;

    QPushButton *pauseGame;

    QTimer timer;
    void timerFunc();
    int timerCount;


    int numOfDiamonds;
    int numOfRedGems;
    int numOfBlueGems;

private slots:
    void moveFireboy();
    void moveWatergirl();
    void repeatLevel();
    void resumeLevel();
    void moveElevator();
    void pauseOnTimer();
};
#endif // LEVEL01_H

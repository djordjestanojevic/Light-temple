#ifndef LEVEL01_H
#define LEVEL01_H

#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QKeyEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>
#include <fstream>
#include <string>

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

    int pauseOnOff;

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
    QList<QGraphicsPixmapItem *> object;
    QList<QGraphicsPixmapItem *> red_diamont;
    QList<QGraphicsPixmapItem *> blue_diamont;
    QList<QGraphicsPixmapItem *> doors;

    QTimer timerFireboy;
    QTimer timerWatergirl;

    QTimer timerElevator;

    int gravityTimerID;

    float velocityFireboy;
    float velocityWatergirl;

    int directionFireboy;
    int directionWatergirl;

    QPushButton *nextLevel;
    QPushButton *exitToManu;
    QPushButton *repeatThisLevel;
    QPushButton *resume;

private slots:
    void moveFireboy();
    void moveWatergirl();
    void repeatLevel();
    void resumeLevel();
    void moveElevator();
};
#endif // LEVEL01_H

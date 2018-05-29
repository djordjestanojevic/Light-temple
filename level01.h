#ifndef LEVEL01_H
#define LEVEL01_H

#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QKeyEvent>
#include <QPropertyAnimation>

#include <fstream>
#include <string>

#include "player.h"

class Level01: public QGraphicsScene {
    Q_OBJECT
public:
    Level01(QWidget *parent = 0);

    void timerEvent(QTimerEvent *event);
private:
    void initPlayers();
    void MakeMap();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    Player *fireboy;
    Player *watergirl;

    QGraphicsRectItem *background;

    QList<QGraphicsPixmapItem *> blocks;
    QList<QGraphicsPixmapItem *> lava;
    QList<QGraphicsPixmapItem *> water;
    QMap<QGraphicsPixmapItem *, QGraphicsPixmapItem *> lever;
    QMap<QGraphicsPixmapItem *, QGraphicsPixmapItem *> pusher;
    QList<QGraphicsPixmapItem *> object;
    QList<QGraphicsPixmapItem *> red_diamont;
    QList<QGraphicsPixmapItem *> blue_diamont;

    QTimer timerFireboy;
    QTimer timerWatergirl;

    int gravityTimerID;

    float velocityFireboy;
    float velocityWatergirl;

    int directionFireboy;
    int directionWatergirl;

private slots:
    void moveFireboy();
    void moveWatergirl();
};
#endif // LEVEL01_H

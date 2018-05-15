#ifndef LEVEL01_H
#define LEVEL01_H

#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QKeyEvent>
#include <fstream>
#include "player.h"

class Level01: public QGraphicsScene {
    Q_OBJECT
public:
    Level01(QWidget *parent = 0);
private:
    void initPlayField();
    void makeMap();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    QList<QGraphicsPixmapItem *> blocks;
    QGraphicsRectItem *background;
    QGraphicsPixmapItem *ground;

    Player *fireboy;

    QTimer m_timer;

    int direction;
private slots:
    void movePlayer();
};
#endif // LEVEL01_H

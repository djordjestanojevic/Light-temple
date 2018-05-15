#ifndef LEVEL01_H
#define LEVEL01_H

#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QKeyEvent>
#include <fstream>
#include <string>

#include "player.h"

class Level01: public QGraphicsScene {
    Q_OBJECT
public:
    Level01(QWidget *parent = 0);
private:
    void initPlayField();
    void MakeMap();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    QGraphicsRectItem *background;

    Player *fireboy;
    Player *watergirl;
    QList<QGraphicsPixmapItem *> blocks;

    QTimer m_timer;

    int direction;


private slots:
    void movePlayer();
};
#endif // LEVEL01_H

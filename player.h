#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QPainter>
#include <string>

class Player: public QGraphicsItem {
public:
    Player(QString str, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    QGraphicsPixmapItem* collidesWithRedGems(QList<QGraphicsPixmapItem *> redGems);
    QGraphicsPixmapItem* collidesWithBlueGems(QList<QGraphicsPixmapItem *> blueGems);
    QGraphicsPixmapItem* collidesWithDiamonds(QList<QGraphicsPixmapItem *> diamonds);
    QGraphicsPixmapItem* collidesWithBoxes(QList<QGraphicsPixmapItem *> boxes);
    QGraphicsPixmapItem* collidesWithBlocks(QList<QGraphicsPixmapItem *> blocks);
    bool collidesWithFluid(QList<QGraphicsPixmapItem *> wf, QList<QGraphicsPixmapItem *> acid);

    bool onGround(QList<QGraphicsPixmapItem *> blocks);

    void nextFrame();
    void setPixmap(QString s);
    void setDirection(int i);
private:
    QPixmap pixmap;
    QPixmap standPixmap;
    QPixmap runPixmap;
    QPixmap currentPixmap;
    int currentFrame;

    int direction;

    QString path;
};

#endif // PLAYER_H

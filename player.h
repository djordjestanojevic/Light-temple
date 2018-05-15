#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QPainter>

class Player: public QGraphicsItem {
public:
    Player(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    bool collidesWithBlocks(QList<QGraphicsPixmapItem *> blocks);
private:
    QPixmap pixmap;
};

#endif // PLAYER_H

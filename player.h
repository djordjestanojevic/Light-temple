#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsItem>
#include <QPixmap>

class Player : public QGraphicsItem {
public:
    Player(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool collidesWithBlock(QList<QGraphicsPixmapItem *> blocks);

private:
    QPixmap pixmap;

};
#endif // PLAYER_H

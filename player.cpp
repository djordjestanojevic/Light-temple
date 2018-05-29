#include "player.h"
#include <iostream>

Player::Player(QString str, QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    pixmap = QPixmap(str).scaled(32, 55);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // Iscrtava figuru
    painter->drawPixmap(0,0 /* koordinate centra figure */,
                        pixmap /* Figura */,
                        0, 0, 32, 55)/* velicina figure */;
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}

QRectF Player::boundingRect() const {
    return QRectF(0,0,32,55);
}

QGraphicsPixmapItem* Player::collidesWithBlocks(QList<QGraphicsPixmapItem *> blocks) {

    for(int i = 0; i < blocks.length(); i++) {
        if(collidesWithItem(blocks[i]))
            return blocks[i];
    }
    return NULL;
}

bool Player::onGround(QList<QGraphicsPixmapItem *> blocks) {

    moveBy(0, 1);
    if(collidesWithBlocks(blocks) != NULL) {
        moveBy(0, -1);
        return true;
    }
    else {
        moveBy(0, -1);
        return false;
    }
}

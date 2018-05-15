#include "player.h"

Player::Player(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    pixmap = QPixmap("./Images/fireboy");
}



QRectF Player::boundingRect() const {

}
void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

}


bool Player::collidesWithBlock(QList<QGraphicsPixmapItem *> blocks) {
    return true;
}

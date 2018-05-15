#include "player.h"

Player::Player(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    pixmap = QPixmap("./Images/fireboy").scaled(55, 100);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // Iscrtava figuru
    painter->drawPixmap(0,0 /* koordinate centra figure */,
                        pixmap /* Figura */,
                        0, 0, 55, 100)/* velicina figure */;
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}

QRectF Player::boundingRect() const {
    return QRectF(0,0,55,100);
}

bool Player::collidesWithBlocks(QList<QGraphicsPixmapItem *> blocks) {

    for(int i = 0; i < blocks.length(); i++) {
        if(collidesWithItem(blocks[i]))
            return true;
    }
    return false;
}

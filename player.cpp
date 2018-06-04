#include "player.h"
#include <iostream>

Player::Player(QString str, QGraphicsItem *parent)
    : QGraphicsItem(parent)
{

    pixmap = QPixmap(str).scaled(32, 55);
//    path = str;
//    direction = 0;

//    standPixmap = QPixmap(str + "Stand").scaled(320, 50);
//    runPixmap = QPixmap(str + "Run").scaled(320, 50);
//    currentPixmap = standPixmap;
//    currentFrame = 0;
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // Iscrtava figuru
    painter->drawPixmap(0,0 /* koordinate centra figure */,
                        /*currentPixmap*/ pixmap /* Figura */,
                        /*currentFrame*/ 0, 0, 32, 55)/* velicina figure */;
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}

QRectF Player::boundingRect() const {
    return QRectF(0,0,32, 55);
}

QGraphicsPixmapItem* Player::collidesWithBlocks(QList<QGraphicsPixmapItem *> blocks) {

    for(int i = 0; i < blocks.length(); i++) {
        if(collidesWithItem(blocks[i]))
            return blocks[i];
    }
    return NULL;
}


QGraphicsPixmapItem* Player::collidesWithBoxes(QList<QGraphicsPixmapItem *> boxes) {

    for(int i = 0; i < boxes.length(); i++) {
        if(collidesWithItem(boxes[i]))
            return boxes[i];
    }
    return NULL;
}

bool Player::collidesWithFluid(QList<QGraphicsPixmapItem *> wf, QList<QGraphicsPixmapItem *> acid) {

    for(int i = 0; i < acid.length(); i++) {
        if(collidesWithItem(acid[i]))
            return true;
    }

    for(int i = 0; i < wf.length(); i++) {
        if(collidesWithItem(wf[i]))
            return true;
    }

    return false;

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


QGraphicsPixmapItem* Player::collidesWithRedGems(QList<QGraphicsPixmapItem *> redGems){

    for(int i = 0; i < redGems.length(); i++) {
        if(collidesWithItem(redGems[i]))
            return redGems[i];
    }
    return NULL;

}
QGraphicsPixmapItem* Player::collidesWithBlueGems(QList<QGraphicsPixmapItem *> blueGems){

    for(int i = 0; i < blueGems.length(); i++) {
        if(collidesWithItem(blueGems[i]))
            return blueGems[i];
    }
    return NULL;
}


QGraphicsPixmapItem* Player::collidesWithDiamonds(QList<QGraphicsPixmapItem *> diamonds) {

    for(int i = 0; i < diamonds.length(); i++) {
        if(collidesWithItem(diamonds[i]))
            return diamonds[i];
    }
    return NULL;
}

void Player::nextFrame() {
    if(currentFrame > 250)
        currentFrame = 0;
    currentFrame += 32;
}

void Player::setPixmap(QString s) {
    if(s == "run")
        currentPixmap = runPixmap;
    if(s == "stand")
        currentPixmap = standPixmap;
}

void Player::setDirection(int i) {
    if(i != direction && direction != 0)
        moveBy(-32*i, 0);
    direction = i;
    setTransform(QTransform(i, 0, 0, 1, 0, 0));
}


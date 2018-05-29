#include "level01.h"

#include <iostream>

Level01::Level01(QWidget *parent)
    : QGraphicsScene(0, 0,  1280, 760, parent)
{
    directionFireboy = 0;
    directionWatergirl = 0;

    velocityFireboy = 0;
    velocityWatergirl = 0;

    MakeMap();
    initPlayers();

    gravityTimerID = startTimer(19.5);

    timerFireboy.setInterval(20);
    connect(&timerFireboy, &QTimer::timeout, this, &Level01::moveFireboy);

    timerWatergirl.setInterval(20);
    connect(&timerWatergirl, &QTimer::timeout, this, &Level01::moveWatergirl);
}

void Level01::initPlayers() {

    fireboy = new Player("./Images/fireboy/Idle__000");
    fireboy->setPos(100, 660);
    this->addItem(fireboy);

    while(fireboy->collidesWithBlocks(blocks) == NULL) {
        fireboy->moveBy(0, 1);
    }
    fireboy->moveBy(0, -1);


    watergirl = new Player("./Images/watergirl/Idle__000");
    watergirl->setPos(100, 570);
    this->addItem(watergirl);

    while(watergirl->collidesWithBlocks(blocks) == NULL) {
        watergirl->moveBy(0, 1);
    }
    watergirl->moveBy(0, -1);
}


void Level01::timerEvent(QTimerEvent *event) {
    if(event->timerId() == gravityTimerID) {
        velocityFireboy += 0.5;
        fireboy->moveBy(0, velocityFireboy);

        velocityWatergirl += 0.5;
        watergirl->moveBy(0, velocityWatergirl);

        if(fireboy->collidesWithBlocks(blocks)) {
            fireboy->moveBy(0, -velocityFireboy);
            velocityFireboy = 0;
        }

        if(watergirl->collidesWithBlocks(blocks)) {
            watergirl->moveBy(0, -velocityWatergirl);
            velocityWatergirl = 0;
        }
    }
}

void Level01::moveFireboy() {

    if(directionFireboy == 1) {
        fireboy->moveBy(5, 0);
        if(fireboy->collidesWithBlocks(blocks)) {
            fireboy->moveBy(-5, 0);
        }

    }

    if(directionFireboy == -1) {
        fireboy->moveBy(-5, 0);
        if(fireboy->collidesWithBlocks(blocks)) {
            fireboy->moveBy(5, 0);
        }

    }

}

void Level01::moveWatergirl() {

    if(directionWatergirl == 1) {
        watergirl->moveBy(5, 0);
        if(watergirl->collidesWithBlocks(blocks)) {
            watergirl->moveBy(-5, 0);
        }

    }

    if(directionWatergirl == -1) {
        watergirl->moveBy(-5, 0);
        if(watergirl->collidesWithBlocks(blocks)) {
            watergirl->moveBy(5, 0);
        }

    }

}

void Level01::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
        return;

    switch (event->key()) {
        case Qt::Key_Right:
            directionFireboy += 1;
            timerFireboy.start();
            break;
        case Qt::Key_Left:
            directionFireboy -= 1;
            timerFireboy.start();
            break;
        case Qt::Key_Up:
            if(fireboy->onGround(blocks)) {
                velocityFireboy = -9.0;
            }
            break;
        case Qt::Key_D:
            directionWatergirl += 1;
            timerWatergirl.start();
            break;
        case Qt::Key_A:
            directionWatergirl -= 1;
            timerWatergirl.start();
            break;
        case Qt::Key_W:
            if(watergirl->onGround(blocks)) {
                velocityWatergirl = -9.0;
            }
            break;
        default:
            break;
    }
}

void Level01::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
        return;

    switch (event->key()) {
        case Qt::Key_Right:
            directionFireboy -= 1;
            if(directionFireboy == 0)
                timerFireboy.stop();
            break;
        case Qt::Key_Left:
            directionFireboy += 1;
            if(directionFireboy == 0)
                timerFireboy.stop();
            break;
        case Qt::Key_D:
            directionWatergirl -= 1;
            if(directionWatergirl == 0)
                timerWatergirl.stop();
            break;
        case Qt::Key_A:
            directionWatergirl += 1;
            if(directionWatergirl == 0)
                timerWatergirl.stop();
            break;
        default:
            break;
    }
}

void Level01::MakeMap() {

    background = this->addRect(0, 0, 1280,760);
    background->setBrush(QBrush(QPixmap("./Images/wall").scaled(600, 600)));


    std::ifstream f("./map.txt", std::ifstream::in);
    while(f.is_open())
    {
        std::string elem;
        int x;
        int y;
        f >> elem >> x >> y;

        if(elem[0] == '/' && elem[1] == '/')
            continue;

        if(elem == "Block" )
        {
            QGraphicsPixmapItem *block = new QGraphicsPixmapItem;
            block->setPixmap(QPixmap("./Images/block").scaled(30, 30));
            block->setPos(x,y);
            addItem(block);
            blocks.append(block);
        }
        else if(elem == "Lava")
        {
            QGraphicsPixmapItem *l = new QGraphicsPixmapItem;
            l->setPixmap(QPixmap("./Images/lava").scaled(30, 29));
            l->setPos(x,y);
            addItem(l);
            lava.append(l);
        }
        else if(elem == "Water")
        {
            QGraphicsPixmapItem *w = new QGraphicsPixmapItem;
            w->setPixmap(QPixmap("./Images/water").scaled(30, 25));
            w->setPos(x,y + 4);
            addItem(w);
            water.append(w);
        }
        else
            break;
    }
}

#include "level01.h"

#include <iostream>

Level01::Level01(QWidget *parent)
    : QGraphicsScene(0, 0,  1280, 760, parent)
{

    direction = 0;
    velocityY = 0;
    MakeMap();
    initPlayers();

    gravityTimerID = startTimer(19.5);

    m_timer.setInterval(20);
    connect(&m_timer, &QTimer::timeout, this, &Level01::movePlayer);

}

void Level01::initPlayers() {

    fireboy = new Player();
    fireboy->setPos(100, 660);
    this->addItem(fireboy);

    while(fireboy->collidesWithBlocks(blocks) == NULL) {
        fireboy->moveBy(0, 1);
    }
    fireboy->moveBy(0, -1);
}


void Level01::timerEvent(QTimerEvent *event) {
    if(event->timerId() == gravityTimerID) {
        velocityY += 0.5;
        fireboy->moveBy(0, velocityY);

        if(fireboy->collidesWithBlocks(blocks)) {
            fireboy->moveBy(0, -velocityY);
            velocityY = 0;
        }
    }
}

void Level01::movePlayer() {

    if(direction == 1) {
        fireboy->moveBy(5, 0);
        if(fireboy->collidesWithBlocks(blocks)) {
            fireboy->moveBy(-5, 0);
        }

    }

    if(direction == -1) {
        fireboy->moveBy(-5, 0);
        if(fireboy->collidesWithBlocks(blocks)) {
            fireboy->moveBy(5, 0);
        }

    }

}

void Level01::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
        return;

    switch (event->key()) {
        case Qt::Key_Right:
            direction += 1;
            m_timer.start();
            break;
        case Qt::Key_Left:
            direction -= 1;
            m_timer.start();
            break;
        case Qt::Key_Up:
            if(fireboy->onGround(blocks)) {
                velocityY = -9.0;
            }
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
            direction -= 1;
            if(direction == 0)
                m_timer.stop();
            break;
        case Qt::Key_Left:
            direction += 1;
            if(direction == 0)
                m_timer.stop();
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

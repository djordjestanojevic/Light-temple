#include "level01.h"

#include <iostream>

Level01::Level01(QWidget *parent)
    : QGraphicsScene(0, 0,  1280, 760, parent)
{

    initPlayField();

    direction = 0;

    m_timer.setInterval(20);
    connect(&m_timer, &QTimer::timeout, this, &Level01::movePlayer);

}

void Level01::initPlayField() {

    MakeMap();

    fireboy = new Player();
    fireboy->setPos(100, 600);
    this->addItem(fireboy);

    std::cout << blocks.length() << std::endl;

    while(!fireboy->collidesWithBlocks(blocks))
        fireboy->moveBy(0, 1);
}

void Level01::movePlayer() {

    if(direction == 1) {
        if(fireboy->pos().x() > 1220) {
            m_timer.stop();
            return;
        }

        fireboy->moveBy(5, 0);

    }

    if(direction == -1) {
        std::cout << fireboy->pos().x() << std::endl;
        if(fireboy->pos().x() < 5) {
            direction = 0;
            return;
        }

        fireboy->moveBy(-5, 0);

    }

}

void Level01::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Right:
            direction = 1;
            m_timer.start();
            break;
        case Qt::Key_Left:
            direction = -1;
            m_timer.start();
            break;
        default:
            break;
    }
}

void Level01::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Right:
            direction = 0;
            m_timer.stop();
            break;
        case Qt::Key_Left:
            direction = 0;
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
        std::cout << "dssd" << std::endl;
        std::string elem;
        int x;
        int y;
        f >> elem >> x >> y;
        if(elem == "Block")
        {
            QGraphicsPixmapItem *block = new QGraphicsPixmapItem;
            block->setPixmap(QPixmap("./Images/block").scaled(50, 50));
            block->setPos(x,y);
            addItem(block);
            blocks.append(block);
        }
        else
            break;
    }
}

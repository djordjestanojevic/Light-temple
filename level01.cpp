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

    makeMap();

    fireboy = new Player();
    fireboy->setPos(100, 600);

    while(!fireboy->collidesWithBlock(blocks))
        fireboy->moveBy(0, 1);
}

void Level01::movePlayer() {


    std::cout << direction << std::endl;

    if(direction == 1) {
        fireboy->moveBy(5, 0);

    }

    if(direction == -1) {
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

void Level01::makeMap() {


    background = this->addRect(0, 0, 1280,760);
    background->setBrush(QBrush(QPixmap("./Images/wall").scaled(600, 600)));

    std::ifstream f("C:/Users/Djordje/Desktop/build-Projekat-Desktop_Qt_5_10_1_MinGW_32bit-Release/release/map.txt");

    while(f.is_open()) {
        std::string type;
        int x;
        int y;
        f >> type >> x >> y;
        if(type == "Block") {
            std::cout << "sds" << std::endl;
            QGraphicsPixmapItem *block = new QGraphicsPixmapItem(QPixmap("./Images/block").scaled(50, 50));
            addItem(block);
            block->setPos(x ,y);
            blocks.append(block);
        }
        else
            break;
    }
}

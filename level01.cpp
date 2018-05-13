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

bool Level01::initPlayField() {

    background = this->addRect(0, 0, 1280,760);
    background->setBrush(QBrush(QPixmap("C:/Users/Djordje/Desktop/Projekat/Images/wall").scaled(600, 600)));

    ground = new QGraphicsPixmapItem(QPixmap("C:/Users/Djordje/Desktop/Projekat/Images/ground"));
    addItem(ground);
    ground->setPos(0, 700);

    fireboy = this->addPixmap(QPixmap("C:/Users/Djordje/Desktop/Projekat/Images/fireboy").scaled(55, 100));
    fireboy->setPos(100, 600);
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

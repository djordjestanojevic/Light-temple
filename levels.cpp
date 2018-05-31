#include "levels.h"
#include <iostream>

Levels::Levels(View *v, Title *t, QWidget *parent)
    : QGraphicsScene(parent)
{
    view = v;
    title = t;

    this->setSceneRect(0,0,1280,760);
    QString path = QCoreApplication::applicationDirPath() + "/Images/background";
    background = new QGraphicsPixmapItem(QPixmap(path).scaled(1280, 760));
    addItem(background);

    // Postavljamo dugme za start igre
    button01 = new QPushButton("Start");
    button01->setToolTip("Click to start");
    button01->setGeometry(QRect(this->width()/2 - 50, this->height()/2 + 100, 100, 32));
    addWidget(button01);
    connect(button01, SIGNAL(clicked()), this, SLOT(startProgram()));

    mainMenu = new QPushButton("Main Manu");
    mainMenu->setGeometry(QRect(this->width()/2 - 50, this->height()/2, 100, 32));
    addWidget(mainMenu);
    connect(mainMenu, SIGNAL(clicked()), title, SLOT(back()));
}


void Levels::startProgram() {

    view->setScene(new Level01("map.txt", this));
}

void Levels::nextLevel() {
}

void Levels::exitLevel() {

    view->setScene(this);
}

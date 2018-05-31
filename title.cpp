#include "title.h"
#include<QCoreApplication>

#include <iostream>

Title::Title(View *v, QWidget *parent)
    : QGraphicsScene(parent)
{

    view = v;

    // Dimenzije scene
    this->setSceneRect(0,0,1280,760);

    // Dodajemo pozadinu
    QString path = QCoreApplication::applicationDirPath() + "/Images/background";
    background = new QGraphicsPixmapItem(QPixmap(path).scaled(1280, 760));
    addItem(background);

    // Dodajemo logo
    path = QCoreApplication::applicationDirPath() + "/Images/icon";
    logo = new QGraphicsPixmapItem(QPixmap(path));
    logo->setScale(0.5);
    logo->setPos(this->width()/2 - 142, this->height()/2 - 120);
    addItem(logo);

    // Postavljamo dugme za start igre
    startButton = new QPushButton("", view);
    startButton->setFlat(true);
    startButton->setToolTip("Click to start");
    startButton->setGeometry(QRect(this->width()/2 - 50, this->height()/2 + 100, 100, 32));
    startButton->setIcon(QIcon(path));
    startButton->setIconSize(QSize(200,50));
    connect(startButton, SIGNAL(clicked()), this, SLOT(startProgram()));
    levels = new Levels(view, this);

    // Postavljamo dugme za ulaz u podesavanja
    settingsButton = new QPushButton("Settings", view);
    settingsButton->setToolTip("Open settings");
    settingsButton->setGeometry(QRect(this->width()/2 - 50, this->height()/2 + 150, 100, 32));
    connect(settingsButton, SIGNAL(clicked()), this, SLOT(goToSettings()));
    settings = new Settings(view, this);

    // Postavljamo dugme za izlaz iz igre
    quitButton = new QPushButton("Quit", view);
    quitButton->setToolTip("Quit program");
    quitButton->setGeometry(QRect(this->width()/2 - 50, this->height()/2 + 200, 100, 32));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(quitProgram()));
}

void Title::startProgram() {

    startButton->setVisible(false);
    settingsButton->setVisible(false);
    quitButton->setVisible(false);

    view->setScene(levels);
}

void Title::goToSettings() {

    startButton->setVisible(false);
    settingsButton->setVisible(false);
    quitButton->setVisible(false);

    view->setScene(settings);
}

void Title::quitProgram() {

    qApp->quit();
}

void Title::back() {

    startButton->setVisible(true);
    settingsButton->setVisible(true);
    quitButton->setVisible(true);

    view->setScene(this);
}

#include "title.h"

Title::Title(View *v, QWidget *parent)
    : QGraphicsScene(parent)
{

    view = v;

    view->setScene(this);

    // Dimenzije scene
    this->setSceneRect(0,0,1280,760);

    // Dodajemo pozadinu
    background = new QGraphicsPixmapItem(QPixmap("./Images/background").scaled(1280, 760));
    addItem(background);

    // Dodajemo logo
    logo = new QGraphicsPixmapItem(QPixmap("./Images/icon"));
    logo->setScale(0.5);
    logo->setPos(this->width()/2 - 142, this->height()/2 - 120);
    addItem(logo);

    // Postavljamo dugme za start igre
    startButton = new QPushButton("Start", view);
    startButton->setToolTip("Click to start");
    startButton->setGeometry(QRect(this->width()/2 - 50, this->height()/2 + 100, 100, 32));
    connect(startButton, SIGNAL(clicked()), this, SLOT(startProgram()));

    // Postavljamo dugme za ulaz u podesavanja
    settingsButton = new QPushButton("Settings", view);
    settingsButton->setToolTip("Open settings");
    settingsButton->setGeometry(QRect(this->width()/2 - 50, this->height()/2 + 150, 100, 32));
    connect(settingsButton, SIGNAL(clicked()), this, SLOT(goToSettings()));

    // Postavljamo dugme za izlaz iz igre
    quitButton = new QPushButton("Quit", view);
    quitButton->setToolTip("Quit program");
    quitButton->setGeometry(QRect(this->width()/2 - 50, this->height()/2 + 200, 100, 32));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(quitProgram()));
}

void Title::startProgram() {

    startButton->close();
    settingsButton->close();
    quitButton->close();

    view->setScene(new Level01());
}

void Title::goToSettings() {

    startButton->close();
    settingsButton->close();
    quitButton->close();

    view->setScene(new Settings());
}

void Title::quitProgram() {
    qApp->quit();
}

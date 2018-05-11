#include "scene.h"

Scene::Scene(View *view, QWidget *parent)
    : QGraphicsScene(parent),
      view(view)
{

    // Postavljamo pozadinu
    background = new QGraphicsPixmapItem(QPixmap("C:/Users/Djordje/Desktop/FAX/Razvoj softvera/Projekat/Images/background"));
    background->setScale(0.7);
    addItem(background);

    // Postavljamo logo
    logo = new QGraphicsPixmapItem(QPixmap("C:/Users/Djordje/Desktop/FAX/Razvoj softvera/Projekat/Images/icon"));
    logo->setScale(0.5);
    logo->setPos(530, 200);
    addItem(logo);

    view->setScene(this);

    // Postavljamo dugme za pocetak igre
    startButton = new QPushButton(view);
    startButton->setText("Start");
    startButton->setObjectName(QString("startButton"));
    startButton->setToolTip("Click to start");
    startButton->setGeometry(QRect(535, 475, 100, 32));
    connect(startButton, SIGNAL(clicked()), this, SLOT(startProgram()));

    // Postavlajmo dugme za izlaz iz igre
    quitButton = new QPushButton(view);
    quitButton->setText("Quit");
    quitButton->setObjectName(QString("quitButton"));
    quitButton->setToolTip("Quit program");
    quitButton->setGeometry(QRect(647, 475, 100, 32));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(quitProgram()));

}


void Scene::quitProgram(){

    qApp->quit();
}


void Scene::startProgram(){

    startButton->close();
    quitButton->close();

}

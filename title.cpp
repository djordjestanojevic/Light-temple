#include "title.h"
#include<QCoreApplication>

#include <iostream>

Title::Title(View *v, QWidget *parent)
    : QGraphicsScene(parent),
      view(v)
{

    // Dimenzije scene
    this->setSceneRect(0,0,1280,760);

    // Dodajemo pozadinu
    QString path = QCoreApplication::applicationDirPath() + "/Images/title/background";
    background = new QGraphicsPixmapItem(QPixmap(path).scaled(1280, 760));
    addItem(background);

    // Dodajemo logo
    path = QCoreApplication::applicationDirPath() + "/Images/icon";
    logo = new QGraphicsPixmapItem(QPixmap(path));
    logo->setScale(0.5);
    logo->setPos(this->width()/2 - 142, this->height()/2 - 300);
    addItem(logo);

    // Postavljamo dugme za start igre
    startButton = new QPushButton("");
    path = QCoreApplication::applicationDirPath() + "/Images/title/start2";
    startButton->setGeometry(QRect(QPoint(this->width()/2 - 125, this->height()/2 - 40), QSize(0, 0)));
    startButton->setFixedSize(220, 80);
    startButton->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; background: none; background-color: rgba(1, 1, 1, 0);}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    connect(startButton, SIGNAL(clicked()), this, SLOT(startProgram()));
    addWidget(startButton);
    levels = new Levels(view, this);

    // Postavljamo dugme za ulaz u podesavanja
    settingsButton = new QPushButton("");
    path = QCoreApplication::applicationDirPath() + "/Images/title/settings2";
    settingsButton->setGeometry(QRect(QPoint(this->width()/2 - 125, this->height()/2 + 35), QSize(0, 0)));
    settingsButton->setFixedSize(220, 80);
    settingsButton->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; background: none; background-color: rgba(1, 1, 1, 0);}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    connect(settingsButton, SIGNAL(clicked()), this, SLOT(goToSettings()));
    addWidget(settingsButton);
    settings = new Settings(view, this);

    // Postavljamo dugme za izlaz iz igre
    quitButton = new QPushButton("");
    path = QCoreApplication::applicationDirPath() + "/Images/title/exit2";
    quitButton->setGeometry(QRect(QPoint(this->width()/2 - 125, this->height()/2 + 110), QSize(0, 0)));
    quitButton->setFixedSize(220, 80);
    quitButton->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; background: none; background-color: rgba(1, 1, 1, 0);}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    connect(quitButton, SIGNAL(clicked()), this, SLOT(quitProgram()));
    addWidget(quitButton);

    QMediaPlayer *player = new QMediaPlayer();
    path = QCoreApplication::applicationDirPath() + "/Sound/click.mp3";
    player->setMedia(QUrl::fromLocalFile(path));
    player->setVolume(500);

    connect(startButton, &QPushButton::pressed, player, &QMediaPlayer::play);
    connect(settingsButton, &QPushButton::pressed, player, &QMediaPlayer::play);
    connect(quitButton, &QPushButton::pressed, player, &QMediaPlayer::play);
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

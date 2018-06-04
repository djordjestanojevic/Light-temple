#include "levels.h"
#include <iostream>

int Levels::lastUnlocked = 1;
int Levels::currentLevel = 1;
int Levels::levelStars[5];

Levels::Levels(View *v, Title *t, QWidget *parent)
    : QGraphicsScene(parent),
      view(v),
      title(t)
{
    // Ucitavanje broja zvezdica za svaki nivo i poslednji otkljucani nivo
    QString path = QCoreApplication::applicationDirPath() + "/levelStar.txt";
    std::ifstream f(path.toStdString(), std::ifstream::in);
    f >> Levels::lastUnlocked;
    for(int i = 0; i < 5; i++)
        f >> levelStars[i];


    // Postavljanje velicine scene i pozadine
    this->setSceneRect(0,0,1280,760);
    path = QCoreApplication::applicationDirPath() + "/Images/background";
    background = new QGraphicsPixmapItem(QPixmap(path).scaled(1280, 760));
    addItem(background);

    // Postavljamo dugme za prvi nivo
    button[0] = new QPushButton("");
    if(levelStars[0] == -1)
        path = QCoreApplication::applicationDirPath() + "/Images/levels/1";
    else
        path = QCoreApplication::applicationDirPath() + "/Images/levels/1" + QString::number(levelStars[0]);
    button[0]->setGeometry(QRect(QPoint(this->width()/3 - 80, this->height()/3), QSize(0, 0)));
    button[0]->setFixedSize(80, 80);
    button[0]->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; font-size: 30px; background-color: rgba(1, 1, 1, 0);}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    addWidget(button[0]);
    connect(button[0], SIGNAL(clicked()), this, SLOT(startLevel1()));



    // Postavljamo dugme za drugi nivo
    button[1] = new QPushButton("");
    if(levelStars[1] == -1)
        path = QCoreApplication::applicationDirPath() + "/Images/levels/2";
    else
        path = QCoreApplication::applicationDirPath() + "/Images/levels/2" + QString::number(levelStars[1]);
    button[1]->setGeometry(QRect(QPoint(this->width()/3 - 80 + 120 * 1, this->height()/3), QSize(0, 0)));
    button[1]->setFixedSize(80, 80);
    button[1]->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; font-size: 30px; background-color: rgba(1, 1, 1, 0);}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    addWidget(button[1]);
    connect(button[1], SIGNAL(clicked()), this, SLOT(startLevel2()));




    // Postavljamo dugme za treci nivo
    button[2] = new QPushButton("");
    if(levelStars[2] == -1)
        path = QCoreApplication::applicationDirPath() + "/Images/levels/3";
    else
        path = QCoreApplication::applicationDirPath() + "/Images/levels/3" + QString::number(levelStars[2]);
    button[2]->setGeometry(QRect(QPoint(this->width()/3 - 80 + 120 * 2, this->height()/3), QSize(0, 0)));
    button[2]->setFixedSize(80, 80);
    button[2]->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; font-size: 30px; background-color: rgba(1, 1, 1, 0);}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    addWidget(button[2]);
    connect(button[2], SIGNAL(clicked()), this, SLOT(startLevel3()));




    // Postavljamo dugme za cetvrti nivo
    button[3] = new QPushButton("");
    if(levelStars[3] == -1)
        path = QCoreApplication::applicationDirPath() + "/Images/levels/4";
    else
        path = QCoreApplication::applicationDirPath() + "/Images/levels/4" + QString::number(levelStars[3]);
    button[3]->setGeometry(QRect(QPoint(this->width()/3 - 80 + 120 * 3, this->height()/3), QSize(0, 0)));
    button[3]->setFixedSize(80, 80);
    button[3]->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; font-size: 30px; background-color: rgba(1, 1, 1, 0);}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    addWidget(button[3]);
    connect(button[3], SIGNAL(clicked()), this, SLOT(startLevel4()));


    // Postavljamo dugme za peti nivo
    button[4] = new QPushButton("");
    if(levelStars[4] == -1)
        path = QCoreApplication::applicationDirPath() + "/Images/levels/5";
    else
        path = QCoreApplication::applicationDirPath() + "/Images/levels/5" + QString::number(levelStars[4]);
    button[4]->setGeometry(QRect(QPoint(this->width()/3 - 80 + 120 * 4, this->height()/3), QSize(0, 0)));
    button[4]->setFixedSize(80, 80);
    button[4]->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; font-size: 30px; background-color: rgba(1, 1, 1, 0);}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    addWidget(button[4]);
    connect(button[4], SIGNAL(clicked()), this, SLOT(startLevel5()));

    // Postavljamo dugme za povratak u glavni meni
    mainMenu = new QPushButton("");
    path = QCoreApplication::applicationDirPath() + "/Images/levels/back";
    mainMenu->setGeometry(QRect(QPoint(this->width()/3 - 50 - 300, 2 * this->height()/3 + 100), QSize(0, 0)));
    mainMenu->setFixedSize(220, 80);
    mainMenu->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; font-size: 30px; background-color: rgba(1, 1, 1, 0);}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    addWidget(mainMenu);
    connect(mainMenu, SIGNAL(clicked()), title, SLOT(back()));

    // Postavljanje zvuka klika
    QMediaPlayer *player = new QMediaPlayer();
    path = QCoreApplication::applicationDirPath() + "/Sound/click.mp3";
    player->setMedia(QUrl::fromLocalFile(path));
    player->setVolume(500);

    connect(button[0], &QPushButton::pressed, player, &QMediaPlayer::play);
    connect(button[1], &QPushButton::pressed, player, &QMediaPlayer::play);
    connect(button[2], &QPushButton::pressed, player, &QMediaPlayer::play);
    connect(button[3], &QPushButton::pressed, player, &QMediaPlayer::play);
    connect(button[4], &QPushButton::pressed, player, &QMediaPlayer::play);
    connect(mainMenu, &QPushButton::pressed, player, &QMediaPlayer::play);
}

//Slotovi za postavljanje scene u zavisnosti od izabranog nivoa

void Levels::startLevel1() {
    currentLevel = 1;
    view->setScene(new Level01("map1.txt", this));
}

void Levels::startLevel2() {
    if(lastUnlocked < 2)
        return;
    currentLevel = 2;
    view->setScene(new Level01("map2.txt", this));
}

void Levels::startLevel3() {
    if(lastUnlocked < 3)
        return;
    currentLevel = 3;
    view->setScene(new Level01("map3.txt", this));
}

void Levels::startLevel4() {
    if(lastUnlocked < 4)
        return;
    currentLevel = 4;
    view->setScene(new Level01("map4.txt", this));
}

void Levels::startLevel5() {
    if(lastUnlocked < 5)
        return;
    currentLevel = 5;
    view->setScene(new Level01("map5.txt", this));
}


//Slot za prelazak na sledeci nivo i za povratak na izbor nivoa

void Levels::nextLevel() {
    if(currentLevel == 5) {
        view->setScene(this);
        return;
    }
    //Azuriranje zvezdica kod nivoa

    QString path = QCoreApplication::applicationDirPath() + "/levelStar.txt";
    std::ofstream f(path.toStdString());
    f << std::to_string(Levels::lastUnlocked) + " ";
    for(int i = 0; i < 5; i++)
        f << std::to_string(levelStars[i]) + " ";

    path = QCoreApplication::applicationDirPath() + "/Images/levels/" + QString::number(currentLevel) + QString::number(levelStars[currentLevel - 1]);
    button[currentLevel-1]->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; font-size: 30px; background-color: rgba(1, 1, 1, 0);}" +
                               "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    currentLevel++;
    view->setScene(new Level01("map" + QString::number(currentLevel) +".txt", this));
}



void Levels::exitLevel() {
    // Azuriranje vrednosti o zvezdicama

    QString path = QCoreApplication::applicationDirPath() + "/levelStar.txt";
    std::ofstream f(path.toStdString());
    f << std::to_string(Levels::lastUnlocked) + " ";
    for(int i = 0; i < 5; i++)
        f << std::to_string(levelStars[i]) + " ";

    if(levelStars[currentLevel - 1] != -1) {
        path = QCoreApplication::applicationDirPath() + "/Images/levels/" + QString::number(currentLevel) + QString::number(levelStars[currentLevel - 1]);
        button[currentLevel-1]->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; font-size: 30px; background-color: rgba(1, 1, 1, 0);}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    }

    view->setScene(this);
}

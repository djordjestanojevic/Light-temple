#include "settings.h"
int Settings::fireboyLeftKey = 16777234;
int Settings::fireboyRightKey = 16777236;
int Settings::fireboyUpKey = 16777235;
int Settings::watergirlLeftKey = 65;
int Settings::watergirlRightKey = 68;
int Settings::watergirlUpKey = 87;


Settings::Settings(View * v, Title *t, QWidget *parent)
    : QGraphicsScene(parent),
      view(v),
      title(t)
{

    this->setSceneRect(0,0,1280,760);
    QString path = QCoreApplication::applicationDirPath() + "/Images/background";
    background = new QGraphicsPixmapItem(QPixmap(path).scaled(1280, 760));
    addItem(background);

    path = QCoreApplication::applicationDirPath() + "/Images/fireboy";
    fireboyLogo = new QGraphicsPixmapItem(QPixmap(path));
    fireboyLogo->setScale(0.5);
    fireboyLogo->setPos(this->width()/3 - 80, this->height()/2 - 250);
    addItem(fireboyLogo);

    path = QCoreApplication::applicationDirPath() + "/Images/watergirl";
    watergirlLogo = new QGraphicsPixmapItem(QPixmap(path));
    watergirlLogo->setScale(0.5);
    watergirlLogo->setPos(2 * this->width()/3 - 80,  this->height()/2 - 250);
    addItem(watergirlLogo);

    fireboyUpKeyIndicator = 0;
    fireboyUp = new QPushButton("");
    path = QCoreApplication::applicationDirPath() + "/Images/settings/jump";
    fireboyUp->setGeometry(QRect(QPoint(this->width()/3 - 50, 400), QSize(0, 0)));
    fireboyUp->setFixedSize(80, 80);
    fireboyUp->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; font-size: 30px; background-color: rgba(1, 1, 1, 0);}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    addWidget(fireboyUp);
    connect(fireboyUp, SIGNAL(clicked()), this, SLOT(fireboyUpKeyUpdate()));

    fireboyLeftKeyIndicator = 0;
    fireboyLeft = new QPushButton("");
    path = QCoreApplication::applicationDirPath() + "/Images/settings/left";
    fireboyLeft->setGeometry(QRect(QPoint(this->width()/3 - 50 - 80, 450), QSize(0, 0)));
    fireboyLeft->setFixedSize(80, 80);
    fireboyLeft->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; font-size: 30px; background-color: rgba(1, 1, 1, 0);}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    addWidget(fireboyLeft);
    connect(fireboyLeft, SIGNAL(clicked()), this, SLOT(fireboyLeftKeyUpdate()));

    fireboyRightKeyIndicator = 0;
    fireboyRight = new QPushButton("");
    path = QCoreApplication::applicationDirPath() + "/Images/settings/right";
    fireboyRight->setGeometry(QRect(QPoint(this->width()/3 - 50 + 80, 450), QSize(0, 0)));
    fireboyRight->setFixedSize(80, 80);
    fireboyRight->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; font-size: 30px; background-color: rgba(1, 1, 1, 0);}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    addWidget(fireboyRight);
    connect(fireboyRight, SIGNAL(clicked()), this, SLOT(fireboyRightKeyUpdate()));

    watergirlUpKeyIndicator = 0;
    watergirlUp = new QPushButton("");
    path = QCoreApplication::applicationDirPath() + "/Images/settings/jump";
    watergirlUp->setGeometry(QRect(QPoint(2 * this->width()/3 - 50, 400), QSize(0, 0)));
    watergirlUp->setFixedSize(80, 80);
    watergirlUp->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; font-size: 30px; background-color: rgba(1, 1, 1, 0);}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    addWidget(watergirlUp);
    connect(watergirlUp, SIGNAL(clicked()), this, SLOT(watergirlUpKeyUpdate()));

    watergirlLeftKeyIndicator = 0;
    watergirlLeft = new QPushButton("");
    path = QCoreApplication::applicationDirPath() + "/Images/settings/left";
    watergirlLeft->setGeometry(QRect(QPoint(2 * this->width()/3 - 50 - 80, 450), QSize(0, 0)));
    watergirlLeft->setFixedSize(80, 80);
    watergirlLeft->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; font-size: 30px; background-color: rgba(1, 1, 1, 0);}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    addWidget(watergirlLeft);
    connect(watergirlLeft, SIGNAL(clicked()), this, SLOT(watergirlLeftKeyUpdate()));

    watergirlRightKeyIndicator = 0;
    watergirlRight = new QPushButton("");
    path = QCoreApplication::applicationDirPath() + "/Images/settings/right";
    watergirlRight->setGeometry(QRect(QPoint(2 * this->width()/3 - 50 + 80, 450), QSize(0, 0)));
    watergirlRight->setFixedSize(80, 80);
    watergirlRight->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; font-size: 30px; background-color: rgba(1, 1, 1, 0);}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    addWidget(watergirlRight);
    connect(watergirlRight, SIGNAL(clicked()), this, SLOT(watergirlRightKeyUpdate()));

    backToTitle = new QPushButton("");
    path = QCoreApplication::applicationDirPath() + "/Images/settings/back";
    backToTitle->setGeometry(QRect(QPoint(this->width()/2 - 110, this->height()/2 +200), QSize(0, 0)));
    backToTitle->setFixedSize(220, 80);
    backToTitle->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; font-size: 30px; background-color: rgba(1, 1, 1, 0);}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    addWidget(backToTitle);
    connect(backToTitle, SIGNAL(clicked()), title, SLOT(back()));

    QMediaPlayer *player = new QMediaPlayer();
    path = QCoreApplication::applicationDirPath() + "/Sound/click.mp3";
    player->setMedia(QUrl::fromLocalFile(path));
    player->setVolume(500);

    connect(fireboyUp, &QPushButton::pressed, player, &QMediaPlayer::play);
    connect(fireboyLeft, &QPushButton::pressed, player, &QMediaPlayer::play);
    connect(fireboyRight, &QPushButton::pressed, player, &QMediaPlayer::play);
    connect(watergirlLeft, &QPushButton::pressed, player, &QMediaPlayer::play);
    connect(watergirlRight, &QPushButton::pressed, player, &QMediaPlayer::play);
    connect(watergirlUp, &QPushButton::pressed, player, &QMediaPlayer::play);
    connect(backToTitle, &QPushButton::pressed, player, &QMediaPlayer::play);
}


void Settings::watergirlUpKeyUpdate(){
    watergirlUpKeyIndicator = 1;
}

void Settings::watergirlLeftKeyUpdate(){
    watergirlLeftKeyIndicator = 1;
}

void Settings::watergirlRightKeyUpdate(){
    watergirlRightKeyIndicator = 1;
}

void Settings::fireboyUpKeyUpdate(){
    fireboyUpKeyIndicator = 1;
}

void Settings::fireboyLeftKeyUpdate(){
    fireboyLeftKeyIndicator = 1;
}

void Settings::fireboyRightKeyUpdate(){
    fireboyRightKeyIndicator = 1;
}

void Settings::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
        return;
    if(fireboyLeftKeyIndicator) {
        fireboyLeftKeyIndicator = 0;
        if(event->key() != watergirlLeftKey && event->key() != watergirlRightKey &&
           event->key() != watergirlUpKey && event->key() != fireboyRightKey && event->key() != fireboyUpKey)
            fireboyLeftKey = event->key();
    }

    if(fireboyRightKeyIndicator) {
        fireboyRightKeyIndicator = 0;
        if(event->key() != watergirlLeftKey && event->key() != watergirlRightKey &&
                event->key() != watergirlUpKey && event->key() != fireboyLeftKey && event->key() != fireboyUpKey)
            fireboyRightKey = event->key();
    }

    if(fireboyUpKeyIndicator) {
        fireboyUpKeyIndicator = 0;
        if(event->key() != watergirlLeftKey && event->key() != watergirlRightKey &&
                event->key() != watergirlUpKey && event->key() != fireboyLeftKey && event->key() != fireboyRightKey)
            fireboyUpKey = event->key();
    }

    if(watergirlLeftKeyIndicator) {
        watergirlLeftKeyIndicator = 0;
        if(event->key() != fireboyUpKey && event->key() != watergirlRightKey &&
                event->key() != watergirlUpKey && event->key() != fireboyLeftKey && event->key() != fireboyRightKey)
            watergirlLeftKey = event->key();
    }

    if(watergirlRightKeyIndicator) {
        watergirlRightKeyIndicator = 0;
        if(event->key() != watergirlLeftKey && event->key() != fireboyUpKey &&
                event->key() != watergirlUpKey && event->key() != fireboyLeftKey && event->key() != fireboyRightKey)
            watergirlRightKey = event->key();
    }

    if(watergirlUpKeyIndicator) {
        watergirlUpKeyIndicator = 0;
        if(event->key() != watergirlLeftKey && event->key() != fireboyUpKey &&
                event->key() != watergirlRightKey && event->key() != fireboyLeftKey && event->key() != fireboyRightKey)
            watergirlUpKey = event->key();
    }

}

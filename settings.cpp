#include "settings.h"
int Settings::fireboyLeftKey = 16777234;
int Settings::fireboyRightKey = 16777236;
int Settings::fireboyUpKey = 16777235;
int Settings::watergirlLeftKey = 65;
int Settings::watergirlRightKey = 68;
int Settings::watergirlUpKey = 87;


Settings::Settings(View * v, Title *t, QWidget *parent)
    : QGraphicsScene(parent)
{
    view = v;
    title = t;

    this->setSceneRect(0,0,1280,760);
    QString path = QCoreApplication::applicationDirPath() + "/Images/background";
    background = new QGraphicsPixmapItem(QPixmap(path).scaled(1280, 760));
    addItem(background);

    path = QCoreApplication::applicationDirPath() + "/Images/fireboy";
    fireboyLogo = new QGraphicsPixmapItem(QPixmap(path));
    fireboyLogo->setScale(0.5);
    fireboyLogo->setPos(this->width()/2 - 260, this->height()/2 - 250);
    addItem(fireboyLogo);

    path = QCoreApplication::applicationDirPath() + "/Images/watergirl";
    watergirlLogo = new QGraphicsPixmapItem(QPixmap(path));
    watergirlLogo->setScale(0.5);
    watergirlLogo->setPos(this->width()/2 + 140, this->height()/2 - 250);
    addItem(watergirlLogo);

    fireboyUpKeyIndicator = 0;
    fireboyUp = new QPushButton("Jump key");
    fireboyUp->setToolTip("Click, then enter new jump key for fireboy");
    fireboyUp->setGeometry(QRect(400, 400, 100, 32));
    addWidget(fireboyUp);
    connect(fireboyUp, SIGNAL(clicked()), this, SLOT(fireboyUpKeyUpdate()));

    fireboyLeftKeyIndicator = 0;
    fireboyLeft = new QPushButton("Left key");
    fireboyLeft->setToolTip("Click, then enter new left key for fireboy");
    fireboyLeft->setGeometry(QRect(320,450, 100, 32));
    addWidget(fireboyLeft);
    connect(fireboyLeft, SIGNAL(clicked()), this, SLOT(fireboyLeftKeyUpdate()));

    fireboyRightKeyIndicator = 0;
    fireboyRight = new QPushButton("Right key");
    fireboyRight->setToolTip("Click, then enter new right key for fireboy");
    fireboyRight->setGeometry(QRect(480, 450, 100, 32));
    addWidget(fireboyRight);
    connect(fireboyRight, SIGNAL(clicked()), this, SLOT(fireboyRightKeyUpdate()));

    watergirlUpKeyIndicator = 0;
    watergirlUp = new QPushButton("Jump key");
    watergirlUp->setToolTip("Click, then enter new jump key for watergirl");
    watergirlUp->setGeometry(800, 400, 100, 32);
    addWidget(watergirlUp);
    connect(watergirlUp, SIGNAL(clicked()), this, SLOT(watergirlUpKeyUpdate()));

    watergirlLeftKeyIndicator = 0;
    watergirlLeft = new QPushButton("Left key");
    watergirlLeft->setToolTip("Click, then enter new left key for watergirl");
    watergirlLeft->setGeometry(720,  450, 100, 32);
    addWidget(watergirlLeft);
    connect(watergirlLeft, SIGNAL(clicked()), this, SLOT(watergirlLeftKeyUpdate()));

    watergirlRightKeyIndicator = 0;
    watergirlRight = new QPushButton("Right key");
    watergirlRight->setToolTip("Click, then enter new right key for watergirl");
    watergirlRight->setGeometry(880, 450, 100, 32);
    addWidget(watergirlRight);
    connect(watergirlRight, SIGNAL(clicked()), this, SLOT(watergirlRightKeyUpdate()));
    backToTitle = new QPushButton("Back to title");
    backToTitle->setGeometry(QRect(this->width()/2 -35, this->height()/2 +200, 100, 32));
    addWidget(backToTitle);
    connect(backToTitle, SIGNAL(clicked()), title, SLOT(back()));
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
        fireboyLeftKey = event->key();
    }

    if(fireboyRightKeyIndicator) {
        fireboyRightKeyIndicator = 0;
        fireboyRightKey = event->key();
    }

    if(fireboyUpKeyIndicator) {
        fireboyUpKeyIndicator = 0;
        fireboyUpKey = event->key();
    }

    if(watergirlLeftKeyIndicator) {
        watergirlLeftKeyIndicator = 0;
        watergirlLeftKey = event->key();
    }

    if(watergirlRightKeyIndicator) {
        watergirlRightKeyIndicator = 0;
        watergirlRightKey = event->key();
    }

    if(watergirlUpKeyIndicator) {
        watergirlUpKeyIndicator = 0;
        watergirlUpKey = event->key();
    }

}

#include "level01.h"

#include "settings.h"
Level01::Level01(QString str, Levels *l, QWidget *parent)
    : QGraphicsScene(0, 0,  1280, 760, parent),
      pauseOnOff(0)
{
    levels = l;
    directionFireboy = 0;
    directionWatergirl = 0;

    velocityFireboy = 0;
    velocityWatergirl = 0;

    MakeMap(str);
    initPlayers();

    gravityTimerID = startTimer(19.5);

    timerFireboy.setInterval(20);
    connect(&timerFireboy, &QTimer::timeout, this, &Level01::moveFireboy);

    timerWatergirl.setInterval(20);
    connect(&timerWatergirl, &QTimer::timeout, this, &Level01::moveWatergirl);

    timerElevator.setInterval(20);
    connect(&timerElevator, &QTimer::timeout, this, &Level01::moveElevator);
    timerElevator.start();

    timerCount = 0;
    timer.setInterval(1000);
    connect(&timer, QTimer::timeout, this, &Level01::timerFunc);
    timer.start();
}

void Level01::initPlayers() {
    watergirl = new Player(QString(QCoreApplication::applicationDirPath() + "/Images/watergirl"));
    watergirl->setPos(100,570);
    this->addItem(watergirl);

    while(watergirl->collidesWithBlocks(blocks) == NULL) {
        watergirl->moveBy(0, 1);
    }
    watergirl->moveBy(0, -1);

    fireboy = new Player(QString(QCoreApplication::applicationDirPath() + "/Images/fireboy"));
    fireboy->setPos(100, 660);
    this->addItem(fireboy);

    while(fireboy->collidesWithBlocks(blocks) == NULL) {
        fireboy->moveBy(0, 1);
    }
    fireboy->moveBy(0, -1);
}

void Level01::timerEvent(QTimerEvent *event) {
    if(event->timerId() == gravityTimerID) {
        // Gravitacija za fireboy-a
        velocityFireboy += 0.5;
        fireboy->moveBy(0, velocityFireboy);

        if(fireboy->collidesWithBlocks(blocks) || fireboy->collidesWithBoxes(boxes)) {
            fireboy->moveBy(0, -velocityFireboy);
            velocityFireboy = 0;
        }

        // Gravitacija za watrgirl
        velocityWatergirl += 0.5;
        watergirl->moveBy(0, velocityWatergirl);

        if(watergirl->collidesWithBlocks(blocks)) {
            watergirl->moveBy(0, -velocityWatergirl);
            velocityWatergirl = 0;
        }

        // Gravitacija za box elemente
        for(int i = 0; i < boxes.length(); i ++) {
            velocityBox[i] += 0.5;
            boxes[i]->moveBy(0, velocityBox[i]);

            for(int j = 0; j < blocks.length(); j++) {
                if(boxes[i] == blocks[j]) {
                    continue;
                }

                if(boxes[i]->collidesWithItem(blocks[j])) {
                    boxes[i]->moveBy(0, -velocityBox[i]);
                    velocityBox[i] = 0;
                }
            }
        }



        // Provera da li su dosli do kraja nivoa
        if((fireboy->collidesWithItem(doors[0]) && watergirl->collidesWithItem(doors[1])) ||
                (fireboy->collidesWithItem(doors[1]) && watergirl->collidesWithItem(doors[0]))) {

            levelEnd();
        }

        // Kraj igre u slucaju dodira sa nekom tecnosti
        if(fireboy->collidesWithFluid(acid, water) || watergirl->collidesWithFluid(acid, lava)) {
            gameOver();
        }
    }
}

void Level01::moveFireboy() {

    if(directionFireboy == 1) {
        fireboy->moveBy(5, 0);

        for(int i = 0; i < levers.length(); i++) {
            bool col = fireboy->collidesWithItem(levers[i].button) && !watergirl->collidesWithItem(levers[i].button);
            if(col && levers[i].buttonPos < 30) {
                levers[i].button->moveBy(5, 0);
                levers[i].buttonPos += 5;
            }
            else if(col && levers[i].buttonPos == 30) {
                fireboy->moveBy(-5, 0);
                levers[i].onOff = 1;
            }
        }

        QGraphicsPixmapItem *collidedBox = fireboy->collidesWithBoxes(boxes);
        if(collidedBox != NULL){
            collidedBox->moveBy(5, 0);
            int i;
            for(i = 0; i < blocks.length(); i++){
                if(collidedBox->collidesWithItem(blocks[i]) && blocks[i] != collidedBox){
                    fireboy->moveBy(-5,0);
                    collidedBox->moveBy(-5, 0);
                }
            }
        }

        if(fireboy->collidesWithBlocks(blocks)) {
            fireboy->moveBy(-5, 0);
        }
    }

    if(directionFireboy == -1) {
        fireboy->moveBy(-5, 0);

        // Kolizija fireboy-a sa rucicama pri kretanju u levo
        for(int i = 0; i < levers.length(); i++) {
            bool col = fireboy->collidesWithItem(levers[i].button) && !watergirl->collidesWithItem(levers[i].button);
            if(col && levers[i].buttonPos > 0) {
                levers[i].button->moveBy(-5, 0);
                levers[i].buttonPos -= 5;
            }
            else if(col && levers[i].buttonPos == 0) {
                fireboy->moveBy(5, 0);
                levers[i].onOff = 0;
            }
        }

        QGraphicsPixmapItem *collidedBox = fireboy->collidesWithBoxes(boxes);
        if(collidedBox != NULL){
            collidedBox->moveBy(-5, 0);
            int i;
            for(i = 0; i < blocks.length(); i++){
                if(collidedBox->collidesWithItem(blocks[i]) && blocks[i] != collidedBox){
                    fireboy->moveBy(5, 0);
                    collidedBox->moveBy(5, 0);
                }
            }
        }

        if(fireboy->collidesWithBlocks(blocks)) {
            fireboy->moveBy(5, 0);
        }
    }


    QGraphicsPixmapItem * diamond;
    if(fireboy->collidesWithDiamonds(diamonds)){
        diamond=fireboy->collidesWithDiamonds(diamonds);
        diamond->hide();
        numOfDiamonds+=1;
    }


    QGraphicsPixmapItem * redGem;
    if(fireboy->collidesWithRedGems(redGems)){
        redGem=fireboy->collidesWithDiamonds(redGems);
        redGem->hide();
        numOfRedGems+=1;
    }



}

void Level01::moveWatergirl() {

    if(directionWatergirl == 1) {
        watergirl->moveBy(5, 0);

        for(int i = 0; i < levers.length(); i++) {
            bool col = watergirl->collidesWithItem(levers[i].button) && !fireboy->collidesWithItem(levers[i].button);
            if(col && levers[i].buttonPos < 30) {
                levers[i].button->moveBy(5, 0);
                levers[i].buttonPos += 5;
            }
            else if(col && levers[i].buttonPos == 30) {
                watergirl->moveBy(-5, 0);
                levers[i].onOff = 1;
            }
        }

        QGraphicsPixmapItem *collidedBox = watergirl->collidesWithBoxes(boxes);
        if(collidedBox != NULL){
            collidedBox->moveBy(5, 0);
            int i;
            for(i = 0; i < blocks.length(); i++){
                if(collidedBox->collidesWithItem(blocks[i]) && blocks[i] != collidedBox){
                    watergirl->moveBy(-5,0);
                    collidedBox->moveBy(-5, 0);
                }
            }
        }

        if(watergirl->collidesWithBlocks(blocks)) {
            watergirl->moveBy(-5, 0);
        }

    }

    if(directionWatergirl == -1) {
        watergirl->moveBy(-5, 0);

        for(int i = 0; i < levers.length(); i++) {
            bool col = watergirl->collidesWithItem(levers[i].button) && !fireboy->collidesWithItem(levers[i].button);
            if(col && levers[i].buttonPos > 0) {
                levers[i].button->moveBy(-5, 0);
                levers[i].buttonPos -= 5;
            }
            else if(col && levers[i].buttonPos == 0) {
                watergirl->moveBy(5, 0);
                levers[i].onOff = 0;
            }
        }

        QGraphicsPixmapItem *collidedBox = watergirl->collidesWithBoxes(boxes);
        if(collidedBox != NULL){
            collidedBox->moveBy(-5, 0);
            int i;
            for(i = 0; i < blocks.length(); i++){
                if(collidedBox->collidesWithItem(blocks[i]) && blocks[i] != collidedBox){
                    watergirl->moveBy(5, 0);
                    collidedBox->moveBy(5, 0);
                }
            }
        }

        if(watergirl->collidesWithBlocks(blocks)) {
            watergirl->moveBy(5, 0);
        }

    }


    QGraphicsPixmapItem * diamond;
    if(watergirl->collidesWithDiamonds(diamonds)){
        diamond=watergirl->collidesWithDiamonds(diamonds);
        diamond->hide();
        numOfDiamonds+=1;
    }

    QGraphicsPixmapItem * blueGem;
    if(watergirl->collidesWithBlueGems(blueGems)){
        blueGem=watergirl->collidesWithBlueGems(blueGems);
        blueGem->hide();
        numOfBlueGems+=1;
    }

}


void Level01::moveElevator() {

    for(int i = 0; i < pushers.length(); i++) {

        bool but1 = fireboy->collidesWithItem(pushers[i].button1) || watergirl->collidesWithItem(pushers[i].button1);
        bool but2 = fireboy->collidesWithItem(pushers[i].button2) || watergirl->collidesWithItem(pushers[i].button2);
        bool elev = fireboy->collidesWithItem(pushers[i].elevator) || watergirl->collidesWithItem(pushers[i].elevator);

        if((but1 || but2) && pushers[i].pos < 90 && !elev) {

            pushers[i].elevator->moveBy(0, 1);
            pushers[i].pos++;
        }
        else if(!(but1 || but2) && pushers[i].pos > 0) {
            pushers[i].elevator->moveBy(0, -1);


            if(fireboy->collidesWithItem(pushers[i].elevator))
                fireboy->moveBy(0, -1);

            if(watergirl->collidesWithItem(pushers[i].elevator))
                watergirl->moveBy(0, -1);



            pushers[i].pos--;
        }


    }

    for(int i = 0; i < levers.length(); i++) {

        bool elev = fireboy->collidesWithItem(levers[i].elevator) || watergirl->collidesWithItem(levers[i].elevator);

        if(levers[i].onOff == 1 && levers[i].elevatorPos < 90 && !elev) {

            levers[i].elevator->moveBy(0, 1);
            levers[i].elevatorPos++;
        }
        else if(levers[i].onOff == 0 && levers[i].elevatorPos > 0) {
            levers[i].elevator->moveBy(0, -1);


            if(fireboy->collidesWithItem(levers[i].elevator))
                fireboy->moveBy(0, -1);

            if(watergirl->collidesWithItem(levers[i].elevator))
                watergirl->moveBy(0, -1);

            levers[i].elevatorPos--;
        }

        if(levers[i].onOff == 1 && levers[i].buttonPos < 30) {
            levers[i].button->moveBy(5, 0);
            levers[i].buttonPos += 5;
            if(fireboy->collidesWithItem(levers[i].button) || watergirl->collidesWithItem(levers[i].button)) {
                levers[i].button->moveBy(-5, 0);
                levers[i].buttonPos -= 5;
            }
        }
        else if(levers[i].onOff == 0 && levers[i].buttonPos > 0) {
                levers[i].button->moveBy(-5, 0);
                levers[i].buttonPos -= 5;
                if(fireboy->collidesWithItem(levers[i].button) || watergirl->collidesWithItem(levers[i].button)) {
                    levers[i].button->moveBy(5, 0);
                    levers[i].buttonPos += 5;
                }
            }


    }


}

void Level01::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
        return;

    if (event->key()==Settings::fireboyRightKey){
            directionFireboy += 1;
            timerFireboy.start();
    }
    if (event->key()==Settings::fireboyLeftKey){
            directionFireboy -= 1;
            timerFireboy.start();
    }
    if(event->key()==Settings::fireboyUpKey){
            if(fireboy->onGround(blocks)) {
                velocityFireboy = -9.0;
            }
    }
     if(event->key()==Settings::watergirlRightKey){
         directionWatergirl += 1;
         timerWatergirl.start();
     }

     if(event->key()==Settings::watergirlLeftKey){
         directionWatergirl -= 1;
         timerWatergirl.start();
     }
     if(event->key()==Settings::watergirlUpKey) {
            if(watergirl->onGround(blocks)) {
                velocityWatergirl = -9.0;
            }
     }
     if(event->key()== Qt::Key_Escape)
            pause();

}
void Level01::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
        return;

    if(event->key()==Settings::watergirlRightKey){
        directionWatergirl -= 1;
        if(directionWatergirl == 0)
            timerWatergirl.stop();
    }

    if(event->key()==Settings::watergirlLeftKey){
        directionWatergirl += 1;
        if(directionWatergirl == 0)
            timerWatergirl.stop();
    }
    if (event->key()==Settings::fireboyRightKey){
        directionFireboy -= 1;
        if(directionFireboy == 0)
            timerFireboy.stop();
    }
    if (event->key()==Settings::fireboyLeftKey){
        directionFireboy += 1;
        if(directionFireboy == 0)
            timerFireboy.stop();
    }

}

void Level01::MakeMap(QString str) {

    background = this->addRect(0, 0, 1280,760);
    QString path = QCoreApplication::applicationDirPath() + "/Images/wall";

    background->setBrush(QBrush(QPixmap(path).scaled(600, 600)));

    path = QCoreApplication::applicationDirPath() + "/"+str;
    std::ifstream f(path.toStdString(), std::ifstream::in);
    while(f.is_open())
    {
        std::string elem;
        int x;
        int y;
        f >> elem >> x >> y;


        if(elem[0] == '/' && elem[1] == '/')
            continue;

        if(elem == "Block" )
        {
            QGraphicsPixmapItem *block = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/block";
            block->setPixmap(QPixmap(path).scaled(30, 30));
            block->setPos(x,y);
            addItem(block);
            blocks.append(block);
        }
        else if(elem == "BlockCut")
        {
            QGraphicsPixmapItem *l = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/blockCut";
            l->setPixmap(QPixmap(path).scaled(30, 10));
            l->setPos(x,y);
            addItem(l);
            blocks.append(l);
        }
        else if(elem == "Lava")
        {
            QGraphicsPixmapItem *l = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/lava";
            l->setPixmap(QPixmap(path).scaled(30, 29));
            l->setPos(x,y);
            addItem(l);
            lava.append(l);
        }
        else if(elem == "Water")
        {
            QGraphicsPixmapItem *w = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/water";
            w->setPixmap(QPixmap(path).scaled(30, 25));
            w->setPos(x,y + 1);
            addItem(w);
            water.append(w);
        }
        else if(elem == "Acid")
        {
            QGraphicsPixmapItem *w = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/acid";
            w->setPixmap(QPixmap(path).scaled(30, 25));
            w->setPos(x,y + 4);
            addItem(w);
            acid.append(w);
        }
        else if(elem == "Door") {
            QGraphicsPixmapItem *w = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/doors";
            w->setPixmap(QPixmap(path).scaled(90, 90));
            w->setPos(x,y);
            addItem(w);
            doors.append(w);
        }
        else if(elem == "Pusher") {
            QGraphicsPixmapItem *w = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/button";
            w->setPixmap(QPixmap(path).scaled(60, 30));
            w->setPos(x,y);
            addItem(w);

            f >> x >> y;
            QGraphicsPixmapItem *v = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/button";
            v->setPixmap(QPixmap(path).scaled(60, 30));
            v->setPos(x,y);
            addItem(v);

            f >> x >> y;
            QGraphicsPixmapItem *r = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/elevator";
            r->setPixmap(QPixmap(path).scaled(120, 25));
            r->setPos(x,y);
            addItem(r);

            blocks.append(r);

            pusher p;
            p.button1 = w;
            p.button2 = v;
            p.elevator = r;
            p.pos = 0;

            pushers.append(p);
        }
        else if(elem == "Lever") {
            QGraphicsPixmapItem *w = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/elevator";
            w->setPixmap(QPixmap(path).scaled(15, 30));
            w->setPos(x,y);
            addItem(w);

            f >> x >> y;
            QGraphicsPixmapItem *r = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/elevator";
            r->setPixmap(QPixmap(path).scaled(120, 25));
            r->setPos(x,y);
            addItem(r);

            blocks.append(w);
            blocks.append(r);

            lever l;
            l.button = w;
            l.elevator = r;
            l.buttonPos = 0;
            l.elevatorPos = 0;
            l.onOff = 0;

            levers.append(l);
        }
        else if(elem == "Box")
        {
            QGraphicsPixmapItem *w = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/box";
            w->setPixmap(QPixmap(path).scaled(30, 30));
            w->setPos(x,y-4);
            addItem(w);

            boxPosition.append(QPointF(x,y-4));
            velocityBox.append(0);
            blocks.append(w);
            boxes.append(w);
        }
        else if(elem == "Diamond")
        {
            QGraphicsPixmapItem *w = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/diamond";
            w->setPixmap(QPixmap(path).scaled(60, 30));
            w->setPos(x,y-4);
            addItem(w);
            diamonds.append(w);
        }
        else if(elem == "BlueGem")
        {
            QGraphicsPixmapItem *w = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/bluegem";
            w->setPixmap(QPixmap(path).scaled(30, 30));
            w->setPos(x,y-4);
            addItem(w);
            blueGems.append(w);
        }
        else if(elem == "RedGem")
        {
            QGraphicsPixmapItem *w = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/redgem";
            w->setPixmap(QPixmap(path).scaled(30, 25));
            w->setPos(x,y-4);
            addItem(w);
            redGems.append(w);
        }
        else
            break;
    }


    pauseGame = new QPushButton("00:00");
    pauseGame->setGeometry(QRect(this->width()/2 - 50, 0, 100, 30));
    pauseGame->setStyleSheet("border: 1px solid #000000; background: rgb(139,69,19); font-size: 22px; font-family: cursive; border-radius: 5px;");
    addWidget(pauseGame);
    connect(pauseGame, SIGNAL(clicked()), SLOT(pauseOnTimer()));

}

void Level01::levelEnd() {
    gravityTimerID--;
    disconnect(&timerFireboy, &QTimer::timeout, this, &Level01::moveFireboy);
    disconnect(&timerWatergirl, &QTimer::timeout, this, &Level01::moveWatergirl);
    disconnect(&timerElevator, &QTimer::timeout, this, &Level01::moveElevator);
    timer.stop();

    endWindow = new QWidget();
    endWindow->setFixedSize(450, 400);QString path = QCoreApplication::applicationDirPath() + "/Images/levelFinished/";
    endWindow->setStyleSheet("border-image: url(" + path + "background" + ") 0 0 0 0 stretch stretch; background-image: url(" + path + "bg" + "); border-width: 0px; background-position: center;");

    endWindow->setFixedSize(400, 400);
    endWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setSpacing(50);
    layout->setContentsMargins(50, 200, 50, 50);

    nextLevel = new QPushButton("Next level", endWindow);
    path = QCoreApplication::applicationDirPath() + "/Images/levelFinished/next";
    nextLevel->setFixedSize(80, 80);
    nextLevel->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; background: none;}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    layout->addWidget(nextLevel);

    exitToManu = new QPushButton("Exit", endWindow);
    path = QCoreApplication::applicationDirPath() + "/Images/levelFinished/menu";
    exitToManu->setFixedSize(80, 80);
    exitToManu->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; background: none;}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    layout->addWidget(exitToManu);

    repeatThisLevel = new QPushButton("Repeat level", endWindow);
    path = QCoreApplication::applicationDirPath() + "/Images/levelFinished/restart";
    repeatThisLevel->setFixedSize(80, 80);
    repeatThisLevel->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; background: none;}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    layout->addWidget(repeatThisLevel);

    endWindow->setLayout(layout);

    connect(nextLevel, SIGNAL(clicked()), levels, SLOT(nextLevel()));
    connect(nextLevel, SIGNAL(clicked()), endWindow, SLOT(close()));
    connect(exitToManu, SIGNAL(clicked()), levels, SLOT(exitLevel()));
    connect(exitToManu, SIGNAL(clicked()), endWindow, SLOT(close()));
    connect(repeatThisLevel, SIGNAL(clicked()), this, SLOT(repeatLevel()));
    connect(repeatThisLevel, SIGNAL(clicked()), endWindow, SLOT(close()));

    endWindow->show();

}

void Level01::gameOver() {
    gravityTimerID--;
    disconnect(&timerFireboy, &QTimer::timeout, this, &Level01::moveFireboy);
    disconnect(&timerWatergirl, &QTimer::timeout, this, &Level01::moveWatergirl);
    disconnect(&timerElevator, &QTimer::timeout, this, &Level01::moveElevator);
    timer.stop();

    endWindow = new QWidget();
    endWindow->setFixedSize(450, 400);QString path = QCoreApplication::applicationDirPath() + "/Images/gameOver/";
    endWindow->setStyleSheet("border-image: url(" + path + "background" + ") 0 0 0 0 stretch stretch; background-image: url(" + path + "bg" + "); border-width: 0px; background-position: center;");

    endWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setSpacing(50);
    layout->setContentsMargins(50, 200, 50, 50);

    repeatThisLevel = new QPushButton("", endWindow);
    path = QCoreApplication::applicationDirPath() + "/Images/gameOver/restart";
    repeatThisLevel->setFixedSize(80, 80);
    repeatThisLevel->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; background: none;}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    layout->addWidget(repeatThisLevel);

    exitToManu = new QPushButton("", endWindow);
    path = QCoreApplication::applicationDirPath() + "/Images/gameOver/menu";
    exitToManu->setFixedSize(80, 80);
    exitToManu->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; background: none;}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    layout->addWidget(exitToManu);

    endWindow->setLayout(layout);

    connect(repeatThisLevel, SIGNAL(clicked()), this, SLOT(repeatLevel()));
    connect(repeatThisLevel, SIGNAL(clicked()), endWindow, SLOT(close()));

    connect(exitToManu, SIGNAL(clicked()), levels, SLOT(exitLevel()));
    connect(exitToManu, SIGNAL(clicked()), endWindow, SLOT(close()));

    endWindow->show();

}

void Level01::repeatLevel() {
    watergirl->setPos(100,570);
    while(watergirl->collidesWithBlocks(blocks) == NULL) {
        watergirl->moveBy(0, 1);
    }
    watergirl->moveBy(0, -1);

    fireboy->setPos(100, 660);
    while(fireboy->collidesWithBlocks(blocks) == NULL) {
        fireboy->moveBy(0, 1);
    }
    fireboy->moveBy(0, -1);

    directionFireboy = 0;
    directionWatergirl = 0;

    gravityTimerID++;
    connect(&timerFireboy, &QTimer::timeout, this, &Level01::moveFireboy);
    connect(&timerWatergirl, &QTimer::timeout, this, &Level01::moveWatergirl);
    connect(&timerElevator, &QTimer::timeout, this, &Level01::moveElevator);

    for(int i = 0; i < levers.length(); i++) {
        levers[i].button->moveBy(-levers[i].buttonPos, 0);
        levers[i].buttonPos = 0;

        levers[i].elevator->moveBy(0, -levers[i].elevatorPos);
        levers[i].elevatorPos = 0;

        levers[i].onOff = 0;
    }

    for(int i = 0; i < boxes.length(); i++) {
        boxes[i]->setPos(boxPosition[i]);
    }

    pauseGame->setText("00:00");
    timerCount = 0;
    timer.start();


    for(int i = 0; i < blueGems.length(); i++) {
       blueGems[i]->show();
    }
    for(int i = 0; i < redGems.length(); i++) {
       redGems[i]->show();
    }
    for(int i = 0; i < diamonds.length(); i++) {
       diamonds[i]->show();
    }
    numOfDiamonds=0;
    numOfRedGems=0;
    numOfBlueGems=0;
}

void Level01::pause() {
    gravityTimerID--;
    disconnect(&timerFireboy, &QTimer::timeout, this, &Level01::moveFireboy);
    disconnect(&timerWatergirl, &QTimer::timeout, this, &Level01::moveWatergirl);
    disconnect(&timerElevator, &QTimer::timeout, this, &Level01::moveElevator);
    timer.stop();

    endWindow = new QWidget();
    endWindow->setFixedSize(500, 400);
    QString path = QCoreApplication::applicationDirPath() + "/Images/pause/";
    endWindow->setStyleSheet("border-image: url(" + path + "background" + ") 0 0 0 0 stretch stretch; background-image: url(" + path + "bg" + "); border-width: 0px; background-position: center;");

    endWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setSpacing(50);
    layout->setContentsMargins(50, 200, 50, 50);

    repeatThisLevel = new QPushButton("", endWindow);
    path = QCoreApplication::applicationDirPath() + "/Images/pause/restart";
    repeatThisLevel->setFixedSize(80, 80);
    repeatThisLevel->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; background: none;}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    layout->addWidget(repeatThisLevel);

    exitToManu = new QPushButton("", endWindow);
    path = QCoreApplication::applicationDirPath() + "/Images/pause/menu";
    exitToManu->setFixedSize(80, 80);
    exitToManu->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; background: none;}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    layout->addWidget(exitToManu);

    resume = new QPushButton("", endWindow);
    path = QCoreApplication::applicationDirPath() + "/Images/pause/play";
    resume->setFixedSize(80, 80);
    resume->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; background: none;}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    layout->addWidget(resume);

    endWindow->setLayout(layout);

    endWindow->show();
    connect(repeatThisLevel, SIGNAL(clicked()), this, SLOT(repeatLevel()));
    connect(repeatThisLevel, SIGNAL(clicked()), endWindow, SLOT(close()));

    connect(exitToManu, SIGNAL(clicked()), levels, SLOT(exitLevel()));
    connect(exitToManu, SIGNAL(clicked()), endWindow, SLOT(close()));

    connect(resume, SIGNAL(clicked()), this, SLOT(resumeLevel()));
    connect(resume, SIGNAL(clicked()), endWindow, SLOT(close()));

}

void Level01::resumeLevel() {

    gravityTimerID++;
    connect(&timerFireboy, &QTimer::timeout, this, &Level01::moveFireboy);
    connect(&timerWatergirl, &QTimer::timeout, this, &Level01::moveWatergirl);
    connect(&timerElevator, &QTimer::timeout, this, &Level01::moveElevator);
    timer.start();

    endWindow->close();
}

void Level01::timerFunc() {
    timerCount++;
    QString s = "";
    if(timerCount/60 < 10)
        s.append("0");
    s.append(QString::number(timerCount/60));
    s.append(":");
    if(timerCount%60 < 10)
        s.append("0");
    s.append(QString::number(timerCount%60));

    pauseGame->setText(s);

}

void Level01::pauseOnTimer() {
    pause();
}

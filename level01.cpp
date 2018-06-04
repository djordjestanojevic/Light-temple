#include "level01.h"
#include "settings.h"

Level01::Level01(QString str, Levels *l, QWidget *parent)
    : QGraphicsScene(0, 0,  1280, 760, parent),
      levels(l),
      velocityFireboy(0),
      velocityWatergirl(0),
      directionFireboy(0),
      directionWatergirl(0),
      numOfDiamonds(0),
      numOfRedGems(0),
      numOfBlueGems(0)
{

    MakeMap(str);
    initPlayers();

    gravityTimerID = startTimer(19.5);

//    run = startTimer(100);

    // Postavljanje kretanja i brzine kretanja igraca i lifta

    timerFireboy.setInterval(19);
    connect(&timerFireboy, &QTimer::timeout, this, &Level01::moveFireboy);

    timerWatergirl.setInterval(19);
    connect(&timerWatergirl, &QTimer::timeout, this, &Level01::moveWatergirl);

    timerElevator.setInterval(20);
    connect(&timerElevator, &QTimer::timeout, this, &Level01::moveElevator);
    timerElevator.start();

    // Postavljanje tajmera za vreme

    timerCount = 0;
    timer.setInterval(1000);
    connect(&timer, &QTimer::timeout, this, &Level01::timerFunc);
    timer.start();
}




void Level01::initPlayers() {

    watergirl = new Player(QString(QCoreApplication::applicationDirPath() + "/Images/watergirl"));
    watergirl->setPos(100,570);
    this->addItem(watergirl);


    fireboy = new Player(QString(QCoreApplication::applicationDirPath() + "/Images/fireboy"));
    fireboy->setPos(100, 660);
    this->addItem(fireboy);

    //Igrac se pomera nagore sve dok je u koliziji sa blokom

    while(watergirl->collidesWithBlocks(blocks) != NULL) {
        watergirl->moveBy(0, -1);
    }


    while(fireboy->collidesWithBlocks(blocks) != NULL) {
        fireboy->moveBy(0, -1);
    }

    // Naknadno ubacen deo koda, nalazi se ovde zbog rasporeda elemenata

    for(int i = 0; i < acid.length(); i++)
        addItem(acid[i]);
    for(int i = 0; i < water.length(); i++)
        addItem(water[i]);
    for(int i = 0; i < lava.length(); i++)
        addItem(lava[i]);
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
            watergirl->hide();
            fireboy->hide();
            gameOver();
        }



    }
//    else if(run == event->timerId()) {
//        fireboy->nextFrame();
//        watergirl->nextFrame();
//    }
}

void Level01::moveFireboy() {

    if(directionFireboy == 1) {
        fireboy->moveBy(5, 0);

        //Obrada kolizije sa rucicom pri kretanju
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
        // Obrada kolizije sa box elementom

        QGraphicsPixmapItem *collidedBox = fireboy->collidesWithBoxes(boxes);
        if(collidedBox != NULL){
            collidedBox->moveBy(5, 0);
            int i;
            for(i = 0; i < blocks.length(); i++){
                if((collidedBox->collidesWithItem(blocks[i]) && blocks[i] != collidedBox) || watergirl->collidesWithBoxes(boxes) != NULL){
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
                if((collidedBox->collidesWithItem(blocks[i]) && blocks[i] != collidedBox) || watergirl->collidesWithBoxes(boxes) != NULL){
                    fireboy->moveBy(5, 0);
                    collidedBox->moveBy(5, 0);
                }
            }
        }

        if(fireboy->collidesWithBlocks(blocks)) {
            fireboy->moveBy(5, 0);
        }
    }

    // Obrada kolizije sa dijamantima

    QGraphicsPixmapItem * diamond;
    if(fireboy->collidesWithDiamonds(diamonds)){
        diamond = fireboy->collidesWithDiamonds(diamonds);
        if(diamond->isVisible()){
            numOfDiamonds -= 1;
            diamond->hide();
        }
    }


    QGraphicsPixmapItem * redGem;
    if(fireboy->collidesWithRedGems(redGems)){
        redGem = fireboy->collidesWithRedGems(redGems);
        if(redGem->isVisible()){
            redGem->hide();
            numOfRedGems -= 1;
        }
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
                if((collidedBox->collidesWithItem(blocks[i]) && blocks[i] != collidedBox) || fireboy->collidesWithBoxes(boxes) != NULL){
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
                if((collidedBox->collidesWithItem(blocks[i]) && blocks[i] != collidedBox) || fireboy->collidesWithBoxes(boxes) != NULL){
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
        diamond = watergirl->collidesWithDiamonds(diamonds);
        if(diamond->isVisible()){
            diamond->hide();
            numOfDiamonds -= 1;
        }
    }

    QGraphicsPixmapItem * blueGem;
    if(watergirl->collidesWithBlueGems(blueGems)){
        blueGem=watergirl->collidesWithBlueGems(blueGems);
        if(blueGem->isVisible()){
            blueGem->hide();
            numOfBlueGems-=1;
        }
    }

}


void Level01::moveElevator() {

    for(int i = 0; i < pushers.length(); i++) {
        // Provera da li se neko od igraca nalazi na dugmetu i pokretanje lifta

        bool but1 = fireboy->collidesWithItem(pushers[i].button1) || watergirl->collidesWithItem(pushers[i].button1);
        bool but2 = fireboy->collidesWithItem(pushers[i].button2) || watergirl->collidesWithItem(pushers[i].button2);
        bool elev = fireboy->collidesWithItem(pushers[i].elevator) || watergirl->collidesWithItem(pushers[i].elevator);

        if((but1 || but2) && pushers[i].pos < 90 && !elev) {

            pushers[i].elevator->moveBy(0, 1);
            pushers[i].pos++;
            if(fireboy->collidesWithItem(pushers[i].elevator) || watergirl->collidesWithItem(pushers[i].elevator)) {
                pushers[i].elevator->moveBy(0, -1);
                pushers[i].pos--;
            }
        }
        else if(!(but1 || but2) && pushers[i].pos > 0) {
            pushers[i].elevator->moveBy(0, -1);

            if(fireboy->collidesWithItem(pushers[i].elevator))
                fireboy->moveBy(0, -1);

            if(watergirl->collidesWithItem(pushers[i].elevator))
                watergirl->moveBy(0, -1);

            pushers[i].pos--;

            QGraphicsPixmapItem *tmp1 = fireboy->collidesWithBlocks(blocks);
            QGraphicsPixmapItem *tmp2 = watergirl->collidesWithBlocks(blocks);
            if((tmp1 != NULL && tmp1 != pushers[i].elevator) || (tmp2 != NULL && tmp2 != pushers[i].elevator)) {
                pushers[i].elevator->moveBy(0, 1);

                if(tmp1 != NULL)
                    fireboy->moveBy(0, 1);

                if(tmp2 != NULL)
                    watergirl->moveBy(0, 1);

                pushers[i].pos++;
            }
        }


    }

    //Provera promene stanja rucice, pokretanje lifta i obrada kolizija

    for(int i = 0; i < levers.length(); i++) {

        bool elev = fireboy->collidesWithItem(levers[i].elevator) || watergirl->collidesWithItem(levers[i].elevator);

        if(levers[i].onOff == 1 && levers[i].elevatorPos < 90 && !elev) {

            levers[i].elevator->moveBy(0, 1);
            levers[i].elevatorPos++;
            if(fireboy->collidesWithItem(levers[i].elevator) || watergirl->collidesWithItem(levers[i].elevator)) {
                levers[i].elevator->moveBy(0, -1);
                levers[i].elevatorPos--;
            }
        }
        else if(levers[i].onOff == 0 && levers[i].elevatorPos > 0) {
            levers[i].elevator->moveBy(0, -1);


            if(fireboy->collidesWithItem(levers[i].elevator))
                fireboy->moveBy(0, -1);

            if(watergirl->collidesWithItem(levers[i].elevator))
                watergirl->moveBy(0, -1);

            levers[i].elevatorPos--;

            QGraphicsPixmapItem *tmp1 = fireboy->collidesWithBlocks(blocks);
            QGraphicsPixmapItem *tmp2 = watergirl->collidesWithBlocks(blocks);
            if((tmp1 != NULL && tmp1 != levers[i].elevator) || (tmp2 != NULL && tmp2 != levers[i].elevator)) {
                pushers[i].elevator->moveBy(0, 1);

                if(tmp1 != NULL)
                    fireboy->moveBy(0, 1);

                if(tmp2 != NULL)
                    watergirl->moveBy(0, 1);

                levers[i].elevatorPos++;
            }
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

//Kretanje igraca

void Level01::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
        return;

    if (event->key()==Settings::fireboyRightKey){
            directionFireboy += 1;
            timerFireboy.start();
//            fireboy->setPixmap("run");
//            fireboy->setDirection(1);
    }
    if (event->key()==Settings::fireboyLeftKey){
            directionFireboy -= 1;
            timerFireboy.start();
//            fireboy->setPixmap("run");
//            fireboy->setDirection(-1);
    }
    if(event->key()==Settings::fireboyUpKey){
            if(fireboy->onGround(blocks)) {
                velocityFireboy = -9.0;
            }
    }
     if(event->key()==Settings::watergirlRightKey){
         directionWatergirl += 1;
         timerWatergirl.start();
//         watergirl->setPixmap("run");
//         watergirl->setDirection(1);
     }

     if(event->key()==Settings::watergirlLeftKey){
         directionWatergirl -= 1;
         timerWatergirl.start();
//         watergirl->setPixmap("run");
//         watergirl->setDirection(-1);
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
        if(directionWatergirl == 0) {
            timerWatergirl.stop();
//            watergirl->setPixmap("stand");
//            watergirl->setDirection(1);
        }
    }

    if(event->key()==Settings::watergirlLeftKey){
        directionWatergirl += 1;
        if(directionWatergirl == 0) {
            timerWatergirl.stop();
//            watergirl->setPixmap("stand");
//            watergirl->setDirection(-1);
        }
    }
    if (event->key()==Settings::fireboyRightKey){
        directionFireboy -= 1;
        if(directionFireboy == 0) {
            timerFireboy.stop();
//            fireboy->setPixmap("stand");
//            fireboy->setDirection(1);
        }
    }
    if (event->key()==Settings::fireboyLeftKey){
        directionFireboy += 1;
        if(directionFireboy == 0) {
            timerFireboy.stop();
//            fireboy->setPixmap("stand");
//            fireboy->setDirection(-1);
        }
    }

}

void Level01::MakeMap(QString str) {

    //Postavljanje pozadine

    background = this->addRect(0, 0, 1280,760);
    QString path = QCoreApplication::applicationDirPath() + "/Images/wall";

    background->setBrush(QBrush(QPixmap(path).scaled(600, 600)));
    addItem(background);

    //Ucitavanje elemenata iz datoteke i njihovo postavljanje

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
            l->setPixmap(QPixmap(path).scaled(30, 25));
            l->setPos(x,y+1);
            lava.append(l);
        }
        else if(elem == "Water")
        {
            QGraphicsPixmapItem *w = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/water";
            w->setPixmap(QPixmap(path).scaled(30, 25));
            w->setPos(x,y + 1);
            water.append(w);
        }
        else if(elem == "Acid")
        {
            QGraphicsPixmapItem *w = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/acid";
            w->setPixmap(QPixmap(path).scaled(30, 25));
            w->setPos(x,y + 1);
            acid.append(w);
        }
        else if(elem == "Door") {
            QGraphicsPixmapItem *w = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/doors";
            w->setPixmap(QPixmap(path).scaled(90, 90));
            w->setPos(x,y+3);
            addItem(w);
            doors.append(w);
        }
        else if(elem == "Pusher") {
            QGraphicsPixmapItem *w = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/button";
            w->setPixmap(QPixmap(path).scaled(30, 30));
            w->setPos(x,y);
            addItem(w);

            f >> x >> y;
            QGraphicsPixmapItem *v = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/button";
            v->setPixmap(QPixmap(path).scaled(30, 30));
            v->setPos(x,y);
            addItem(v);

            f >> x >> y;
            QGraphicsPixmapItem *r = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/elevator";
            r->setPixmap(QPixmap(path).scaled(120, 22));
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
            path = QCoreApplication::applicationDirPath() + "/Images/lever";
            w->setPixmap(QPixmap(path).scaled(15, 30));
            w->setPos(x,y);
            addItem(w);

            QGraphicsPixmapItem *s = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/l";
            s->setPixmap(QPixmap(path).scaled(55, 20));
            s->setPos(x-5,y + 16);
            addItem(s);

            f >> x >> y;
            QGraphicsPixmapItem *r = new QGraphicsPixmapItem;
            path = QCoreApplication::applicationDirPath() + "/Images/elevator";
            r->setPixmap(QPixmap(path).scaled(120, 22));
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
            w->setPixmap(QPixmap(path).scaled(27, 20));
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

    // Postavljanje tajmera

    pauseGame = new QPushButton("00:00");
    pauseGame->setGeometry(QRect(this->width()/2 - 50, 0, 100, 30));
    pauseGame->setStyleSheet("border: 1px solid #000000; background: rgb(139,69,19); font-size: 22px; font-family: cursive; border-radius: 5px;");
    addWidget(pauseGame);
    connect(pauseGame, SIGNAL(clicked()), SLOT(pauseOnTimer()));

    //Postavljanje zvuka klika

    QMediaPlayer *player = new QMediaPlayer();
    path = QCoreApplication::applicationDirPath() + "/Sound/click.mp3";
    player->setMedia(QUrl::fromLocalFile(path));
    player->setVolume(500);

    connect(pauseGame, &QPushButton::pressed, player, &QMediaPlayer::play);

}

// Prozori pri interakciji

void Level01::levelEnd() {
    // Uspesno zavrsen nivo

    // Dodela broja zvezdica

    if(Levels::currentLevel == Levels::lastUnlocked) {
        Levels::lastUnlocked++;
    }
    int s = 0;
    if(numOfBlueGems <= 0)
        s++;
    if(numOfRedGems <= 0)
        s++;
    if(numOfDiamonds <= 0)
        s++;
    if(timerCount > 150)
        s--;
    if(s > Levels::levelStars[Levels::currentLevel - 1])
        Levels::levelStars[Levels::currentLevel - 1] = s;

    //Zaustavljanje svih tajmera

    gravityTimerID--;
    disconnect(&timerFireboy, &QTimer::timeout, this, &Level01::moveFireboy);
    disconnect(&timerWatergirl, &QTimer::timeout, this, &Level01::moveWatergirl);
    disconnect(&timerElevator, &QTimer::timeout, this, &Level01::moveElevator);
    timer.stop();

    //Postavljanje prozora i dugmica

    endWindow = new QWidget();
    endWindow->setFixedSize(500, 400);
    QString path = QCoreApplication::applicationDirPath() + "/Images/levelFinished/";
    endWindow->setStyleSheet("border-image: url(" + path + "background" + QString::number(s) + ") 0 0 0 0 stretch stretch;" +
                             "background-image: url(" + path + "bg" + "); border-width: 0px; background-position: center;");
    endWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    endWindow->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, endWindow->size(), qApp->desktop()->availableGeometry()));

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setSpacing(50);
    layout->setContentsMargins(50, 200, 50, 50);

    nextLevel = new QPushButton("", endWindow);
    path = QCoreApplication::applicationDirPath() + "/Images/levelFinished/next";
    nextLevel->setFixedSize(80, 80);
    nextLevel->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; background: none;}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    layout->addWidget(nextLevel);

    exitToMenu = new QPushButton("", endWindow);
    path = QCoreApplication::applicationDirPath() + "/Images/levelFinished/menu";
    exitToMenu->setFixedSize(80, 80);
    exitToMenu->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; background: none;}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    layout->addWidget(exitToMenu);

    repeatThisLevel = new QPushButton("", endWindow);
    path = QCoreApplication::applicationDirPath() + "/Images/levelFinished/restart";
    repeatThisLevel->setFixedSize(80, 80);
    repeatThisLevel->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; background: none;}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    layout->addWidget(repeatThisLevel);

    endWindow->setLayout(layout);

    connect(nextLevel, SIGNAL(clicked()), levels, SLOT(nextLevel()));
    connect(nextLevel, SIGNAL(clicked()), endWindow, SLOT(close()));
    connect(exitToMenu, SIGNAL(clicked()), levels, SLOT(exitLevel()));
    connect(exitToMenu, SIGNAL(clicked()), endWindow, SLOT(close()));
    connect(repeatThisLevel, SIGNAL(clicked()), this, SLOT(repeatLevel()));
    connect(repeatThisLevel, SIGNAL(clicked()), endWindow, SLOT(close()));


    QMediaPlayer *player = new QMediaPlayer();
    path = QCoreApplication::applicationDirPath() + "/Sound/click.mp3";
    player->setMedia(QUrl::fromLocalFile(path));
    player->setVolume(500);

    connect(nextLevel, &QPushButton::pressed, player, &QMediaPlayer::play);
    connect(exitToMenu, &QPushButton::pressed, player, &QMediaPlayer::play);
    connect(repeatThisLevel, &QPushButton::pressed, player, &QMediaPlayer::play);

    endWindow->show();

}

void Level01::gameOver() {
    // Prozor u slucaju nepredjenog nivoa
    gravityTimerID--;
    disconnect(&timerFireboy, &QTimer::timeout, this, &Level01::moveFireboy);
    disconnect(&timerWatergirl, &QTimer::timeout, this, &Level01::moveWatergirl);
    disconnect(&timerElevator, &QTimer::timeout, this, &Level01::moveElevator);
    timer.stop();

    endWindow = new QWidget();
    endWindow->setFixedSize(450, 400);QString path = QCoreApplication::applicationDirPath() + "/Images/gameOver/";
    endWindow->setStyleSheet("border-image: url(" + path + "background" + ") 0 0 0 0 stretch stretch; background-image: url(" + path + "bg" + "); border-width: 0px; background-position: center;");

    endWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    endWindow->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, endWindow->size(), qApp->desktop()->availableGeometry()));

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setSpacing(50);
    layout->setContentsMargins(50, 200, 50, 50);

    repeatThisLevel = new QPushButton("", endWindow);
    path = QCoreApplication::applicationDirPath() + "/Images/gameOver/restart";
    repeatThisLevel->setFixedSize(80, 80);
    repeatThisLevel->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; background: none;}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    layout->addWidget(repeatThisLevel);

    exitToMenu = new QPushButton("", endWindow);
    path = QCoreApplication::applicationDirPath() + "/Images/gameOver/menu";
    exitToMenu->setFixedSize(80, 80);
    exitToMenu->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; background: none;}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    layout->addWidget(exitToMenu);

    endWindow->setLayout(layout);

    connect(repeatThisLevel, SIGNAL(clicked()), this, SLOT(repeatLevel()));
    connect(repeatThisLevel, SIGNAL(clicked()), endWindow, SLOT(close()));

    connect(exitToMenu, SIGNAL(clicked()), levels, SLOT(exitLevel()));
    connect(exitToMenu, SIGNAL(clicked()), endWindow, SLOT(close()));

    QMediaPlayer *player = new QMediaPlayer();
    path = QCoreApplication::applicationDirPath() + "/Sound/click.mp3";
    player->setMedia(QUrl::fromLocalFile(path));
    player->setVolume(500);

    connect(repeatThisLevel, &QPushButton::pressed, player, &QMediaPlayer::play);
    connect(exitToMenu, &QPushButton::pressed, player, &QMediaPlayer::play);

    endWindow->show();

}

void Level01::repeatLevel() {

    //Postavljanje svih elemenata na pocetne pozicije

    watergirl->setPos(100,570);
    while(watergirl->collidesWithBlocks(blocks) != NULL) {
        watergirl->moveBy(0, -1);
//        watergirl->setDirection(-1);
    }

    fireboy->setPos(100, 660);
    while(fireboy->collidesWithBlocks(blocks) != NULL) {
        fireboy->moveBy(0, -1);
//        fireboy->setDirection(-1);
    }

    fireboy->show();
    watergirl->show();

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
    numOfDiamonds = 2;
    numOfRedGems = 3;
    numOfBlueGems = 3;
}

void Level01::pause() {
    // Zaustavljanje animacije
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
    endWindow->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, endWindow->size(), qApp->desktop()->availableGeometry()));

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setSpacing(50);
    layout->setContentsMargins(50, 200, 50, 50);

    repeatThisLevel = new QPushButton("", endWindow);
    path = QCoreApplication::applicationDirPath() + "/Images/pause/restart";
    repeatThisLevel->setFixedSize(80, 80);
    repeatThisLevel->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; background: none;}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    layout->addWidget(repeatThisLevel);

    exitToMenu = new QPushButton("", endWindow);
    path = QCoreApplication::applicationDirPath() + "/Images/pause/menu";
    exitToMenu->setFixedSize(80, 80);
    exitToMenu->setStyleSheet("QPushButton {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 2px; background: none;}" +
                                   "QPushButton:hover {border-image: url(" + path + ") 0 0 0 0 stretch stretch; margin: 0px;}");
    layout->addWidget(exitToMenu);

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

    connect(exitToMenu, SIGNAL(clicked()), levels, SLOT(exitLevel()));
    connect(exitToMenu, SIGNAL(clicked()), endWindow, SLOT(close()));

    connect(resume, SIGNAL(clicked()), this, SLOT(resumeLevel()));
    connect(resume, SIGNAL(clicked()), endWindow, SLOT(close()));

    QMediaPlayer *player = new QMediaPlayer();
    path = QCoreApplication::applicationDirPath() + "/Sound/click.mp3";
    player->setMedia(QUrl::fromLocalFile(path));
    player->setVolume(500);

    connect(repeatThisLevel, &QPushButton::pressed, player, &QMediaPlayer::play);
    connect(exitToMenu, &QPushButton::pressed, player, &QMediaPlayer::play);
    connect(resume, &QPushButton::pressed, player, &QMediaPlayer::play);

}

void Level01::resumeLevel() {

    // Ponovno pokretanje tajmera i animacije

    gravityTimerID++;
    connect(&timerFireboy, &QTimer::timeout, this, &Level01::moveFireboy);
    connect(&timerWatergirl, &QTimer::timeout, this, &Level01::moveWatergirl);
    connect(&timerElevator, &QTimer::timeout, this, &Level01::moveElevator);
    timer.start();

    endWindow->close();
}

//Postavljanje vremena

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

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <QCoreApplication>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <iostream>

#include "view.h"

int main(int argc, char *argv[])
{
    // Inicijalizacija GUI-a
    QApplication app(argc, argv);

    // Postavljamo ikonicu prozora
    QString path = QCoreApplication::applicationDirPath() + "/Images/icon";
    app.setWindowIcon(QIcon(path));

    // Slika koja se prikazuje pri otvaranju aplikacije
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(path));
    splash->show();

    QMediaPlaylist *playList = new QMediaPlaylist();
    path = QCoreApplication::applicationDirPath() + "/Sound/e.mp3";
    playList->addMedia(QUrl("http://soundimage.org/wp-content/uploads/2016/07/Fantasy_Game_Background_Looping.mp3"));
    playList->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer *player = new QMediaPlayer();
    player->setPlaylist(playList);
    player->setVolume(20);
    player->play();

    // Prikaz pocetnog ekrana
    View *view = new View();


    // singleShot funkcija poziva slot posle zadatog intervala
    QTimer::singleShot(1000, splash, SLOT(close()));
    if(QApplication::desktop()->screenGeometry().width() > 1366 && QApplication::desktop()->screenGeometry().height() > 768)
        QTimer::singleShot(1000, view, SLOT(show()));
    else
        QTimer::singleShot(1000, view, SLOT(showFullScreen()));

    // Ulazimo u glavnu petlju
    return app.exec();
}

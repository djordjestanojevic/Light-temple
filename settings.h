#ifndef SETTINGS_H
#define SETTINGS_H
#include "view.h"
#include "title.h"
#include <QGraphicsScene>
#include <QWidget>
#include <QPushButton>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QApplication>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <iostream>
#include <QGraphicsView>


class View;
class Title;

class Settings: public QGraphicsScene {
    Q_OBJECT
public:
    Settings(View *v, Title *t, QWidget *parent = 0);


    int fireboyUpKeyIndicator;
    int fireboyLeftKeyIndicator;
    int fireboyRightKeyIndicator;
    int watergirlUpKeyIndicator;
    int watergirlLeftKeyIndicator;
    int watergirlRightKeyIndicator;

    static int fireboyLeftKey;
    static int fireboyRightKey;
    static int fireboyUpKey;
    static int watergirlLeftKey;
    static int watergirlRightKey;
    static int watergirlUpKey;
private:
    QGraphicsPixmapItem *fireboyLogo;
    QGraphicsPixmapItem *watergirlLogo;
    View *view;
    Title *title;
    QGraphicsPixmapItem *background;

    void keyPressEvent(QKeyEvent *event);

    QPushButton *fireboyUp;
    QPushButton *backToTitle;
    QPushButton *fireboyLeft;
    QPushButton *fireboyRight;
    QPushButton *watergirlUp;
    QPushButton *watergirlLeft;
    QPushButton *watergirlRight;

    QPushButton *mute;

    QMediaPlayer *sound;

public slots:
    void fireboyUpKeyUpdate();
    void fireboyRightKeyUpdate();
    void fireboyLeftKeyUpdate();
    void watergirlUpKeyUpdate();
    void watergirlRightKeyUpdate();
    void watergirlLeftKeyUpdate();
    void muteButton();
};

#endif // SETTINGS_H

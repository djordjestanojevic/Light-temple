#ifndef TITLE_H
#define TITLE_H

#include <QGraphicsView>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QApplication>

#include "view.h"
#include "settings.h"
#include "levels.h"

class View;
class Levels;
class Settings;

class Title: public QGraphicsScene {
    Q_OBJECT
public:
    Title(View *v, QWidget *parent = 0);

    QPushButton *startButton;
    QPushButton *settingsButton;
    QPushButton *quitButton;

private:
    QGraphicsPixmapItem *logo;
    QGraphicsPixmapItem *background;

    View *view;

    Levels *levels;
    Settings *settings;

public slots:
    void startProgram();
    void goToSettings();
    void quitProgram();

    void back();
};

#endif // TITLE_H

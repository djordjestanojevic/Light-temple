#ifndef TITLE_H
#define TITLE_H

#include <QGraphicsView>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QApplication>

#include "view.h"
#include "level01.h"
#include "settings.h"

class View;

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

public slots:
    void startProgram();
    void goToSettings();
    void quitProgram();
};

#endif // TITLE_H

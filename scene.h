#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QPushButton>
#include <QApplication>
#include <QGraphicsPixmapItem>

#include "view.h"


class Scene: public QGraphicsScene {
    Q_OBJECT
public:
    Scene(View *view, QWidget *parent = 0);


private slots:
    void startProgram();
    void quitProgram();

private:
    View *view;

    QPushButton *startButton;
    QPushButton *quitButton;

    QGraphicsPixmapItem *background;
    QGraphicsPixmapItem *logo;

};

#endif // SCENE_H

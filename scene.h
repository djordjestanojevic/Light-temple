#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

#include "view.h"

class Scene: public QGraphicsScene {
public:
    Scene(View *view, QWidget *parent = 0);

};

#endif // SCENE_H

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QGraphicsScene>
#include <QWidget>

class Settings: public QGraphicsScene {
    Q_OBJECT
public:
    Settings(QWidget *parent = 0);

};

#endif // SETTINGS_H

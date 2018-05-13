#ifndef LEVEL01_H
#define LEVEL01_H

#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QKeyEvent>

class Level01: public QGraphicsScene {
    Q_OBJECT
public:
    Level01(QWidget *parent = 0);
private:
    bool initPlayField();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    QGraphicsRectItem *background;
    QGraphicsPixmapItem *ground;

    QGraphicsPixmapItem *fireboy;

    QTimer m_timer;

    int direction;
private slots:
    void movePlayer();
};
#endif // LEVEL01_H

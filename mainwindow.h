#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "view.h"
#include "scene.h"

class MainWindow: public QMainWindow {
public:
    MainWindow(QWidget *parent);
    
private:
    void createScene();
    
    Scene *scene;
    View *view;
    
};

#endif // MAINWINDOW_H

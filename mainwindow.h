#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDesktopWidget>
#include <QApplication>

#include "view.h"
#include "scene.h"

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    void setSize();
    
private:
    void createScene();
    
    Scene *scene;
    View *view;
    
};

#endif // MAINWINDOW_H

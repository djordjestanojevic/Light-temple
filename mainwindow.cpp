#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createScene();
    // Postavljamo da view bude centralni widget glavnog prozora
    setCentralWidget(view);
}


void MainWindow::createScene() {

    view = new View;
    scene = new Scene(view);
}



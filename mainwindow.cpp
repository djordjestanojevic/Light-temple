#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createScene();
    setCentralWidget(view);
}


void MainWindow::createScene() {

    // Klase za postavljanje widgeta
    view = new View;
    scene = new Scene(view);
}


void MainWindow::setSize(){
    // Postavljanje velicine ekrana
    this->setFixedSize(1280,760);

}

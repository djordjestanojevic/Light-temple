#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // Inicijalizacija GUI-a
    QApplication app(argc, argv);

    // Postavljamo ikonicu prozora
    app.setWindowIcon(QIcon("C:/Users/Djordje/Desktop/FAX/Razvoj softvera/Projekat/Images/icon"));

    // Slika koja se prikazuje pri otvaranju aplikacije
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap("C:/Users/Djordje/Desktop/FAX/Razvoj softvera/Projekat/Images/icon"));
    splash->show();

    // Postavljamo glavni prozor aplikacije
    MainWindow mainWin;
    // Postavljamo velicinu prozora
    mainWin.setSize();

    // singleShot funkcija poziva slot posle zadatog intervala
    QTimer::singleShot(1000, splash, SLOT(close()));
    QTimer::singleShot(1000, &mainWin, SLOT(show()));

    // Ulazimo u glavnu petlju
    return app.exec();
}

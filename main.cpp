#include <QApplication>
#include <QMainWindow>
#include <QTimer>

int main(int argc, char *argv[])
{
    // Inicijalizacija GUI-a
    QApplication app(argc, argv);

    // Postavljamo ikonicu prozora
    app.setWindowIcon(QIcon(":/Images/icon"));

    // Postavljamo glavni prozor aplikacije
    QMainWindow mainWin;
    mainWin.show();

    // Ulazimo u glavnu petlju
    return app.exec();
}

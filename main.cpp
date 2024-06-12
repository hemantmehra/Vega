#include <QApplication>
#include <QLabel>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMainWindow>
#include <WebView.h>

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow main_window;
    main_window.setWindowTitle("Test");
    main_window.resize(WIDTH, HEIGHT);

    WebView wv(WIDTH, HEIGHT);
    main_window.setCentralWidget(&wv);
    main_window.show();

    int result = app.exec();
    return result;
}

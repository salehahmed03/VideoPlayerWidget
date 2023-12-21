#include "VideoPlayerWidget.h"
#include <QtWidgets/QApplication>
#include "VideoList.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VideoPlayerWidget w;
    w.show();
    VideoList Y;
    Y.show();
    return a.exec();
}

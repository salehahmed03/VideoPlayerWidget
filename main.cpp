#include "VideoPlayerWidget.h"
#include <QtWidgets/QApplication>
#include "VideoList.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VideoList Y;
    Y.show();
    return a.exec();
}

#include <QtGui/QApplication>
#include "ffmpegui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ffmpegui w;
    w.show();

    return a.exec();
}

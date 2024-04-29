#include "dashboardclass.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DashBoardClass w;
    w.show();
    return a.exec();
}

#include "MainWindow.h"
#include <QApplication>
#include "userdate.h"
#include "register_page.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    userdate::addUser(); //初始化用户信息
    return a.exec();
}

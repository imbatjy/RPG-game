#include "mw1.h"
#include "world.h"
#include <QApplication>
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cout<<"1"<<endl;
    //MainWindow w;
    //w.show();
    MW1 mw;
    mw.show();

    return a.exec();
}

#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include "MathFunctions.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout << "mysqrt(23):" << mysqrt(23);

    return a.exec();
//    return 0;
}

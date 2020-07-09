#include <QCoreApplication>
#include "philosopher.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Fork fork1(1);
    Fork fork2(2);
    Fork fork3(3);
    Fork fork4(4);
    Fork fork5(5);

    Philosopher* pl1 = new Philosopher(1, fork1, fork5);
    pl1->start();

    Philosopher* pl2 = new Philosopher(2, fork1, fork2);
    pl2->start();

    Philosopher* pl3 = new Philosopher(3, fork2, fork3);
    pl3->start();

    Philosopher* pl4 = new Philosopher(4, fork3, fork4);
    pl4->start();

    Philosopher* pl5 = new Philosopher(5, fork4, fork5);
    pl5->start();


    std::cout<< "End..."<<std::endl;;
    return a.exec();
}

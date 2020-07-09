#include <QCoreApplication>
#include "buffer.h"
#include "consumer.h"
#include "producer.h"
#include <iostream>

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    Buffer buffer(10);

    Producer producer(buffer);
    Consumer consumer(buffer);

    producer.start();
    consumer.start();

    consumer.wait();
    producer.wait();

    std::cout<<"End..."<<std::endl;

    return a.exec();
}

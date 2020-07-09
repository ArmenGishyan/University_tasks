#include "producer.h"
#include <QRandomGenerator>
#include <QThread>
#include <iostream>

Producer::Producer(Buffer& buffer):m_buffer(buffer)
{}

void Producer::run()
{
    for(int i = 0; i< 100; ++i)
    {
        produce();
    }
}

void Producer::produce()
{
    std::cout<<"Produce..."<<std::endl;
    QRandomGenerator rand;

    m_buffer.push(rand.generate());
    QThread::sleep(rand.generate() % 4);
}

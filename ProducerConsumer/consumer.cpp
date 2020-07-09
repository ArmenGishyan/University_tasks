#include "consumer.h"
#include <QRandomGenerator>
#include <iostream>

Consumer::Consumer(Buffer& buffer) : m_buffer(buffer)
{
}

void Consumer::run()
{
    for(int i = 0; i < 100; ++i)
    {
        consume();
    }
}

void Consumer::consume()
{
    std::cout<<"Consume..."<<std::endl;
    QRandomGenerator rand;

    m_buffer.pop();
    QThread::sleep(rand.generate() % 2);
}

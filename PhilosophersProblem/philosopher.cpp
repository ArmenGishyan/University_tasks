#include "philosopher.h"
#include <iostream>
#include <QRandomGenerator>

bool Fork::take()
{
    std::lock_guard<std::mutex> lock(m_mu);
    if(!m_bTaken) {
        m_bTaken = true;
        return true;
    }
    return false;
}

void Fork::putDown()
{
    std::lock_guard<std::mutex> lock(m_mu);
    m_bTaken = false;
}


Philosopher::Philosopher(int index, Fork& left, Fork& right)
    : m_left(left), m_right(right), m_id(index)
{
}
void Philosopher::run()
{
    hungry();
}

void Philosopher::eat()
{
    std::cout<<m_id << " " << "Eating..."<<std::endl;
    QRandomGenerator rand;
    QThread::sleep(rand.generate() % 3);

    // put both forks down
    m_left.putDown();
    m_right.putDown();

    // think
    think();
}

void Philosopher::think()
{
    std::cout<<m_id << " " << "Thinking..."<<std::endl;

    QRandomGenerator rand;
    QThread::sleep(rand.generate() % 2);

    hungry();
}

void Philosopher::hungry()
{
    std::cout<<m_id << " " << "Hungry..."<<std::endl;
    // get first fork low priority
    if(m_left.get() < m_right.get())
    {
        if(m_left.take())
        {
            if(m_right.take())
            {
                // here we have two forks;
                eat();
                return;
            }
            // if we don't succeed put down first one
            m_left.putDown();
        }
    } else {
        if(m_right.take())
        {
            if(m_left.take())
            {
                // here we have two forks;
                eat();
                return;
            }
            // first
            m_right.putDown();
        }
    }

    hungry();
}




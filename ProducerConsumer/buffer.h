#ifndef BUFFER_H
#define BUFFER_H

#include <QSemaphore>
#include <QQueue>

class Buffer
{
public:
    Buffer(int size);
    // add new values from end of buffer
    void push(int x);
    // remove values from begining of buffer
    int pop();

private:
    // control availability of values in buffer
    QSemaphore m_full;
    // control if thre are space avilable to push new value
    QSemaphore m_emtpy;

    // buffer to store values
    QQueue<int> m_buffer;
};

#endif // BUFFER_H

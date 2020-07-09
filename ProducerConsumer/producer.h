#ifndef PRODUCER_H
#define PRODUCER_H

#include "buffer.h"
#include <QThread>

class Producer : public QThread
{
public:
    Producer(Buffer& buffer);
    // generates random numbers andpush into buffer
    // if space avilable otherwise got blocked
    void produce();
    void run() override;

private:
    Buffer& m_buffer;
};

#endif // PRODUCER_H

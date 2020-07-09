#ifndef CONSUMER_H
#define CONSUMER_H

#include "buffer.h"
#include <QThread>

class Consumer : public QThread
{
public:
    Consumer(Buffer& m_buffer);
    // consume values from top of buffer
    // if buffer empty got blocked
    void consume();
    void run() override;

private:
    Buffer& m_buffer;
};

#endif // CONSUMER_H

#include "buffer.h"

Buffer::Buffer(int size) : m_full(size), m_emtpy(size)
{
    m_full.acquire(size);
}

void Buffer::push(int value)
{    
    m_emtpy.acquire();

    m_buffer.push_back(value);
    m_full.release();
}

int Buffer::pop()
{    
    m_full.acquire();

    int value = m_buffer.front();
    m_buffer.pop_front();
    m_emtpy.release();

    return value;
}

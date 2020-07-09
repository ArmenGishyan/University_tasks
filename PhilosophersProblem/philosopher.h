#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <QThread>

struct Fork
{
    Fork(int index): m_index(index){}
    bool take();
    void putDown();
    const int& get() const {return m_index;}

private:
    bool m_bTaken {false};
    std::mutex m_mu;
    int m_index;
};

class Philosopher : public QThread
{
public:
    Philosopher(int index, Fork& left, Fork& right);
    void run() override;

private:
    void eat();
    void think();
    void hungry();

private:
    Fork& m_left;
    Fork& m_right;
    // this for debugging
    int m_id; 
};

#endif // PHILOSOPHER_H

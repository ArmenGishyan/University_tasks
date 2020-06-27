#pragma once

#include <thread>
#include <mutex>
#include <queue>

class Bridge;

//
///  Class is responsible to handle cars traffic on one side only.
///  Have nested semaphore implementation for scheduling carss access to bridge
///  Used conditional variable and mutex for semaphore implementation
//
class Traffic
{
public:
	enum Status
	{
		Empty = 1,
	};

	Traffic(Bridge* br, bool execState, int count = 1) : m_bridge(br), m_execState(execState),								
							   m_count(count), m_maxValue(count){}
	
	// get current state in-progress or locked 
	bool getExecState() const { return m_execState; }
	// set execution state
	void setExecState(bool state);
	
	// Cars arne't available in traffic
	bool empty() { return m_maxValue == m_count; }
	
	// pop car from traffic
	void pop();
	// push car into traffic
	void push(std::thread::id id);

private:
	std::mutex m_mu;
	std::condition_variable m_cv;
	// current semaphore value
	int m_count;
	// max value semaphore can reache. 
	int m_maxValue;

	// Cars queue which waithing for own turn to pass the bridge
	std::queue<std::thread::id> m_thQueue;
	
	// Traffic can be blocked -> false or in progress -> true
	bool m_execState;
	// bridge pointer which Traffic belong to 
	Bridge* m_bridge {nullptr};
};


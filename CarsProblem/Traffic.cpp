#include "Traffic.h"
#include "bridge.h"
#include <iostream>

void Traffic::pop()
{
	std::unique_lock<std::mutex> lock(m_mu);

	m_count++;

	if (m_count == m_maxValue) {
		// if traffic is empty notify to bridge
		
		m_bridge->notify(this, Traffic::Status::Empty);
	}

	m_cv.notify_all();
}

void Traffic::push(std::thread::id id)
{
	std::unique_lock<std::mutex> lock(m_mu);

	if (m_count == 0 || !m_execState)
	{
		m_thQueue.push(id);
		bool flag = false;

		m_cv.wait(lock, [this, id, &flag]() {
			std::cout << "withing ..." << std::endl;
			if (flag &&  m_execState && !m_thQueue.empty() && m_thQueue.front() == id)
				return true;

			// for first case
			flag = true;
			return false;

		});

		--m_count;

		if (!m_thQueue.empty())
			m_thQueue.pop();

		return;
	}

	--m_count;
}

void Traffic::setExecState(bool state)
{
	m_execState = state;
	// in case of true notify all
	if (m_execState)
		m_cv.notify_all();
}
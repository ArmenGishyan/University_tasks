#pragma once

#include <thread>
#include "Bridge.h"

//
/// Backgroud object which should time by time switch traffic direction left -> right and vice versa 
//
class TrafficSwitcher
{
public:
	TrafficSwitcher(Bridge& br) : m_br(br) {}

	void setTimeout(int delay)
	{
		std::thread sw([this, delay]() {
			while (!m_stop)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(delay));
				
				m_br.switchDirection();
			}
		});

		sw.detach();
	}

	void stop() { m_stop = true; }
	
private:
	Bridge& m_br;
	bool m_stop {false};
};


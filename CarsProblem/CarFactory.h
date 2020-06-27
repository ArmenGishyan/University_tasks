#pragma once

#include <thread>
#include "TrafficSwitcher.h"

// 
/// Class isn't related to algorithm
/// Just creates cars and move them to bridge
//
class CarFactory
{
public:
	CarFactory()
	{
		TrafficSwitcher tf(br);
		tf.setTimeout(2000);
	}

	~CarFactory()
	{
		// wait all cars to finish
		std::for_each(m_cars.begin(), m_cars.end(), [](std::thread& th) { th.join(); });
	}

	void produceCar(int count)
	{
		for (int i = 0; i < count; ++i)
		{
			if (i % 2 == 0)
			{
				leftSideCar(i);
			}
			else {
				rightSideCar(i);
			}
		}
	}

private:
	void leftSideCar(int i)
	{
		m_cars.push_back(std::thread([this, i]() {
			br.pushLeftSide(std::this_thread::get_id());

			std::chrono::milliseconds dura((i * 1000) % 5);
			std::this_thread::sleep_for(dura);

			std::cout << " left before " << i << std::endl;
			br.popLeftSide();
			std::cout << " left after " << i << std::endl;

			std::this_thread::sleep_for(dura);

		}));
	}

	void rightSideCar(int i)
	{
		m_cars.push_back(std::thread([this, i]() {
			br.pushRightSide(std::this_thread::get_id());

			std::chrono::milliseconds dura((i * 1000) % 5);
			std::this_thread::sleep_for(dura);

			std::cout << " right before " << i << std::endl;
			br.popRightSide();
			std::cout << " right after " << i << std::endl;

			std::this_thread::sleep_for(dura);
		}));
	}

private:
	Bridge br { 4 };
	
	// collect cars to join() them on destruction
	std::vector<std::thread> m_cars;
};

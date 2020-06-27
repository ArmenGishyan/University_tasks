#include "Action.h"

#include <stdlib.h> // rand ()
#include <iostream>

Searcher::~Searcher()
{
	m_searcher.join();
}

void Searcher::work()
{
	if (m_searcher.joinable())
		m_searcher.join();

	m_searcher = std::move(std::thread ([this]() {
		
		for (int i = 0; i < 20; ++i)
		{
			std::cout << "Searcher working" << std::endl;
			m_shmu.lock_shared();

			// do search
			
			m_shmu.unlock_shared();

			std::this_thread::sleep_for((std::chrono::seconds(2)));
			
		}
	}));
}

Inserter::~Inserter()
{
	m_inserter1.join();

	m_inserter2.join();
}

void Inserter::work()
{
	if (m_inserter1.joinable())
		m_inserter1.join();

	m_inserter1 = std::move(std::thread([this]() {
		for (int i = 0; i < 20; ++i)
		{
			std::cout << "inserter 1 working" << std::endl;
			m_mu.lock();

			push_back((rand() % 10));

			m_mu.unlock();

			std::this_thread::sleep_for((std::chrono::seconds(3)));
		}
	}));

	
	m_inserter2 = std::move(std::thread ([this]() {

		for (int i = 0; i < 20; ++i)
		{
			std::cout << "inserter 2 working" << std::endl;
			m_mu.lock();

			push_back((rand() % 10));

			m_mu.unlock();

			std::this_thread::sleep_for((std::chrono::seconds(2)));
		}
	}));

}

void Inserter::push_back(int number)
{
	m_shmu.lock_shared();

	m_qu.push_back(number);

	// make search
	m_shmu.unlock_shared();
}

Deleter::~Deleter()
{
	m_deleter.join();
}

void Deleter::work()
{
	if (m_deleter.joinable())
		m_deleter.join();

	m_deleter = std::move(std::thread([this]() {
		for (int i = 0; i < 20; ++i)
		{
			std::cout << "Deleter working" << std::endl;

			m_shmu.lock();

			// do delete 
			if(!m_qu.empty())
				m_qu.pop_back();

			m_shmu.unlock();
			std::this_thread::sleep_for((std::chrono::seconds(1)));
		}
		// make delete
		
	}));
	
}
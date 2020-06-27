#pragma once

#include <deque>
#include <shared_mutex>

// base class for all action
class Action
{
public:
	Action(std::deque<int>& qu, std::shared_mutex& shmu) :m_qu(qu), m_shmu(shmu) {}

protected:
	// shared queue for derived actions to work with it
	std::deque<int>& m_qu;
	// synchronization object to handle parallel queue access
	std::shared_mutex& m_shmu;
};

class Searcher : public Action
{
public:
	Searcher(std::deque<int>& qu, std::shared_mutex& shmu) : Action(qu, shmu) {}
	~Searcher();
	void work();

private:
	std::thread m_searcher;
};

class Inserter : public Action
{
public:
	Inserter(std::deque<int>& qu, std::shared_mutex& shmu) : Action(qu, shmu) {}
	~Inserter();

	void work();

private:
	void push_back(int number);
	// mutex for exclusive insert
	std::mutex m_mu;
	// two nested inserter
	std::thread m_inserter1;
	std::thread m_inserter2;
};

class Deleter : public Action
{
public:
	Deleter(std::deque<int>& qu, std::shared_mutex& shmu) : Action(qu, shmu) {}
	~Deleter();

	void work();

private:
	std::thread m_deleter;
};

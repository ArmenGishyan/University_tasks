#include "Action.h"
#include <iostream>


int main()
{
	// Shared queue 
	std::deque<int> queue;

	std::shared_mutex mu;

	// searcher
	Searcher* S = new Searcher(queue, mu);

	// inserter
	// have two nested inserter thread
	Inserter* I = new Inserter(queue, mu);

	// deleter
	Deleter* D = new Deleter(queue, mu);

	S->work();
	D->work();
	I->work();
	
	delete S;
	delete D;
	delete I;
	
	std::cout << "End..." << std::endl;
	system("pause");
}


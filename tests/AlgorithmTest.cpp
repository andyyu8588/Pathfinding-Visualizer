#include "../src/Algorithm.h"
#include "../src/Square.h"
#include "AlgorithmTest.h"

#include <stdexcept>

void AlgorithmTest::shouldSuccessfulPath(std::shared_ptr<Graph> g, Algorithm* algo)
{
	algo->run();
	std::shared_ptr<Square> currentSquare = g->getEnd();
	while (currentSquare != g->getStart())
	{
		if (currentSquare->getPreviousSquare() == nullptr) {
			throw logic_error{"Can't reach start square."};
		}
		currentSquare = currentSquare->getPreviousSquare();
	}	
	if (g->hasSuccessfulPath() == false) {
		throw logic_error{"Graph should have successful path."};
	}
}

void AlgorithmTest::shouldUnsuccessfulPath(std::shared_ptr<Graph> g, Algorithm* algo)
{
	algo->run();
	if (g->hasSuccessfulPath() == true) {
		throw logic_error{"Graph shouldn't have successful path."};
	}
}
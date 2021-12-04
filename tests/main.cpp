#include "../src/Astar.h"
#include "../src/BFS.h"
#include "../src/DFS.h"
#include "../src/Dijkstra.h"
#include "../src/Graph.h"

#include "AlgorithmTest.h"
#include "MockObserver.h"

const int dimension = 64;

std::shared_ptr<Graph> getGraph(std::shared_ptr<MockObserver> mockObserver)
{
	std::shared_ptr<Graph> g = std::make_shared<Graph>(dimension);
	g->setStart(0, 0);
	g->setEnd(dimension - 1, dimension - 1);

	// attach mock observer
	for (int i = 0; i < dimension; ++i)
	{
		for (int j = 0; j < dimension; ++j)
		{
			g->getSquare(i, j)->attach(mockObserver);
		}
	}
	return g;
}

std::shared_ptr<Graph> getSuccessfulGraph(std::shared_ptr<MockObserver> mockObserver) 
{
	std::shared_ptr<Graph> g = getGraph(mockObserver);

	// setup path
	for (int i = 1; i < dimension - 1; ++i) {
		for (int j = 1; j < dimension - 1; ++j) {
			g->getSquare(i, j)->changeWall();
		}
	}
	return g;	
}

std::shared_ptr<Graph> getUnsuccessfulGraph(std::shared_ptr<MockObserver> mockObserver)
{
	std::shared_ptr<Graph> g = getGraph(mockObserver);

	// setup path
	for (int i = 1; i < dimension - 1; ++i) {
		for (int j = 0; j < dimension; ++j) {
			g->getSquare(i, j)->changeWall();
		}
	}
	return g;	
}

template<class Algorithm>
void testAlgorithm(AlgorithmTest* algorithmTest, std::shared_ptr<MockObserver> mockObserver)
{
	std::shared_ptr<Graph> successfulGraph = getSuccessfulGraph(mockObserver);
	Algorithm successfulAlgorithm{successfulGraph};
	algorithmTest->shouldSuccessfulPath(successfulGraph, &successfulAlgorithm);

	std::shared_ptr<Graph> unsuccessfulGraph = getUnsuccessfulGraph(mockObserver);
	Algorithm unsuccessfulAlgorithm{unsuccessfulGraph};
	algorithmTest->shouldUnsuccessfulPath(unsuccessfulGraph, &unsuccessfulAlgorithm);
}

int main() 
{
	AlgorithmTest algorithmTest;
	std::shared_ptr<MockObserver> mockObserver = std::make_shared<MockObserver>();	
	testAlgorithm<Astar>(&algorithmTest, mockObserver);
	testAlgorithm<BFS>(&algorithmTest, mockObserver);
	testAlgorithm<DFS>(&algorithmTest, mockObserver);
	testAlgorithm<Dijkstra>(&algorithmTest, mockObserver);
	return 0;
}
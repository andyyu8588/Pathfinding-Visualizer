#pragma once

#include <memory>

class Algorithm;
class Graph;

class AlgorithmTest 
{
public:
	void shouldSuccessfulPath(std::shared_ptr<Graph>, Algorithm*);
	void shouldUnsuccessfulPath(std::shared_ptr<Graph>, Algorithm*);
};
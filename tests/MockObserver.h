#pragma once

#include "../src/Observer.h"

class MockObserver : public Observer 
{
public:
	void notify(Subject&) override;	
};
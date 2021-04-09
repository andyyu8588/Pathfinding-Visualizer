#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <windows.h>
#pragma comment(lib,"user32.lib")

#include "Graph.h"
#include "Observer.h"
#include "Runner.h"

class Display : public Observer
{
	int squareDim;
	shared_ptr<Graph> graph;
	shared_ptr <Runner> runner;
	shared_ptr<sf::RenderWindow> window;
	shared_ptr<tgui::GuiSFML> gui;
	shared_ptr<tgui::Canvas> canvas;

	void drawSquare(int x, int y, int size, sf::Color color);
	void editStart();
	void editEnd();
	void editWall();
	void reset();
	void run();
	shared_ptr<Square> getSquareOnMousePos();

	// Observer methods:
	void notify(Subject & who) override;

public:
	Display(shared_ptr<Graph> graph, shared_ptr<Runner> runner);
	void init();
	void draw();
	void render();
};


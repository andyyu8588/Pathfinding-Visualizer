#ifndef _DISPLAY_H_
#define _DISPLAY_H_


#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "Graph.h"

class Display
{
	shared_ptr<Graph> g;
	shared_ptr<sf::RenderWindow> window;
	shared_ptr<tgui::GuiSFML> gui;

public:
	Display(shared_ptr<Graph> g);

	void init();

	void draw();


};

#endif


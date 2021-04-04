#include "Display.h"

Display::Display(shared_ptr<Graph> g) 
    : g(g) 
{
    window = make_shared<sf::RenderWindow>(sf::VideoMode(1200, 900), "Pathfinder Visualizer V0.1", sf::Style::Titlebar | sf::Style::Close);
    gui = make_shared<tgui::GuiSFML>(*window);
    canvas = tgui::Canvas::create();
    gui->add(canvas);
    // squareDim = 35;
    squareDim = 899 / g->getDimension();
}

void Display::init()
{
    // Line vector: start->end point.
    sf::Vertex line[2] =
    {
        sf::Vertex(sf::Vector2f(950, 0), sf::Color(192, 192, 192)),
        sf::Vertex(sf::Vector2f(950, 900), sf::Color(192, 192, 192))
    };
    canvas->clear(sf::Color(255, 255, 255));
    canvas->draw(line, 2, sf::Lines);


    tgui::Button::Ptr runButton = tgui::Button::create();
    runButton->setPosition(1000, 800);
    runButton->setSize(150, 50);
    runButton->setText("Run");
    gui->add(runButton, "run");

    tgui::RadioButton::Ptr editStartOption = tgui::RadioButton::create();
    editStartOption->setPosition(1000, 100);
    editStartOption->tgui::RadioButton::setText("Edit Start");
    gui->add(editStartOption, "editStart");
    
    
    tgui::RadioButton::Ptr editEndOption = tgui::RadioButton::create();
    editEndOption->setPosition(1000, 150);
    editEndOption->tgui::RadioButton::setText("Edit End");
    gui->add(editEndOption, "editEnd");

    tgui::RadioButton::Ptr editWallOption = tgui::RadioButton::create();
    editWallOption->setPosition(1000, 200);
    editWallOption->tgui::RadioButton::setText("Edit Wall");
    gui->add(editWallOption, "editWall");
}

void Display::drawSquare(int x, int y, int size, sf::Color color)
{
    sf::RectangleShape squareShape;
    squareShape.setSize(sf::Vector2f(size, size));
    squareShape.setOutlineColor(sf::Color(192, 192, 192));
    squareShape.setOutlineThickness(1);
    squareShape.setFillColor(color);
    squareShape.setPosition(x, y);
    canvas->draw(squareShape);
}

shared_ptr<Square> Display::getSquareOnMousePos() 
{
    sf::Vector2i mousepos = sf::Mouse::getPosition(*window);
    int mouseX = mousepos.x;
    int mouseY = mousepos.y;
    if (mouseX > 35 && mouseX < (squareDim * g->getDimension()) + 35 &&
        mouseY > 15 && mouseY < (squareDim * g->getDimension()) + 15) 
    {
        int squareX = (mouseX - 35) / squareDim;
        int squareY = (mouseY - 15) / squareDim;
        return g->getSquare(squareX, squareY);
    }
    return nullptr;
}

void Display::editStart()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
    {
        shared_ptr<Square> squareObj = getSquareOnMousePos();
        if (squareObj != nullptr)
        {            
            if (squareObj != g->getEnd() && !squareObj->isWall()) 
            {
                // delete old start:
                shared_ptr<Square> startSquare = g->getStart();
                if (startSquare != nullptr)
                {
                    drawSquare((squareDim * startSquare->getX()) + 35,
                        (squareDim * startSquare->getY()) + 15,
                        squareDim - 1, 
                        sf::Color(255, 255, 255));
                }

                // drawing:
                drawSquare((squareDim * squareObj->getX()) + 35,
                    (squareDim * squareObj->getY()) + 15,
                    squareDim - 1, 
                    sf::Color(135, 206, 235));
                g->setStart(squareObj->getX(), squareObj->getY());
            }
        }
    }
}

void Display::editEnd() 
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        shared_ptr<Square> squareObj = getSquareOnMousePos();
        if (squareObj != nullptr)
        {
            if (squareObj != g->getStart() && !squareObj->isWall())
            {
                // delete old end:
                shared_ptr<Square> endSquare = g->getEnd();
                if (endSquare != nullptr)
                {
                    drawSquare((squareDim * endSquare->getX()) + 35,
                        (squareDim * endSquare->getY()) + 15,
                        squareDim - 1,
                        sf::Color(255, 255, 255));
                }

                // drawing:
                drawSquare((squareDim * squareObj->getX()) + 35,
                    (squareDim * squareObj->getY()) + 15,
                    squareDim - 1,
                    sf::Color(255, 204, 203));
                g->setEnd(squareObj->getX(), squareObj->getY());
            }
        }
    }
}

void Display::editWall() 
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        shared_ptr<Square> squareObj = getSquareOnMousePos();
        if (squareObj != nullptr)
        {
            if (squareObj != g->getStart() && squareObj != g->getEnd())
            {
                if (squareObj->isWall()) 
                {
                    drawSquare((squareDim * squareObj->getX()) + 35,
                        (squareDim * squareObj->getY()) + 15,
                        squareDim - 1,
                        sf::Color(255, 255, 255));
        
                }
                else 
                {
                    drawSquare((squareDim * squareObj->getX()) + 35,
                        (squareDim * squareObj->getY()) + 15,
                        squareDim - 1,
                        sf::Color(192, 192, 192));
                }
                squareObj->changeWall();
            }
        }
    }
}

void Display::draw()
{
	for (int i = 0; i < g->getDimension(); i++) 
    {
        for (int j = 0; j < g->getDimension(); j++) 
        {
            sf::RectangleShape square;
            if (j == g->getDimension() - 1 || i == g->getDimension() - 1) 
            {
                square.setSize(sf::Vector2f(squareDim - 1, squareDim - 1));
            }
            else 
            {
                square.setSize(sf::Vector2f(squareDim, squareDim));
            }
            square.setOutlineColor(sf::Color(192, 192, 192));
            square.setOutlineThickness(1);
            square.setPosition((squareDim * j) + 35, (squareDim * i) + 15);
            canvas->draw(square);
        }
	}
}

void Display::render()
{
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            gui->handleEvent(event);

            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear(sf::Color(255, 255, 255));
        gui->draw();
        canvas->display();
        window->display();

        if (gui->get<tgui::RadioButton>("editStart")->isChecked()) 
        {
            
            editStart();
        }
        else if (gui->get<tgui::RadioButton>("editEnd")->isChecked())
        {
            editEnd();
            
        }
        else if (gui->get<tgui::RadioButton>("editWall")->isChecked())
        {
            editWall();
            
        }
    }
}


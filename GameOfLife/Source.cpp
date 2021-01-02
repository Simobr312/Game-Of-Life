#include <SFML/Graphics.hpp>
#include <iostream>

#include "Grid.h"


void PollEvents(sf::RenderWindow& window, sf::View& view);
void CamScrolling(sf::View& view, sf::Vector2i mousePosWindow);

sf::Vector2i mousePosView;

//Init clocks
sf::Clock timer;
float dt	= 0;
float maxdt = 0.2;

//Cam Acceleration
float camacc = 1.f;

int main() {
	//Init window
	sf::RenderWindow window({ 1280, 720}, "Game of Life", sf::Style::Close);
	window.setFramerateLimit(120);
	
	//Init view
	sf::View view = window.getDefaultView();
	window.setView(view);
	 
	//Init grid
	Grid grid(window);

	//Init mouse selector
	grid.InitSelector();

	while (window.isOpen()) {
		dt += timer.restart().asSeconds();
		PollEvents(window, view);


		//Uptade mousepos
		sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);
		sf::Vector2f mousePosView = window.mapPixelToCoords(mousePosWindow);

		//Cam Scrolling
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			CamScrolling(view, mousePosWindow);
			window.setView(view);
		} else camacc = 1;

		//Fixing the viewpos
		if(view.getSize().x >= window.getSize().x && view.getSize().y >= window.getSize().y)
			view = window.getDefaultView();

		//Uptade Selector 
		grid.UptadeSelector(mousePosView);

		//Uptade grid
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && dt >= maxdt) {
			grid.UptadeToNextGen();
			dt = 0;
		}

		//Clear the window
		window.clear();

		//Rendering
		grid.Draw();
		grid.DrawSelector();

		//Dispay
		window.display();
	}
	return 0;
}

void PollEvents(sf::RenderWindow& window, sf::View& view) {
	sf::Event e;
	while (window.pollEvent(e)) {
		switch (e.type)
		{
		case sf::Event::Closed: 
			window.close();
			break;
		case sf::Event::MouseWheelMoved:
			if (e.mouseWheel.delta > 0) view.zoom(0.9);
			else if (e.mouseWheel.delta < 0) view.zoom(1.1);

			window.setView(view);
			break;
		case sf::Event::KeyPressed:

			if (e.key.code == sf::Keyboard::Left)	maxdt += 0.9;
			if (e.key.code == sf::Keyboard::Right)	maxdt -= 0.9;

			maxdt = std::max(std::min(maxdt, 1.f), 0.02f);

			break;
		default: break;
		}
	}
}

void CamScrolling(sf::View& view, sf::Vector2i mousePosWindow)
{
	
	sf::Vector2f delta((float)mousePosWindow.x - view.getCenter().x,
		(float)mousePosWindow.y - view.getCenter().y);

	sf::Vector2f mousedir(delta.x/abs(delta.x), delta.y/abs(delta.y));

	view.move(mousedir.x * camacc, mousedir.y * camacc);
	camacc += 0.05;

}

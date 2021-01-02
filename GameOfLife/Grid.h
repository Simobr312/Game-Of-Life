#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

const float cellSizeF = 6.f; //Size of a cell in float

class Grid
{
private:
	sf::RenderWindow& window_ref;
	sf::Vector2u mapSize;

	std::vector<std::vector<bool>> states;

	sf::Vector2i mousePosGrid;
	sf::RectangleShape selector;

	sf::Clock toggleClock;
	float tdt;

public:
	Grid(sf::RenderWindow& window);
	~Grid();

	void UptadeToNextGen();
	void Draw();

	//Selector
	void InitSelector();
	void UptadeSelector(sf::Vector2f mousePosWiew);
	void ToggleSelector();
	void DrawSelector();
};


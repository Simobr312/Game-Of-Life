#pragma once
#include <SFML/Graphics.hpp>
const int LENGHT = 1280;
const int HEIGHT = 720;

const int CellSize = 50;

class Cell
{
private:
	sf::RectangleShape body;
	bool isActive;
public:
	Cell(float x, float y, bool isActive);
	~Cell();

	void Uptade();
	void Draw(sf::RenderWindow& window);

	void Toggle() { isActive = !isActive; };
	void SetState(bool state) { isActive = state;  }
	
	bool GetState() { return isActive; }
};


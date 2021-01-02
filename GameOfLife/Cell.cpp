#include "Cell.h"
#include <iostream>

Cell::Cell(float x, float y, bool isActive)
{
	this->isActive = isActive;

	body.setSize({ CellSize, CellSize });
	body.setPosition(x * CellSize, y * CellSize);
}

Cell::~Cell()
{
}

void Cell::Uptade()
{
	if (isActive)
		body.setFillColor(sf::Color::White);
	else
		body.setFillColor(sf::Color::Black);
}

void Cell::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

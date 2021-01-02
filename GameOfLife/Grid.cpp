#include "Grid.h"

#include <iostream>

Grid::Grid(sf::RenderWindow& window)
	:window_ref(window), mapSize(window_ref.getSize().x / cellSizeF, window_ref.getSize().x / cellSizeF)
{
	states.resize(mapSize.x + 2, std::vector<bool>());

	for (int x = 0; x < mapSize.x + 2; ++x) {
		states[x].resize(mapSize.y + 2, bool());
		for (int y = 0; y < mapSize.y + 2; ++y) {
			states[x][y] = false;
		}
	}

}

Grid::~Grid()
{
}

void Grid::UptadeToNextGen()
{
	std::vector < std::vector<bool>> t_states( states );

	for (int x = 1; x < mapSize.x + 1; ++x) {
		for (int y = 1; y < mapSize.y + 1; ++y) {
			int neighbor =	t_states[x - 1][y - 1]	+ t_states[x][y - 1]	+ t_states[x + 1][y - 1]	+
							t_states[x - 1][y]		+			0			+ t_states[x + 1][y]		+
							t_states[x - 1][y + 1]	+ t_states[x][y + 1]	+ t_states[x + 1][y + 1]	;

			if (t_states[x][y] && (neighbor > 3 || neighbor < 2))
				states[x][y] = false;
			else if (!t_states[x][y] && neighbor == 3)
				states[x][y] = true;

		}

	}
}

void Grid::Draw()
{
	for (unsigned x = 0; x < mapSize.x + 2; ++x) {
		for (unsigned y = 0; y < mapSize.y + 2; ++y) {
			if (states[x][y] == true) {
				sf::RectangleShape cell(sf::Vector2f(cellSizeF, cellSizeF));
				cell.setPosition(x * cellSizeF, y * cellSizeF);
				window_ref.draw(cell);
			}
		}
	}
}

///
///Selector
/// 
void Grid::InitSelector()
{
	selector = sf::RectangleShape(sf::Vector2f(cellSizeF, cellSizeF));
	selector.setFillColor(sf::Color::Transparent);
	selector.setOutlineThickness(1.f);
	selector.setOutlineColor(sf::Color::Green);
}

void Grid::UptadeSelector(sf::Vector2f mousePosWiew)
{
	tdt += toggleClock.restart().asSeconds();

	if (mousePosWiew.x >= 0 && mousePosWiew.x <= mapSize.x * cellSizeF)
		mousePosGrid.x = mousePosWiew.x / (unsigned)cellSizeF;
	if (mousePosWiew.y >= 0 && mousePosWiew.y <= mapSize.y * cellSizeF)
		mousePosGrid.y = mousePosWiew.y / (unsigned)cellSizeF;

	selector.setPosition((sf::Vector2f)mousePosGrid * cellSizeF);

	ToggleSelector();
}

void Grid::ToggleSelector()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && tdt >= 0.2f) {

		states[mousePosGrid.x][mousePosGrid.y] = states[mousePosGrid.x][mousePosGrid.y] ? false : true;
		tdt = 0;
	}
}

void Grid::DrawSelector()
{
	window_ref.draw(selector);
}

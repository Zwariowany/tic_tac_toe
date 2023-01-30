#pragma once

#include "resources.h"

class Cell {
public:
	enum class CellStatus {
		EMPTY,
		CROSS,
		CIRCLE
	};

private:
	sf::Sprite _sprite;
	CellStatus _cellStatus;

	void updateSprite();

public:
	Cell();

	void setPosition(sf::Vector2f position);

	CellStatus getStatus();
	void setStatus(CellStatus status);

	sf::Sprite& getSprite();

	sf::FloatRect getGlobalBounds();
};

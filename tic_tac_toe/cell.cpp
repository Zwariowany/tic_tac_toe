#include "cell.h"
#include "cell.h"

void Cell::updateSprite() {
	switch (this->_cellStatus) {
	case CellStatus::EMPTY:
		this->_sprite.setTexture(resources.getTexture("EmptyCell"));
		break;
	case CellStatus::CROSS:
		this->_sprite.setTexture(resources.getTexture("CrossCell"));
		break;
	case CellStatus::CIRCLE:
		this->_sprite.setTexture(resources.getTexture("CircleCell"));
		break;
	default:
		break;
	}
}

Cell::Cell() {
	this->_cellStatus = CellStatus::EMPTY;
	this->setStatus(CellStatus::EMPTY);
}

void Cell::setPosition(sf::Vector2f position) {
	this->_sprite.setPosition(position);
}

Cell::CellStatus Cell::getStatus() {
	return this->_cellStatus;
}

void Cell::setStatus(CellStatus status) {
	if (this->_cellStatus == CellStatus::EMPTY) {
		this->_cellStatus = status;
		this->updateSprite();
	}
}

sf::Sprite& Cell::getSprite() {
	return this->_sprite;
}

sf::FloatRect Cell::getGlobalBounds() {
	return this->_sprite.getGlobalBounds();
}

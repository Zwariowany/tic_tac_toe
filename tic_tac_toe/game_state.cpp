#include "game_state.h"

void GameState::checkCollision() {
	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*this->_window));
	sf::FloatRect bounds;

	int x = 0;
	int y = 0;

	for (auto& column : this->_cells) {
		y = 0;

		for (auto& cell : column) {
			bounds = cell.getGlobalBounds();

			if (bounds.contains(mousePosition)) {
				if (cell.getStatus() == Cell::CellStatus::EMPTY) {
					cell.setStatus(this->_currentPlayer);
					this->changePlayer();
					this->checkIfWin(sf::Vector2i(x, y));
				}
				break;
			}
			y++;
		}
		x++;
	}
}

void GameState::changePlayer() {
	if (this->_currentPlayer == Cell::CellStatus::CIRCLE) {
		this->_currentPlayer = Cell::CellStatus::CROSS;
	}
	else {
		this->_currentPlayer = Cell::CellStatus::CIRCLE;
	}

	this->updatePlayerVisualizer();
}

void GameState::updatePlayerVisualizer() {
	switch (this->_currentPlayer) {
	case Cell::CellStatus::CROSS:
		this->_playerVisualizer.setTexture(resources.getTexture("Cross"));
		break;
	case Cell::CellStatus::CIRCLE:
		this->_playerVisualizer.setTexture(resources.getTexture("Circle"));
		break;
	case Cell::CellStatus::EMPTY:
	default:
		break;
	}
}

void GameState::checkIfWin(sf::Vector2i position) {
	for (auto& possibility : this->_possibilities) {
		sf::Vector2i prevPosition = position + possibility.first;
		sf::Vector2i nextPosition = position + possibility.second;

		if (this->isInBoard(prevPosition) && this->isInBoard(nextPosition)) {
			if (this->_cells[prevPosition.x][prevPosition.y].getStatus() == this->_cells[position.x][position.y].getStatus() &&
				this->_cells[position.x][position.y].getStatus() == this->_cells[nextPosition.x][nextPosition.y].getStatus()) {
				this->_endGame = true;
				break;
			}
		}
	}

	int counter = 0;

	for (auto& column : this->_cells) {
		for (auto& cell : column) {
			if (cell.getStatus() != Cell::CellStatus::EMPTY) {
				counter++;
			}
		}
	}

	if (counter == BOARD_WIDTH * BOARD_HEIGHT) {
		_endGame = true;
	}
}

bool GameState::isInBoard(sf::Vector2i position) {
	return (position.x >= 0 && position.y >= 0 && position.x < BOARD_WIDTH&& position.y < BOARD_HEIGHT);
}

void GameState::resetGame() {
	_endGame = false;
	initCells();
}

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states) {

}

void GameState::initCells() {
	this->_cells.clear();
	this->_cells.resize(BOARD_WIDTH, {});

	for (auto& x : this->_cells) {
		x.resize(BOARD_HEIGHT, Cell());
	}

	sf::Vector2f startPosition = sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	startPosition.x -= BOARD_WIDTH / 2 * CELL_SIZE + CELL_SIZE / 2;
	startPosition.y -= BOARD_HEIGHT / 2 * CELL_SIZE + CELL_SIZE / 2;

	sf::Vector2f cellPosition;

	int x = 0;
	int y = 0;

	for (auto& column : this->_cells) {
		y = 0;

		for (auto& cell : column) {
			cellPosition = startPosition;
			cellPosition.x += x * CELL_SIZE;
			cellPosition.y += y * CELL_SIZE;

			cell.setPosition(cellPosition);

			y++;
		}

		x++;
	}
}

void GameState::start() {
	this->initCells();

	this->_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	this->_background.setFillColor(sf::Color(25, 42, 50));

	sf::Vector2f position = sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	position.x -= CELL_SIZE;
	position.y -= (BOARD_HEIGHT / 2.0 + 1) * CELL_SIZE;
	this->_playerVisualizer.setPosition(position);

	position = sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	position.x -= CELL_SIZE;
	position.y += (BOARD_HEIGHT / 2.0) * CELL_SIZE;
	this->_replayButton.setPosition(position);
	this->_replayButton.setTexture(resources.getTexture("Replay"));

	this->_currentPlayer = Cell::CellStatus::CROSS;
	this->updatePlayerVisualizer();
	this->_endGame = false;
}

void GameState::updateEvent(sf::Event event) {
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		if (!_endGame) {
			this->checkCollision();
		}
		else {
			sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*this->_window));
			sf::FloatRect bounds = this->_replayButton.getGlobalBounds();

			if (bounds.contains(mousePosition)) {
				resetGame();
			}
		}

	}
}

void GameState::update() {
}

void GameState::render() {
	this->_window->draw(_background);
	this->_window->draw(_playerVisualizer);

	if (_endGame) {
		this->_window->draw(_replayButton);
	}

	for (auto& column : this->_cells) {
		for (auto& cell : column) {
			this->_window->draw(cell.getSprite());
		}
	}
}

void GameState::end() {
}

void GameState::switchState() {
}

#include "game.h"

void Game::initWindow() {
	this->_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tic Tac Toe");
	this->_window.setActive(true);
	this->_window.setVerticalSyncEnabled(false);
	this->_window.setFramerateLimit(120);
	this->_window.setKeyRepeatEnabled(false);
}

void Game::updateEvent() {
	while (this->_window.pollEvent(this->_event)) {
		if (this->_event.type == sf::Event::Closed) {
			_window.close();
		}

		this->_states.top()->updateEvent(this->_event);
	}
}

void Game::update() {
	this->_states.top()->update();
}

void Game::render() {
	this->_window.clear();

	this->_states.top()->render();

	this->_window.display();
}

Game::Game() {
	initWindow();

	this->_states.push(new GameState(&_window, &this->_states));
	this->_states.top()->start();
}

void Game::run() {
	while (this->_window.isOpen()) {
		this->updateEvent();
		this->update();
		this->render();
	}
}
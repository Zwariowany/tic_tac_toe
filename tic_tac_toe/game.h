#pragma once

#include <stack>
#include <SFML/Graphics.hpp>

#include "state.h"
#include "game_state.h"

class Game {
private:
	sf::RenderWindow _window;
	sf::Event _event;

	std::stack<State*> _states;

	void initWindow();

	void updateEvent();
	void update();
	void render();

public:
	Game();

	void run();
};


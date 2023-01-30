#pragma once

#include <stack>

#include <SFML/Graphics.hpp>

class State {
private:

protected:
	sf::RenderWindow* _window;
	std::stack<State*>* _states;

public:
	State(sf::RenderWindow* window, std::stack<State*>* states);

	virtual void start() = 0;
	virtual void updateEvent(sf::Event event) = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void end() = 0;
	virtual void switchState() = 0;
};

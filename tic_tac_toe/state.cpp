#include "state.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states) {
	this->_window = window;
	this->_states = states;
}
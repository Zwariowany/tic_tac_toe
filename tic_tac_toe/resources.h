#pragma once

#include <iostream>
#include <map>
#include <string>

#include <SFML/Graphics.hpp>

class Resources {
private:
	std::map<std::string, sf::Texture> _textures;

	std::map<std::string, std::string> _texturesToLoad{
		{"EmptyCell", "images/empty_cell.png"},
		{"CircleCell", "images/circle_cell.png"},
		{"CrossCell", "images/cross_cell.png"},
		{"Circle", "images/player_visualizer_circle.png"},
		{"Cross", "images/player_visualizer_cross.png"},
		{"Replay", "images/replay.png"}
	};

	void loadTextures();
	void loadTexture(std::string name, std::string path);
public:
	Resources();

	sf::Texture& getTexture(std::string name);
};

inline Resources resources;
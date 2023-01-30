#include "resources.h"

void Resources::loadTextures() {
	for (auto& [name, path] : this->_texturesToLoad) {
		this->loadTexture(name, path);
	}
}

void Resources::loadTexture(std::string name, std::string path) {
	sf::Texture texture;

	if (texture.loadFromFile(path)) {
		this->_textures[name] = texture;
	}
}

Resources::Resources() {
	this->loadTextures();
}

sf::Texture& Resources::getTexture(std::string name) {
	return this->_textures[name];
}

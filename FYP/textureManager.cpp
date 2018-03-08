#include "textureManager.hpp"

TextureManager TextureManager::textureManager;

void TextureManager::LoadTexture(std::string fileName) {
	sf::Texture texture;
	texture.loadFromFile(filePath + fileName);
	
	textures[fileName] = texture;
}
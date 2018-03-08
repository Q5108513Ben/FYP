#pragma once

#include "textureManager.hpp"
#include "SFML\Graphics.hpp"

namespace SpriteCreator {
	sf::Sprite Create(std::string fileName) {
		TextureManager::Instance()->LoadTexture(fileName);
		sf::Sprite sprite;
		sprite.setTexture(TextureManager::Instance()->textures[fileName]);

		return sprite;
	}
}
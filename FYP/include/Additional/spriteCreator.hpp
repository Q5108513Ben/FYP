#pragma once

#include "Managers/textureManager.hpp"
#include "SFML/Graphics.hpp"

struct Position {
	int x, y;
	Position(int xPos, int yPos) : x(xPos), y(yPos) {}
};

namespace TextureCreator {
	static tgui::Texture Create(std::string fileName) {
		TextureManager::Instance()->LoadTexture(fileName);
		tgui::Texture texture;
		texture.load(TextureManager::Instance()->textures[fileName]);

		return texture;
	}
}

namespace SpriteCreator {
	static sf::Sprite Create(std::string fileName) {
		TextureManager::Instance()->LoadTexture(fileName);
		sf::Sprite sprite;
		sprite.setTexture(TextureManager::Instance()->textures[fileName]);

		return sprite;
	}

	static sf::Sprite Create(std::string fileName, Position pos) {
		TextureManager::Instance()->LoadTexture(fileName);
		sf::Sprite sprite;
		sprite.setTexture(TextureManager::Instance()->textures[fileName]);
		sprite.setPosition((float)pos.x, (float)pos.y);

		return sprite;
	}
}

namespace ButtonCreator {
	static tgui::Picture::Ptr Create(std::string fileName, Position pos) {
		TextureManager::Instance()->LoadTexture(fileName);
		auto picture = tgui::Picture::create();
		picture->setTexture(TextureManager::Instance()->textures[fileName]);
		picture->scale(3, 3);
		picture->setPosition(pos.x, pos.y);
		picture->setOpacity(0);

		return picture;
	}
}
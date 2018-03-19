#pragma once

#include "TGUI\TGUI.hpp"
#include <unordered_map>

class TextureManager {
	public:
		void LoadTexture(std::string fileName);

		std::unordered_map<std::string, sf::Texture> textures;

		static TextureManager* Instance() { return &textureManager; }

	protected:
		TextureManager() { }

	private:
		static TextureManager textureManager;

		std::string filePath = "Images/";

};
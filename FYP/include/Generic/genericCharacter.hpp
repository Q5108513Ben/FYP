#pragma once
#include "tinyxml2.h"
#include <iostream>

class GenericCharacter {

	public:

		const unsigned  int& GetID() { return characterID; }
		const std::string& GetName() { return characterName; }

		void RetrieveCharacterData(tinyxml2::XMLElement* dataPtr);

	private:

		unsigned int characterID{ 0 };
		std::string characterName{ " " };

};
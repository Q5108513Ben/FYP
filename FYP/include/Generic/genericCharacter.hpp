#pragma once
#include "tinyxml2.h"
#include <vector>
#include <iostream>

class GenericCharacter {

	public:

		struct Class {
			unsigned int classID;
			std::string className;
		};

		const unsigned int& GetID() { return characterID; }
		const std::string& GetName() { return characterName; }
		const std::vector<Class>& GetClasses() { return classes; }

		void RetrieveCharacterData(tinyxml2::XMLElement* dataPtr);

	private:

		unsigned int characterID{ 0 };
		std::string characterName{ " " };
		std::vector<Class> classes;
};
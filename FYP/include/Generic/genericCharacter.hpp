#pragma once
#include "tinyxml2.h"
#include <unordered_map>
#include <iostream>

class GenericCharacter {

	public:

		struct Stats {
			int rawMainStat;
			int rawConstitution;
			int rawWisdom;
			int rawResilience;
			int rawResistance;
			int rawAffliction;
		};

		struct Class {
			unsigned int classID;
			std::string className;
			Stats classStats;
		};

		const unsigned int& GetID() { return characterID; }
		const std::string& GetName() { return characterName; }
		const std::unordered_map<unsigned int, Class>& GetClasses() { return classes; }
		const Class& GetClass(unsigned int id) { return classes[id]; }

		void RetrieveCharacterData(tinyxml2::XMLElement* dataPtr);

	private:

		unsigned int characterID{ 0 };
		std::string characterName{ " " };
		std::unordered_map<unsigned int, Class> classes;
};
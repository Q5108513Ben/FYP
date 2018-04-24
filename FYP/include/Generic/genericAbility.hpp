#pragma once
#include "tinyxml2.h"
#include <unordered_map>
#include <iostream>

class GenericAbility {

	public:

		const unsigned int& GetID() { return abilityID; }
		const std::string& GetName() { return abilityName; }

		void RetrieveAbilityData(tinyxml2::XMLElement* dataPtr);

	private:

		unsigned int abilityID{ 0 };
		std::string abilityName{ "" };
};
#pragma once
#include "tinyxml2.h"
#include <unordered_map>
#include <iostream>

class GenericAbility {

	private:

		struct Effect {
			unsigned int effectID;
			std::string effectName;
		};

		struct Tag {
			unsigned int tagID;
			std::string tagName;
		};

	public:

		const unsigned int& GetID() { return abilityID; }
		const std::string& GetName() { return abilityName; }
		const std::unordered_map<unsigned int, Effect>& GetEffects() { return effects; }
		const std::unordered_map<unsigned int, Tag>& GetTags() { return tags; }

		void RetrieveAbilityData(tinyxml2::XMLElement* dataPtr);

	private:

		unsigned int abilityID{ 0 };
		std::string abilityName{ "" };
		std::unordered_map<unsigned int, Effect> effects;
		std::unordered_map<unsigned int, Tag> tags;
};
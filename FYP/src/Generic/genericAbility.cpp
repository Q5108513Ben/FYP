#include "Generic/genericAbility.hpp"

void GenericAbility::RetrieveAbilityData(tinyxml2::XMLElement* dataPtr) {
	abilityID = dataPtr->FirstChildElement("ID")->FloatText();
	abilityName = dataPtr->FirstChildElement("AbilityName")->GetText();

	tinyxml2::XMLElement* effectPtr = dataPtr->FirstChildElement("Effects");
	effectPtr = effectPtr->FirstChildElement();
	while (effectPtr != nullptr) {
		Effect e;
		e.effectID = effectPtr->IntAttribute("id");
		e.effectName = effectPtr->Attribute("name");

		effects[e.effectID] = e;
		effectPtr = effectPtr->NextSiblingElement();
	}

	tinyxml2::XMLElement* tagPtr = dataPtr->FirstChildElement("Tags");
	tagPtr = tagPtr->FirstChildElement();
	while (tagPtr != nullptr) {
		Tag t;
		t.tagID = tagPtr->IntAttribute("id");
		t.tagName = tagPtr->Attribute("name");

		tags[t.tagID] = t;
		tagPtr = tagPtr->NextSiblingElement();
	}
}
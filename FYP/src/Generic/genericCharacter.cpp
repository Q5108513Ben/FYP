#include "Generic/genericCharacter.hpp"

void GenericCharacter::RetrieveCharacterData(tinyxml2::XMLElement* dataPtr) {
	characterID = dataPtr->FirstChildElement("ID")->FloatText();
	characterName = dataPtr->FirstChildElement("CharacterName")->GetText();

	dataPtr = dataPtr->FirstChildElement("Classes");
	dataPtr = dataPtr->FirstChildElement();
	while (dataPtr != nullptr) {
		Class c;
		c.classID = dataPtr->FirstChildElement("ID")->FloatText();
		c.className = dataPtr->FirstChildElement("ClassName")->GetText();

		tinyxml2::XMLElement* statPtr = dataPtr->FirstChildElement("Stats");
		c.classStats.rawMainStat = statPtr->FirstChildElement("MainStat")->FloatText();
		c.classStats.rawConstitution = statPtr->FirstChildElement("Constitution")->FloatText();
		c.classStats.rawWisdom = statPtr->FirstChildElement("Wisdom")->FloatText();
		c.classStats.rawResilience = statPtr->FirstChildElement("Resilience")->FloatText();
		c.classStats.rawResistance = statPtr->FirstChildElement("Resistance")->FloatText();
		c.classStats.rawAffliction = statPtr->FirstChildElement("Affliction")->FloatText();

		classes[c.classID] = c;

		dataPtr = dataPtr->NextSiblingElement();
	}
}
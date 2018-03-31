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

		classes[c.classID] = c;

		dataPtr = dataPtr->NextSiblingElement();
	}
}
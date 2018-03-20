#include "Generic/genericCharacter.hpp"

void GenericCharacter::RetrieveCharacterData(tinyxml2::XMLElement* dataPtr) {
	characterID = dataPtr->FirstChildElement("ID")->FloatText();
	characterName = dataPtr->FirstChildElement("CharacterName")->GetText();
}
#include "Managers/dataManager.hpp"

DataManager DataManager::dataManager;

void DataManager::RetrieveCharacterData(tinyxml2::XMLNode* root) {
	tinyxml2::XMLElement* characterPtr = root->FirstChildElement();

	while (characterPtr != nullptr) {
		GenericCharacter character;
		character.RetrieveCharacterData(characterPtr);

		charactersMap[character.GetID()] = character;

		characterPtr = characterPtr->NextSiblingElement();
	}
}
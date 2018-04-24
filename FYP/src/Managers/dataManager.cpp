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

void DataManager::RetrieveEnemyData(tinyxml2::XMLNode* root) {
	tinyxml2::XMLElement* enemyPtr = root->FirstChildElement();

	while (enemyPtr != nullptr) {
		GenericEnemy enemy;
		enemy.RetrieveEnemyData(enemyPtr);

		enemiesMap[enemy.GetID()] = enemy;

		enemyPtr = enemyPtr->NextSiblingElement();
	}
}

void DataManager::RetrieveAbilityData(tinyxml2::XMLNode* root) {
	tinyxml2::XMLElement* abilityPtr = root->FirstChildElement();

	while (abilityPtr != nullptr) {
		GenericAbility ability;
		ability.RetrieveAbilityData(abilityPtr);

		abilitiesMap[ability.GetID()] = ability;

		abilityPtr = abilityPtr->NextSiblingElement();
	}
}
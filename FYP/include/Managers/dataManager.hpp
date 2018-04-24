#pragma once
#include "Generic/genericCharacter.hpp"
#include "Generic/genericEnemy.hpp"
#include "Generic/genericAbility.hpp"
#include <unordered_map>

class DataManager {
	public:

		void RetrieveCharacterData(tinyxml2::XMLNode* root);
		const GenericCharacter& GetCharacter(unsigned int ID) { return charactersMap[ID]; }
		const std::unordered_map<unsigned int, GenericCharacter>& GetAllCharacters() { return charactersMap; }

		void RetrieveEnemyData(tinyxml2::XMLNode* root);
		const GenericEnemy& GetEnemy(unsigned int ID) { return enemiesMap[ID]; }
		const std::unordered_map<unsigned int, GenericEnemy>& GetAllEnemies() { return enemiesMap; }

		void RetrieveAbilityData(tinyxml2::XMLNode* root);
		const GenericAbility& GetAbility(unsigned int ID) { return abilitiesMap[ID]; }
		const std::unordered_map<unsigned int, GenericAbility>& GetAllAbilities() { return abilitiesMap; }

		static DataManager* Instance() { return &dataManager; }

	private:

		std::unordered_map<unsigned int, GenericCharacter> charactersMap;
		std::unordered_map<unsigned int, GenericEnemy> enemiesMap;
		std::unordered_map<unsigned int, GenericAbility> abilitiesMap;

		static DataManager dataManager;

	protected:

		DataManager() { }
};
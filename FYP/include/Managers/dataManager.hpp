#pragma once
#include "Generic/genericCharacter.hpp"
#include <unordered_map>

class DataManager {
	public:

		void RetrieveCharacterData(tinyxml2::XMLNode* root);
		const GenericCharacter& GetCharacter(unsigned int ID) { return charactersMap[ID]; }
		const std::unordered_map<unsigned int, GenericCharacter>& GetAllCharacters() { return charactersMap; }

		static DataManager* Instance() { return &dataManager; }

	private:

		std::unordered_map<unsigned int, GenericCharacter> charactersMap;

		static DataManager dataManager;

	protected:

		DataManager() { }
};
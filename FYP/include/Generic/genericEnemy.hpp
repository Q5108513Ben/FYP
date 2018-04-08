#pragma once
#include "tinyxml2.h"
#include <unordered_map>
#include <iostream>

class GenericEnemy {

	public:

		const unsigned int& GetID() { return enemyID; }
		const std::string& GetName() { return enemyName; }

		void RetrieveEnemyData(tinyxml2::XMLElement* dataPtr);

	private:

		unsigned int enemyID{ 0 };
		std::string enemyName{ " " };
};
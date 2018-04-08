#include "Generic/genericEnemy.hpp"

void GenericEnemy::RetrieveEnemyData(tinyxml2::XMLElement* dataPtr) {
	enemyID = dataPtr->FirstChildElement("ID")->FloatText();
	enemyName = dataPtr->FirstChildElement("EnemyName")->GetText();
}
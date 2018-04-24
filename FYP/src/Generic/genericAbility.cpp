#include "Generic/genericAbility.hpp"

void GenericAbility::RetrieveAbilityData(tinyxml2::XMLElement* dataPtr) {
	abilityID = dataPtr->FirstChildElement("ID")->FloatText();
	abilityName = dataPtr->FirstChildElement("AbilityName")->GetText();
}
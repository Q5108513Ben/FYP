#include "includeStates.hpp"
#include "Additional/spriteCreator.hpp"
#include "Additional/typeConverter.hpp"
#include "Managers/dataManager.hpp"

CharacterEditState CharacterEditState::characterstate;

void CharacterEditState::Initialise(sf::RenderWindow* window, tgui::Gui* gui) {
	windowRef = window;
	guiRef = gui;

	//-------Loading-XML-Data----------\\

	tinyxml2::XMLDocument characterXML;
	characterXML.LoadFile("data/Character.xml");
	DataManager::Instance()->RetrieveCharacterData(characterXML.RootElement());

	//---------Static-Images-----------\\

	sprites.push_back(SpriteCreator::Create("ListBackground.png", Position(810, 330)));

	auto characterInfo = ButtonCreator::Create("CharacterInfo.png", Position(24, 105));
	characterInfo->setOpacity(100);
	characterInfo->hide();
	guiRef->add(characterInfo, "CharacterInfo");

	auto classInfo = ButtonCreator::Create("ClassInfo.png", Position(345, 90));
	classInfo->setOpacity(100);
	classInfo->hide();
	guiRef->add(classInfo, "ClassInfo");

	//------Character-List-Search------\\

	auto search = ButtonCreator::Create("ListSearch.png", Position(816, 333));
	search->setOpacity(100);
	guiRef->add(search, "Search");
	search->connect("Clicked", &CharacterEditState::ShowSearch, &characterstate, "Search", "SearchText");

	auto searchText = tgui::EditBox::copy(guiRef->get<tgui::EditBox>("EditBox"));
	searchText->enable();
	searchText->setPosition(816, 333);
	searchText->setSize(144, 18);
	guiRef->add(searchText, "SearchText");
	searchText->connect("Unfocused", &CharacterEditState::UnfocusSearch, &characterstate, "Search", "SearchText");
	searchText->connect("Unfocused", &CharacterEditState::CheckSearchBar, &characterstate);

	//---------Character-List----------\\

	auto characterList = tgui::ListBox::copy(guiRef->get<tgui::ListBox>("ListBox"));
	characterList->setPosition(821, 381);
	characterList->setSize(165, 267);
	characterList->show();
	characterList->enable();
	guiRef->add(characterList, "CharacterList");
	characterList->connect("ItemSelected", &CharacterEditState::LoadCharacter, &characterstate);

	for (auto character : DataManager::Instance()->GetAllCharacters()) {
		characterList->addItem(character.second.GetName(), character.first);
	}

	//---------Character-Name---------\\

	auto name = ButtonCreator::Create("CharacterName.png", Position(126, 105));
	name->setOpacity(100);
	name->hide();
	guiRef->add(name, "CharacterName");
	name->connect("Clicked", &CharacterEditState::ShowSearch, &characterstate, "CharacterName", "CharacterNameText");

	auto nameText = tgui::EditBox::copy(guiRef->get<tgui::EditBox>("EditBox"));
	nameText->enable();
	nameText->setPosition(129, 108);
	nameText->setSize(183, 21);
	guiRef->add(nameText, "CharacterNameText");
	nameText->connect("Unfocused", &CharacterEditState::UnfocusSearch, &characterstate, "CharacterName", "CharacterNameText");
	nameText->connect("Unfocused", &CharacterEditState::CheckNameChange, &characterstate);

	//-----------Class-List------------\\

	auto classList = tgui::ListBox::copy(guiRef->get<tgui::ListBox>("ListBox"));
	classList->setPosition(36, 174);
	classList->setSize(165, 267);
	classList->enable();
	guiRef->add(classList, "ClassList");
	classList->connect("ItemSelected", &CharacterEditState::LoadClass, &characterstate);

	//-----------Class-Name------------\\

	auto className = ButtonCreator::Create("CharacterName.png", Position(525, 105));
	className->setOpacity(100);
	className->hide();
	guiRef->add(className, "ClassName");
	className->connect("Clicked", &CharacterEditState::ShowSearch, &characterstate, "ClassName", "ClassNameText");

	auto classNameText = tgui::EditBox::copy(guiRef->get<tgui::EditBox>("EditBox"));
	classNameText->enable();
	classNameText->setPosition(528, 108);
	classNameText->setSize(183, 21);
	guiRef->add(classNameText, "ClassNameText");
	classNameText->connect("Unfocused", &CharacterEditState::UnfocusSearch, &characterstate, "ClassName", "ClassNameText");
	classNameText->connect("Unfocused", &CharacterEditState::CheckClassNameChange, &characterstate);

	//-----------Class-Stats-----------\\
	
	auto statTotal = tgui::EditBox::copy(guiRef->get<tgui::EditBox>("EditBox"));
	statTotal->show();
	statTotal->setPosition(570, 144);
	statTotal->setSize(33, 21);
	statTotal->setAlignment(tgui::EditBox::Alignment::Right);
	statTotal->setText(std::to_string(statRemaining));
	statTotal->getRenderer()->setTextColor(sf::Color(51, 51, 51, 255));
	statTotal->setTextSize(24);
	guiRef->add(statTotal, "StatTotal");

	unsigned int offset = 0;

	for (int i = 0; i < 6; i++) {
		auto statValue = tgui::EditBox::copy(guiRef->get<tgui::EditBox>("EditBox"));
		statValue->enable();
		statValue->show();
		statValue->setPosition(567, 174 + offset);
		statValue->setSize(30, 21);
		statValue->setAlignment(tgui::EditBox::Alignment::Right);
		statValue->setText("0");
		statValue->setMaximumCharacters(2);
		guiRef->add(statValue, "StatValue" + i);
		statValue->connect("Unfocused", &CharacterEditState::UpdateStatTotal, &characterstate, i);

		offset += 24;
	}
}

void CharacterEditState::CleanUp() {

}

void CharacterEditState::Pause() {
	HideUI(CharacterList);
	HideUI(CharacterInfo);
	HideUI(ClassInfo);
}

void CharacterEditState::Resume() {
	(!searchEntered) ? guiRef->get("Search")->show() : guiRef->get("SearchText")->show();
	guiRef->get("CharacterList")->show();

	if (CheckListSelected("CharacterList")) {
		guiRef->get("CharacterInfo")->show();
		guiRef->get("CharacterNameText")->show();
		guiRef->get("ClassList")->show();

		(nameChanged) ? guiRef->get<tgui::EditBox>("CharacterNameText")->setText(nameEdited) :
						guiRef->get<tgui::EditBox>("CharacterNameText")->setText(nameSaved);

		if (CheckListSelected("ClassList")) {
			guiRef->get("ClassInfo")->show();
			guiRef->get("ClassNameText")->show();

			(classNameChanged) ? guiRef->get<tgui::EditBox>("ClassNameText")->setText(classNameEdited) :
								 guiRef->get<tgui::EditBox>("ClassNameText")->setText(classNameSaved);
		}
	}
}

void CharacterEditState::HandleEvent(StateMachine* machine, sf::Event event) {

}

void CharacterEditState::Update(StateMachine* machine) {

}

void CharacterEditState::Render(StateMachine* machine) {
	for (auto sprite : sprites) {
		sprite.scale(3, 3);
		windowRef->draw(sprite);
	}
}

void CharacterEditState::ShowSearch(sf::String imageName, sf::String searchName) {
	guiRef->get(imageName)->hide();
	guiRef->get(searchName)->show();
	guiRef->get(searchName)->focus();
}

void CharacterEditState::UnfocusSearch(sf::String imageName, sf::String searchName) {
	sf::String textInBox = guiRef->get<tgui::EditBox>(searchName)->getText();
	sf::String noText = "";

	if (textInBox != noText) {
		return;
	}
	else {
		guiRef->get(searchName)->hide();
		guiRef->get(imageName)->showWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(0.25));
	}
}

void CharacterEditState::LoadCharacter() {
	if (!CheckListSelected("CharacterList")) {
		HideUI(CharacterInfo);
		HideUI(ClassInfo);
		return;
	}
	guiRef->get("CharacterInfo")->show();
	guiRef->get("CharacterName")->hide();
	guiRef->get("CharacterNameText")->show();
	guiRef->get("ClassList")->show();
	
	HideUI(ClassInfo);
	
	auto selected = guiRef->get<tgui::ListBox>("CharacterList")->getSelectedItemId();
	unsigned int itemID = (unsigned int)*selected.getData();

	if (itemID == NULL) { return; }

	auto tempChar = DataManager::Instance()->GetCharacter(itemID);

	guiRef->get<tgui::EditBox>("CharacterNameText")->setText(tempChar.GetName());
	nameSaved = tempChar.GetName();

	guiRef->get<tgui::ListBox>("ClassList")->removeAllItems();

	for (auto c : tempChar.GetClasses()) {
		guiRef->get<tgui::ListBox>("ClassList")->addItem(c.second.className, c.first);
	}
}

void CharacterEditState::LoadClass() {
	if (!CheckListSelected("ClassList")) {
		HideUI(ClassInfo);
		return;
	}

	guiRef->get("ClassInfo")->show();
	guiRef->get("ClassName")->hide();
	guiRef->get("ClassNameText")->show();

	auto selectedCharacter = guiRef->get<tgui::ListBox>("CharacterList")->getSelectedItemId();
	unsigned int characterID = (unsigned int)*selectedCharacter.getData();

	auto selectedClass = guiRef->get<tgui::ListBox>("ClassList")->getSelectedItemId();
	unsigned int classID = (unsigned int)*selectedClass.getData();

	if (classID == NULL) { return; }

	auto tempChar = DataManager::Instance()->GetCharacter(characterID);
	auto tempClass = tempChar.GetClass(classID);

	guiRef->get<tgui::EditBox>("ClassNameText")->setText(tempClass.className);
	classNameSaved = tempClass.className;

}

bool CharacterEditState::CheckListSelected(sf::String listName) {
	if (guiRef->get<tgui::ListBox>(listName)->getSelectedItemIndex() == -1) {
		return false;
	}
	return true;
}

void CharacterEditState::CheckNameChange() {
	sf::String textInBox = guiRef->get<tgui::EditBox>("CharacterNameText")->getText();
	sf::String noText = "";

	if (textInBox != noText) {
		if (textInBox != nameSaved) {
			nameChanged = true;
			nameEdited = textInBox;
			return;
		}
		nameChanged = false;
		return;
	}
	else {
		nameChanged = false;
	}
}

void CharacterEditState::CheckClassNameChange() {
	sf::String textInBox = guiRef->get<tgui::EditBox>("ClassNameText")->getText();
	sf::String noText = "";

	if (textInBox != noText) {
		if (textInBox != classNameSaved) {
			classNameChanged = true;
			classNameEdited = textInBox;
			return;
		}
		classNameChanged = false;
		return;
	}
	else {
		classNameChanged = false;
	}
}

void CharacterEditState::UpdateStatTotal(int index) {
	sf::String textInBox = guiRef->get<tgui::EditBox>("StatValue" + index)->getText();
	std::string stringInBox = textInBox;
	int valueInBox = Convert::StringToInt(stringInBox);

	switch (index) {
	case 0:
		if (valueInBox < 0) {
			return;
		}
		(valueInBox < val0) ? IncStatRemaining(val0, valueInBox) : DecStatRemaining(val0, valueInBox);
		return;
	case 1:
		if (valueInBox < 0) {
			return;
		}
		(valueInBox < val1) ? IncStatRemaining(val1, valueInBox) : DecStatRemaining(val1, valueInBox);
		return;
	case 2:
		if (valueInBox < 0) {
			return;
		}
		(valueInBox < val2) ? IncStatRemaining(val2, valueInBox) : DecStatRemaining(val2, valueInBox);
		return;
	case 3:
		if (valueInBox < 0) {
			return;
		}
		(valueInBox < val3) ? IncStatRemaining(val3, valueInBox) : DecStatRemaining(val3, valueInBox);
		return;
	case 4:
		if (valueInBox < 0) {
			return;
		}
		(valueInBox < val4) ? IncStatRemaining(val4, valueInBox) : DecStatRemaining(val4, valueInBox);
		return;
	case 5:
		if (valueInBox < 0) {
			return;
		}
		(valueInBox < val5) ? IncStatRemaining(val5, valueInBox) : DecStatRemaining(val5, valueInBox);
		return;
	}
}

void CharacterEditState::CheckSearchBar() {
	sf::String textInBox = guiRef->get<tgui::EditBox>("SearchText")->getText();
	sf::String noText = "";

	(textInBox != noText) ? searchEntered = true : searchEntered = false;
}

void CharacterEditState::HideUI(UI ui) {
	switch (ui) {
	case CharacterList:
		guiRef->get("Search")->hide();
		guiRef->get("SearchText")->hide();
		guiRef->get("CharacterList")->hide();
		break;
	case CharacterInfo:
		guiRef->get("CharacterInfo")->hide();
		guiRef->get("CharacterName")->hide();
		guiRef->get("CharacterNameText")->hide();
		guiRef->get("ClassList")->hide();
		break;
	case ClassInfo:
		guiRef->get("ClassInfo")->hide();
		guiRef->get("ClassName")->hide();
		guiRef->get("ClassNameText")->hide();
		break;
	}
}

void CharacterEditState::IncStatRemaining(int& stat, int newValue) {
	statRemaining += stat - newValue;
	stat = newValue;
	guiRef->get<tgui::EditBox>("StatTotal")->setText(std::to_string(statRemaining));
}

bool CharacterEditState::DecStatRemaining(int& stat, int newValue) {
	statRemaining -= newValue - stat;
	
	if (statRemaining < 0) {
		statRemaining += newValue - stat;
		return false;
	}
	else {
		stat = newValue;
		guiRef->get<tgui::EditBox>("StatTotal")->setText(std::to_string(statRemaining));
		return true;
	}
}
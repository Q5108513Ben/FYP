#include "includeStates.hpp"
#include "Additional/spriteCreator.hpp"
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
	guiRef->add(characterInfo, "CharacterInfo");

	auto classInfo = ButtonCreator::Create("ClassInfo.png", Position(345, 90));
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
}

void CharacterEditState::CleanUp() {

}

void CharacterEditState::Pause() {
	guiRef->get("Search")->hide();
	guiRef->get("SearchText")->setOpacity(0);
	guiRef->get("CharacterList")->hide();
	guiRef->get("CharacterInfo")->setOpacity(0);
	guiRef->get("CharacterName")->hide();
	guiRef->get("CharacterNameText")->hide();
	
	guiRef->get("ClassList")->hide();
	guiRef->get("ClassInfo")->setOpacity(0);
	guiRef->get("ClassName")->hide();
	guiRef->get("ClassNameText")->hide();
}

void CharacterEditState::Resume() {
	if (!searchEntered) {
		guiRef->get("Search")->show();
	}

	guiRef->get("SearchText")->setOpacity(100);
	guiRef->get("CharacterList")->show();

	if (CheckListSelected("CharacterList")) {
		guiRef->get("CharacterNameText")->show();
		guiRef->get("CharacterInfo")->setOpacity(100);
		guiRef->get("ClassList")->show();

		if (nameChanged) {
			guiRef->get<tgui::EditBox>("CharacterNameText")->setText(nameEdited);
		}
		else {
			guiRef->get<tgui::EditBox>("CharacterNameText")->setText(nameSaved);
		}

		if (CheckListSelected("ClassList")) {
			guiRef->get("ClassInfo")->setOpacity(100);
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
		guiRef->get("CharacterNameText")->hide();
		guiRef->get("CharacterInfo")->setOpacity(0);
		guiRef->get("CharacterName")->hide();


		guiRef->get("ClassList")->hide();
		guiRef->get("ClassInfo")->setOpacity(0);
		return;
	}

	guiRef->get("CharacterNameText")->show();
	guiRef->get("CharacterInfo")->setOpacity(100);
	guiRef->get("CharacterName")->hide();
	guiRef->get("ClassList")->show();
	guiRef->get("ClassInfo")->setOpacity(0);
	guiRef->get("ClassName")->hide();

	auto selected = guiRef->get<tgui::ListBox>("CharacterList")->getSelectedItemId();
	unsigned int itemID = (unsigned int)*selected.getData();
	if (itemID == NULL) {
		return;
	}

	auto tempChar = DataManager::Instance()->GetCharacter(itemID);

	guiRef->get<tgui::EditBox>("CharacterNameText")->setText(tempChar.GetName());
	nameSaved = tempChar.GetName();

	guiRef->get<tgui::ListBox>("ClassList")->removeAllItems();

	for (auto c : tempChar.GetClasses()) {
		guiRef->get<tgui::ListBox>("ClassList")->addItem(c.className, c.classID);
	}
}

void CharacterEditState::LoadClass() {
	if (!CheckListSelected("ClassList")) {
		guiRef->get("ClassInfo")->setOpacity(0);
		guiRef->get("ClassName")->hide();
		return;
	}

	guiRef->get("ClassInfo")->setOpacity(100);
	guiRef->get("ClassName")->show();
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

void CharacterEditState::CheckSearchBar() {
	sf::String textInBox = guiRef->get<tgui::EditBox>("SearchText")->getText();
	sf::String noText = "";

	if (textInBox != noText) {
		searchEntered = true;
	}
	else {
		searchEntered = false;
	}
}
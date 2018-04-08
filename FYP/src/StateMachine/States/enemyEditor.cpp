#include "includeStates.hpp"
#include "Additional/spriteCreator.hpp"
#include "Managers/dataManager.hpp"

EnemyEditState EnemyEditState::enemystate;

void EnemyEditState::Initialise(sf::RenderWindow* window, tgui::Gui* gui) {
	windowRef = window;
	guiRef = gui;

	//-------Loading-XML-Data----------\\

	tinyxml2::XMLDocument enemyXML;
	enemyXML.LoadFile("data/Enemy.xml");
	DataManager::Instance()->RetrieveEnemyData(enemyXML.RootElement());

	//---------Static-Images-----------\\

	sprites.push_back(SpriteCreator::Create("ListBackground.png", Position(810, 330)));

	auto enemyInfo = ButtonCreator::Create("EnemyInfo.png", Position(24, 105));
	enemyInfo->setOpacity(100);
	enemyInfo->hide();
	guiRef->add(enemyInfo, "EnemyInfo");
	
	//--------Enemy-List-Search-------\\

	auto search = ButtonCreator::Create("ListSearch.png", Position(816, 333));
	search->setOpacity(100);
	guiRef->add(search, "EnemySearch");
	search->connect("Clicked", &EnemyEditState::ShowSearch, &enemystate, "EnemySearch", "EnemySearchText");

	auto searchText = tgui::EditBox::copy(guiRef->get<tgui::EditBox>("EditBox"));
	searchText->enable();
	searchText->setPosition(816, 333);
	searchText->setSize(144, 18);
	guiRef->add(searchText, "EnemySearchText");
	searchText->connect("Unfocused", &EnemyEditState::UnfocusSearch, &enemystate, "EnemySearch", "EnemySearchText");
	searchText->connect("Unfocused", &EnemyEditState::CheckSearchBar, &enemystate);

	//-----------Enemy-List------------\\

	auto enemyList = tgui::ListBox::copy(guiRef->get<tgui::ListBox>("ListBox"));
	enemyList->setPosition(821, 381);
	enemyList->setSize(165, 267);
	enemyList->show();
	enemyList->enable();
	guiRef->add(enemyList, "EnemyList");
	enemyList->connect("ItemSelected", &EnemyEditState::LoadEnemy, &enemystate);

	for (auto enemy : DataManager::Instance()->GetAllEnemies()) {
		enemyList->addItem(enemy.second.GetName(), enemy.first);
	}

	//-----------Enemy-Name-----------\\

	auto name = ButtonCreator::Create("CharacterName.png", Position(126, 105));
	name->setOpacity(100);
	name->hide();
	guiRef->add(name, "EnemyName");
	name->connect("Clicked", &EnemyEditState::ShowSearch, &enemystate, "EnemyName", "EnemyNameText");

	auto nameText = tgui::EditBox::copy(guiRef->get<tgui::EditBox>("EditBox"));
	nameText->enable();
	nameText->setPosition(129, 108);
	nameText->setSize(183, 21);
	guiRef->add(nameText, "EnemyNameText");
	nameText->connect("Unfocused", &EnemyEditState::UnfocusSearch, &enemystate, "EnemyName", "EnemyNameText");
	nameText->connect("Unfocused", &EnemyEditState::CheckNameChange, &enemystate);
}

void EnemyEditState::CleanUp() {

}

void EnemyEditState::Pause() {
	HideUI(EnemyList);
	HideUI(EnemyInfo);
}

void EnemyEditState::Resume() {
	(!searchEntered) ? guiRef->get("EnemySearch")->show() : guiRef->get("EnemySearchText")->show();
	guiRef->get("EnemyList")->show();

	if (CheckListSelected("EnemyList")) {
		guiRef->get("EnemyInfo")->show();
		guiRef->get("EnemyNameText")->show();

		(nameChanged) ? guiRef->get<tgui::EditBox>("EnemyNameText")->setText(nameEdited) :
						guiRef->get<tgui::EditBox>("EnemyNameText")->setText(nameSaved);
	}
}

void EnemyEditState::HandleEvent(StateMachine* machine, sf::Event event) {

}

void EnemyEditState::Update(StateMachine* machine) {

}

void EnemyEditState::Render(StateMachine* machine) {
	for (auto sprite : sprites) {
		sprite.scale(3, 3);
		windowRef->draw(sprite);
	}
}

void EnemyEditState::ShowSearch(sf::String imageName, sf::String searchName) {
	guiRef->get(imageName)->hide();
	guiRef->get(searchName)->show();
	guiRef->get(searchName)->focus();
}

void EnemyEditState::UnfocusSearch(sf::String imageName, sf::String searchName) {
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

void EnemyEditState::LoadEnemy() {
	if (!CheckListSelected("EnemyList")) {
		HideUI(EnemyInfo);
		return;
	}
	guiRef->get("EnemyInfo")->show();
	guiRef->get("EnemyName")->hide();
	guiRef->get("EnemyNameText")->show();

	auto selected = guiRef->get<tgui::ListBox>("EnemyList")->getSelectedItemId();
	unsigned int itemID = (unsigned int)*selected.getData();

	if (itemID == NULL) { return; }

	auto tempEnem = DataManager::Instance()->GetEnemy(itemID);

	nameSaved = tempEnem.GetName();
	guiRef->get<tgui::EditBox>("EnemyNameText")->setText(nameSaved);
}

bool EnemyEditState::CheckListSelected(sf::String listName) {
	if (guiRef->get<tgui::ListBox>(listName)->getSelectedItemIndex() == -1) {
		return false;
	}
	return true;
}

void EnemyEditState::CheckNameChange() {
	sf::String textInBox = guiRef->get<tgui::EditBox>("EnemyNameText")->getText();
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

void EnemyEditState::CheckSearchBar() {
	sf::String textInBox = guiRef->get<tgui::EditBox>("SearchText")->getText();
	sf::String noText = "";

	(textInBox != noText) ? searchEntered = true : searchEntered = false;
}

void EnemyEditState::HideUI(UI ui) {
	switch (ui) {
	case EnemyList:
		guiRef->get("EnemySearch")->hide();
		guiRef->get("EnemySearchText")->hide();
		guiRef->get("EnemyList")->hide();
		break;
	case EnemyInfo:
		guiRef->get("EnemyInfo")->hide();
		guiRef->get("EnemyName")->hide();
		guiRef->get("EnemyNameText")->hide();
	}
}
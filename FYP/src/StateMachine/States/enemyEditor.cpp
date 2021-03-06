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

	auto enemyStatInfo = ButtonCreator::Create("EnemyStatInfo.png", Position(345, 90));
	enemyStatInfo->setOpacity(100);
	enemyStatInfo->hide();
	guiRef->add(enemyStatInfo, "EnemyStatInfo");

	auto enemyAbilityInfo = ButtonCreator::Create("EnemyAbilityInfo.png", Position(345, 90));
	enemyAbilityInfo->setOpacity(100);
	enemyAbilityInfo->hide();
	guiRef->add(enemyAbilityInfo, "EnemyAbilityInfo");

	auto enemyAIInfo = ButtonCreator::Create("EnemyAIInfo.png", Position(345, 90));
	enemyAIInfo->setOpacity(100);
	enemyAIInfo->hide();
	guiRef->add(enemyAIInfo, "EnemyUIInfo");

	auto enemyDropInfo = ButtonCreator::Create("EnemyDropInfo.png", Position(345, 90));
	enemyDropInfo->setOpacity(100);
	enemyDropInfo->hide();
	guiRef->add(enemyDropInfo, "EnemyDropInfo");
	
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

	//--------------Tabs--------------\\

	auto statTab = tgui::Button::create();
	statTab->setPosition(245, 141);
	statTab->setSize(24, 24);
	statTab->setOpacity(0);
	statTab->hide();
	guiRef->add(statTab, "EnemyStatTab");
	statTab->connect("Clicked", &EnemyEditState::OpenTab, &enemystate, 2);

	auto abilityTab = tgui::Button::create();
	abilityTab->setPosition(245, 174);
	abilityTab->setSize(24, 24);
	abilityTab->setOpacity(0);
	abilityTab->hide();
	guiRef->add(abilityTab, "EnemyAbilityTab");
	abilityTab->connect("Clicked", &EnemyEditState::OpenTab, &enemystate, 3);

	auto aiTab = tgui::Button::create();
	aiTab->setPosition(245, 207);
	aiTab->setSize(24, 24);
	aiTab->setOpacity(0);
	aiTab->hide();
	guiRef->add(aiTab, "EnemyAITab");
	aiTab->connect("Clicked", &EnemyEditState::OpenTab, &enemystate, 4);

	auto dropTab = tgui::Button::create();
	dropTab->setPosition(245, 240);
	dropTab->setSize(24, 24);
	dropTab->setOpacity(0);
	dropTab->hide();
	guiRef->add(dropTab, "EnemyDropTab");
	dropTab->connect("Clicked", &EnemyEditState::OpenTab, &enemystate, 5);
}

void EnemyEditState::CleanUp() {

}

void EnemyEditState::Pause() {
	HideUI(EnemyList);
	HideUI(EnemyInfo);
	if (isTabSelected) {
		switch (tabSelected) {
		case StatInfo:
			HideUI(StatInfo);
			break;
		case AbilityInfo:
			HideUI(AbilityInfo);
			break;
		case AIInfo:
			HideUI(AIInfo);
			break;
		case DropInfo:
			HideUI(DropInfo);
			break;
		}
	}
}

void EnemyEditState::Resume() {
	(!searchEntered) ? guiRef->get("EnemySearch")->show() : guiRef->get("EnemySearchText")->show();
	guiRef->get("EnemyList")->show();

	if (CheckListSelected("EnemyList")) {
		guiRef->get("EnemyInfo")->show();
		guiRef->get("EnemyNameText")->show();
		guiRef->get("EnemyStatTab")->show();
		guiRef->get("EnemyAbilityTab")->show();
		guiRef->get("EnemyAITab")->show();
		guiRef->get("EnemyDropTab")->show();

		(nameChanged) ? guiRef->get<tgui::EditBox>("EnemyNameText")->setText(nameEdited) :
						guiRef->get<tgui::EditBox>("EnemyNameText")->setText(nameSaved);

		if (isTabSelected) {
			switch (tabSelected) {
			case 2:
				guiRef->get("EnemyStatInfo")->show();
				break;
			case 3:
				guiRef->get("EnemyAbilityInfo")->show();
				break;
			case 4:
				guiRef->get("EnemyUIInfo")->show();
				break;
			case 5:
				guiRef->get("EnemyDropInfo")->show();
				break;
			}
		}
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
	guiRef->get("EnemyStatTab")->show();
	guiRef->get("EnemyAbilityTab")->show();
	guiRef->get("EnemyAITab")->show();
	guiRef->get("EnemyDropTab")->show();

	auto selected = guiRef->get<tgui::ListBox>("EnemyList")->getSelectedItemId();
	unsigned int itemID = (unsigned int)*selected.getData();

	if (itemID == NULL) { return; }

	auto tempEnem = DataManager::Instance()->GetEnemy(itemID);

	nameSaved = tempEnem.GetName();
	guiRef->get<tgui::EditBox>("EnemyNameText")->setText(nameSaved);

	if (isTabSelected) {
		isTabSelected = false;
		switch (tabSelected) {
		case StatInfo:
			HideUI(StatInfo);
			break;
		case AbilityInfo:
			HideUI(AbilityInfo);
			break;
		case AIInfo:
			HideUI(AIInfo);
			break;
		case DropInfo:
			HideUI(DropInfo);
			break;
		}
	}
}

void EnemyEditState::OpenTab(unsigned int tabID) {
	switch (tabSelected) {
	case 0:
		break;
	case 2:
		HideUI(StatInfo);
		break;
	case 3:
		HideUI(AbilityInfo);
		break;
	case 4:
		HideUI(AIInfo);
		break;
	case 5:
		HideUI(DropInfo);
		break;
	}
	
	switch (tabID) {
	case 2:
		tabSelected = 2;
		guiRef->get("EnemyStatInfo")->show();
		break;
	case 3:
		tabSelected = 3;
		guiRef->get("EnemyAbilityInfo")->show();
		break;
	case 4:
		tabSelected = 4;
		guiRef->get("EnemyUIInfo")->show();
		break;
	case 5:
		tabSelected = 5;
		guiRef->get("EnemyDropInfo")->show();
		break;
	}
	isTabSelected = true;
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
	sf::String textInBox = guiRef->get<tgui::EditBox>("EnemySearchText")->getText();
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
		guiRef->get("EnemyStatTab")->hide();
		guiRef->get("EnemyAbilityTab")->hide();
		guiRef->get("EnemyAITab")->hide();
		guiRef->get("EnemyDropTab")->hide();
		break;
	case StatInfo:
		guiRef->get("EnemyStatInfo")->hide();
		break;
	case AbilityInfo:
		guiRef->get("EnemyAbilityInfo")->hide();
		break;
	case AIInfo:
		guiRef->get("EnemyUIInfo")->hide();
		break;
	case DropInfo:
		guiRef->get("EnemyDropInfo")->hide();
		break;
	}
}
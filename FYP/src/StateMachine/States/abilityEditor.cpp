#include "includeStates.hpp"
#include "Additional/spriteCreator.hpp"
#include "Managers/dataManager.hpp"

AbilityEditState AbilityEditState::abilitystate;

void AbilityEditState::Initialise(sf::RenderWindow* window, tgui::Gui* gui) {
	windowRef = window;
	guiRef = gui;

	//-------Loading-XML-Data----------\\

	tinyxml2::XMLDocument abilityXML;
	abilityXML.LoadFile("data/Ability.xml");
	DataManager::Instance()->RetrieveAbilityData(abilityXML.RootElement());

	//---------Static-Images-----------\\

	sprites.push_back(SpriteCreator::Create("ListBackground.png", Position(810, 330)));

	auto abilityInfo = ButtonCreator::Create("AbilityInfo.png", Position(24, 105));
	abilityInfo->setOpacity(100);
	abilityInfo->hide();
	guiRef->add(abilityInfo, "AbilityInfo");

	auto abilityGeneralInfo = ButtonCreator::Create("AbilityGeneralInfo.png", Position(345, 90));
	abilityGeneralInfo->setOpacity(100);
	abilityGeneralInfo->hide();
	guiRef->add(abilityGeneralInfo, "AbilityGeneralInfo");

	//-------Ability-List-Search-------\\

	auto search = ButtonCreator::Create("ListSearch.png", Position(816, 333));
	search->setOpacity(100);
	guiRef->add(search, "AbilitySearch");
	search->connect("Clicked", &AbilityEditState::ShowSearch, &abilitystate, "AbilitySearch", "AbilitySearchText");

	auto searchText = tgui::EditBox::copy(guiRef->get<tgui::EditBox>("EditBox"));
	searchText->enable();
	searchText->setPosition(816, 333);
	searchText->setSize(144, 18);
	guiRef->add(searchText, "AbilitySearchText");
	searchText->connect("Unfocused", &AbilityEditState::UnfocusSearch, &abilitystate, "AbilitySearch", "AbilitySearchText");
	searchText->connect("Unfocused", &AbilityEditState::CheckSearchBar, &abilitystate);

	//----------Ability-List------------\\
	
	auto abilityList = tgui::ListBox::copy(guiRef->get<tgui::ListBox>("ListBox"));
	abilityList->setPosition(821, 381);
	abilityList->setSize(165, 267);
	abilityList->show();
	abilityList->enable();
	guiRef->add(abilityList, "AbilityList");
	abilityList->connect("ItemSelected", &AbilityEditState::LoadAbility, &abilitystate);

	for (auto ability : DataManager::Instance()->GetAllAbilities()) {
		abilityList->addItem(ability.second.GetName(), ability.first);
	}

	//-----------Ability-Name----------\\

	auto name = ButtonCreator::Create("CharacterName.png", Position(126, 105));
	name->setOpacity(100);
	name->hide();
	guiRef->add(name, "AbilityName");
	name->connect("Clicked", &AbilityEditState::ShowSearch, &abilitystate, "AbilityName", "AbilityNameText");

	auto nameText = tgui::EditBox::copy(guiRef->get<tgui::EditBox>("EditBox"));
	nameText->enable();
	nameText->setPosition(129, 108);
	nameText->setSize(183, 21);
	guiRef->add(nameText, "AbilityNameText");
	nameText->connect("Unfocused", &AbilityEditState::UnfocusSearch, &abilitystate, "AbilityName", "AbilityNameText");
	nameText->connect("Unfocused", &AbilityEditState::CheckNameChange, &abilitystate);

	//-----------Effect-List----------\\

	auto effectList = tgui::ListBox::copy(guiRef->get<tgui::ListBox>("ListBox"));
	effectList->setPosition(36, 207);
	effectList->setSize(165, 267);
	effectList->enable();
	guiRef->add(effectList, "EffectList");
	effectList->connect("ItemSelected", &AbilityEditState::LoadEffect, &abilitystate);

	//-------------Tag-List------------\\

	auto tagList = tgui::ListBox::copy(guiRef->get<tgui::ListBox>("ListBox"));
	tagList->setPosition(36, 441);
	tagList->setSize(165, 267);
	guiRef->add(tagList, "TagList");

	//-----------General-Tab-----------\\

	auto genTab = tgui::Button::create();
	genTab->setPosition(245, 141);
	genTab->setSize(24, 24);
	genTab->setOpacity(0);
	genTab->hide();
	guiRef->add(genTab, "GeneralTab");
	genTab->connect("Clicked", &AbilityEditState::OpenTab, &abilitystate);

	//--------General-Text-Fields-------\\

	unsigned int offset = 0;

	for (int i = 0; i < 3; i++) {
		auto textField = tgui::EditBox::copy(guiRef->get<tgui::EditBox>("EditBox"));
		textField->enable();
		textField->setPosition(627, 144 + offset);
		textField->setSize(90, 21);
		textField->setAlignment(tgui::EditBox::Alignment::Right);
		textField->setText("0");
		textField->setMaximumCharacters(3);
		guiRef->add(textField, "AbilityValue" + i);

		offset += 24;
	}

	//----------Drop-Down-Menus--------\\

	auto targetDrop = tgui::ComboBox::copy(guiRef->get<tgui::ComboBox>("ComboBox"));
	targetDrop->enable();
	targetDrop->setPosition(555, 105);
	targetDrop->setSize(182, 21);
	guiRef->add(targetDrop, "TargetDrop");
	targetDrop->addItem("Single", "0");
	targetDrop->addItem("AoE", "1");
	targetDrop->addItem("Row", "2");
	targetDrop->addItem("Column", "3");
}

void AbilityEditState::CleanUp() {

}

void AbilityEditState::Pause() {
	HideUI(AbilityList);
	HideUI(AbilityInfo);
	HideUI(GeneralInfo);
}

void AbilityEditState::Resume() {
	(!searchEntered) ? guiRef->get("AbilitySearch")->show() : guiRef->get("AbilitySearchText")->show();
	guiRef->get("AbilityList")->show();

	if (CheckListSelected("AbilityList")) {
		guiRef->get("AbilityInfo")->show();
		guiRef->get("AbilityNameText")->show();
		guiRef->get("EffectList")->show();
		guiRef->get("TagList")->show();
		guiRef->get("GeneralTab")->show();
		
		(nameChanged) ? guiRef->get<tgui::EditBox>("AbilityNameText")->setText(nameEdited) :
						guiRef->get<tgui::EditBox>("AbilityNameText")->setText(nameSaved);

		if (isTabSelected) {
			guiRef->get("AbilityGeneralInfo")->show();
			guiRef->get("TargetDrop")->show();
			for (int i = 0; i < 3; i++) { guiRef->get("AbilityValue" + i)->show(); }
		}
	}
}

void AbilityEditState::HandleEvent(StateMachine* machine, sf::Event event) {

}

void AbilityEditState::Update(StateMachine* machine) {

}

void AbilityEditState::Render(StateMachine* machine) {
	for (auto sprite : sprites) {
		sprite.scale(3, 3);
		windowRef->draw(sprite);
	}
}

void AbilityEditState::ShowSearch(sf::String imageName, sf::String searchName) {
	guiRef->get(imageName)->hide();
	guiRef->get(searchName)->show();
	guiRef->get(searchName)->focus();
}

void AbilityEditState::UnfocusSearch(sf::String imageName, sf::String searchName) {
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

void AbilityEditState::LoadAbility() {
	if (!CheckListSelected("AbilityList")) {
		HideUI(AbilityInfo);
		HideUI(GeneralInfo);
		return;
	}
	
	guiRef->get("AbilityInfo")->show();
	guiRef->get("AbilityName")->hide();
	guiRef->get("AbilityNameText")->show();
	guiRef->get("EffectList")->show();
	guiRef->get("TagList")->show();
	guiRef->get("GeneralTab")->show();

	if (isTabSelected) {
		HideUI(GeneralInfo);
		isTabSelected = false;
	}

	auto selected = guiRef->get<tgui::ListBox>("AbilityList")->getSelectedItemId();
	unsigned int itemID = (unsigned int)*selected.getData();

	if (itemID == NULL) { return; }

	auto tempAbil = DataManager::Instance()->GetAbility(itemID);

	nameSaved = tempAbil.GetName();
	guiRef->get<tgui::EditBox>("AbilityNameText")->setText(nameSaved);

	guiRef->get<tgui::ListBox>("EffectList")->removeAllItems();
	guiRef->get<tgui::ListBox>("TagList")->removeAllItems();

	for (auto e : tempAbil.GetEffects()) {
		guiRef->get<tgui::ListBox>("EffectList")->addItem(e.second.effectName, e.first);
	}
	for (auto t : tempAbil.GetTags()) {
		guiRef->get<tgui::ListBox>("TagList")->addItem(t.second.tagName, t.first);
	}
}

void AbilityEditState::LoadEffect() {

}

void AbilityEditState::OpenTab() {
	isTabSelected = true;
	guiRef->get("AbilityGeneralInfo")->show();
	guiRef->get("TargetDrop")->show();
	for (int i = 0; i < 3; i++) { guiRef->get("AbilityValue" + i)->show(); }
}

bool AbilityEditState::CheckListSelected(sf::String listName) {
	if (guiRef->get<tgui::ListBox>(listName)->getSelectedItemIndex() == -1) {
		return false;
	}
	return true;
}

void AbilityEditState::CheckNameChange() {
	sf::String textInBox = guiRef->get<tgui::EditBox>("AbilityNameText")->getText();
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

void AbilityEditState::CheckSearchBar() {
	sf::String textInBox = guiRef->get<tgui::EditBox>("AbilitySearchText")->getText();
	sf::String noText = "";

	(textInBox != noText) ? searchEntered = true : searchEntered = false;
}

void AbilityEditState::HideUI(UI ui) {
	switch (ui) {
	case AbilityList:
		guiRef->get("AbilitySearch")->hide();
		guiRef->get("AbilitySearchText")->hide();
		guiRef->get("AbilityList")->hide();
		break;
	case AbilityInfo:
		guiRef->get("AbilityInfo")->hide();
		guiRef->get("AbilityName")->hide();
		guiRef->get("AbilityNameText")->hide();
		guiRef->get("EffectList")->hide();
		guiRef->get("TagList")->hide();
		guiRef->get("GeneralTab")->hide();
		break;
	case GeneralInfo:
		guiRef->get("AbilityGeneralInfo")->hide();
		guiRef->get("TargetDrop")->hide();
		for (int i = 0; i < 3; i++) { guiRef->get("AbilityValue" + i)->hide(); }
		break;
	}
}
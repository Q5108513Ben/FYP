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

	//--------Enemy-List-Search-------\\

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

}

void AbilityEditState::CleanUp() {

}

void AbilityEditState::Pause() {
	HideUI(AbilityList);
}

void AbilityEditState::Resume() {
	(!searchEntered) ? guiRef->get("AbilitySearch")->show() : guiRef->get("AbilitySearchText")->show();
	guiRef->get("AbilityList")->show();
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
	}
}
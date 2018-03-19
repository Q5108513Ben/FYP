#include "includeStates.hpp"
#include "Additional\spriteCreator.hpp"

CharacterEditState CharacterEditState::characterstate;

void CharacterEditState::Initialise(sf::RenderWindow* window, tgui::Gui* gui) {
	windowRef = window;
	guiRef = gui;

	sprites.push_back(SpriteCreator::Create("ListBackground.png", Position(810,330)));



	auto search = ButtonCreator::Create("ListSearch.png", Position(816, 333));
	search->setOpacity(100);
	guiRef->add(search, "Search");
	search->connect("Clicked", &CharacterEditState::ShowSearch, &characterstate);

	auto searchText = tgui::EditBox::create();
	searchText->setPosition(816, 333);
	searchText->setSize(144, 18);
	sf::Font font;
	font.loadFromFile("UnbeknownstStnd.ttf");
	searchText->getRenderer()->setBackgroundColor(sf::Color(0, 0, 0, 0));
	searchText->getRenderer()->setBorders(tgui::Borders(0));
	searchText->getRenderer()->setCaretColor(sf::Color(130,130,130,255));
	searchText->getRenderer()->setTextColor(sf::Color(130,130,130,255));
	searchText->getRenderer()->setSelectedTextColor(sf::Color(243, 243, 243, 255));
	searchText->getRenderer()->setSelectedTextBackgroundColor(sf::Color(51,51,51,255));
	searchText->setFont(font);
	searchText->setTextSize(16);
	searchText->setCaretWidth(2);
	searchText->hide();
	searchText->setOpacity(0);
	guiRef->add(searchText, "SearchText");
	searchText->connect("Unfocused", &CharacterEditState::UnfocusSearch, &characterstate);

	
}

void CharacterEditState::CleanUp() {

}

void CharacterEditState::Pause() {
	guiRef->get("Search")->hide();
	guiRef->get("SearchText")->hide();
}

void CharacterEditState::Resume() {
	guiRef->get("Search")->show();
	guiRef->get("SearchText")->show();
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

void CharacterEditState::ShowSearch() {
	guiRef->get("Search")->setOpacity(0);
	guiRef->get("SearchText")->show();
	guiRef->get("SearchText")->setOpacity(100);
	guiRef->get("SearchText")->focus();
}

void CharacterEditState::UnfocusSearch() {
	sf::String textInBox = guiRef->get<tgui::EditBox>("SearchText")->getText();
	sf::String noText = "";

	if (textInBox != noText) {
		return;
	}
	else {
		guiRef->get("SearchText")->setOpacity(0);
		guiRef->get("SearchText")->hide();
		guiRef->get("Search")->setOpacity(100);
		guiRef->get("Search")->showWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(0.5));
	}
}
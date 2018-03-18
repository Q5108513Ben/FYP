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

	auto searchText = tgui::EditBox::create();
	searchText->setPosition(816, 333);
	searchText->setSize(144, 18);
	sf::Font font;
	font.loadFromFile("UnbeknownstStnd.ttf");
	searchText->setFont(font);
	searchText->setTextSize(16);
	searchText->setCaretWidth(2);
	guiRef->add(searchText, "SearchText");
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
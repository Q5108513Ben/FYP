#include "includeStates.hpp"
#include "Additional\spriteCreator.hpp"

TitleScreenState TitleScreenState::titlestate;

void TitleScreenState::Initialise(sf::RenderWindow* window, tgui::Gui* gui) {
	windowRef = window;
	guiRef = gui;

	sprites.push_back(SpriteCreator::Create("IntroMessage.png", Position(126,228)));

	auto helpArrow = ButtonCreator::Create("HelpArrow.png", Position(906, 48 ));
	guiRef->add(helpArrow, "HelpArrow");

	auto helpButton = tgui::Picture::create();
	helpButton->setSize(72, 21);
	helpButton->setPosition(285, 297);
	guiRef->add(helpButton, "HelpButton");
	helpButton->connect("MouseEntered", [&]() {guiRef->get("HelpArrow")->setOpacity(100); });
	helpButton->connect("MouseLeft", [&]() {guiRef->get("HelpArrow")->setOpacity(0); });
}

void TitleScreenState::CleanUp() {

}

void TitleScreenState::Pause() {
	guiRef->get("HelpButton")->hide();
}

void TitleScreenState::Resume() {

}

void TitleScreenState::HandleEvent(StateMachine* machine, sf::Event event) {

}

void TitleScreenState::Update(StateMachine* machine) {
	
}

void TitleScreenState::Render(StateMachine* machine) {
	for (auto sprite : sprites) {
		sprite.scale(3, 3);
		windowRef->draw(sprite);
	}
}
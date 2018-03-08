#include "Managers/UIManager.hpp"
#include "Additional/spriteCreator.hpp"

UIManager UIManager::ui;

void UIManager::LoadBaseUI(sf::RenderWindow* window, StateMachine* machine, tgui::Gui* gui) {
	windowPtr = window;
	guiPtr = gui;
	
	sprites.push_back(SpriteCreator::Create("Background.png"));
	
	auto toolbar = tgui::Picture::create();
	toolbar->setSize(1020, 40);
	guiPtr->add(toolbar, "Toolbar");
	toolbar->connect("MousePressed", &UIManager::WindowDragOn, &ui);
	toolbar->connect("MouseReleased", [&]() {grabbedWindow = false; });
	
	auto exit = ButtonCreator::Create("ExitHover.png", Position(987,12));
	exit->setOpacity(0);
	guiPtr->add(exit, "Exit");
	exit->connect("Clicked", &UIManager::QuitProgram, &ui, machine);
	exit->connect("MouseEntered", &UIManager::ShowButton, &ui, "Exit");
	exit->connect("MouseLeft", &UIManager::HideButton, &ui, "Exit");
}

void UIManager::Render() {
	if (grabbedWindow) {
		windowPtr->setPosition(sf::Mouse::getPosition() + grabbedOffset);
	}
	
	for (auto sprite : sprites) {
		sprite.scale(3, 3);
		windowPtr->draw(sprite);
	}
}

void UIManager::WindowDragOn() {
	grabbedOffset = windowPtr->getPosition() - sf::Mouse::getPosition();
	grabbedWindow = true;
}

void UIManager::ShowButton(std::string buttonName) {
	guiPtr->get(buttonName)->setOpacity(100);
}

void UIManager::HideButton(std::string buttonName) {
	guiPtr->get(buttonName)->setOpacity(0);
}

void UIManager::QuitProgram(StateMachine* machine) {
	machine->Quit();
}
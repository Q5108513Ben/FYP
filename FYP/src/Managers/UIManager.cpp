#include "Managers/UIManager.hpp"
#include "Additional/spriteCreator.hpp"

UIManager UIManager::ui;

void UIManager::LoadBaseUI(sf::RenderWindow* window, StateMachine* machine, tgui::Gui* gui) {
	windowPtr = window;
	guiPtr = gui;
	
	sprites.push_back(SpriteCreator::Create("Background.png"));
	
	auto toolbar = tgui::Picture::create();
	toolbar->setSize(1020, 42);
	guiPtr->add(toolbar, "Toolbar");
	toolbar->connect("MousePressed", &UIManager::WindowDragOn, &ui);
	toolbar->connect("MouseReleased", [&]() {grabbedWindow = false; });
	
	auto exit = ButtonCreator::Create("ExitHover.png", Position(987, 12));
	guiPtr->add(exit, "Exit");
	exit->connect("Clicked", &UIManager::QuitProgram, &ui, machine);
	exit->connect("MouseEntered", &UIManager::ShowButton, &ui, "Exit");
	exit->connect("MouseLeft", &UIManager::HideButton, &ui, "Exit");

	auto options = ButtonCreator::Create("OptionsHover.png", Position(957, 12));
	guiPtr->add(options, "Options");
	options->connect("MouseEntered", &UIManager::ShowButton, &ui, "Options");
	options->connect("MouseLeft", &UIManager::HideButton, &ui, "Options");

	auto help = ButtonCreator::Create("HelpHover.png", Position(930, 12));
	guiPtr->add(help, "Help");
	help->connect("MouseEntered", &UIManager::ShowButton, &ui, "Help");
	help->connect("MouseLeft", &UIManager::HideButton, &ui, "Help");

	auto play = ButtonCreator::Create("PlayHover.png", Position(21, 15));
	guiPtr->add(play, "Play");
	play->connect("MouseEntered", &UIManager::ShowButton, &ui, "Play");
	play->connect("MouseLeft", &UIManager::HideButton, &ui, "Play");

	auto pause = ButtonCreator::Create("PauseHover.png", Position(45, 15));
	guiPtr->add(pause, "Pause");
	pause->connect("MouseEntered", &UIManager::ShowButton, &ui, "Pause");
	pause->connect("MouseLeft", &UIManager::HideButton, &ui, "Pause");

	auto playerSheet = ButtonCreator::Create("PlayerSheetHover.png", Position(81,0));
	guiPtr->add(playerSheet, "PlayerSheet");
	playerSheet->connect("Clicked", &UIManager::ActivateTab, &ui, 0);
	playerSheet->connect("MouseEntered", &UIManager::ShowButton, &ui, "PlayerSheet");
	playerSheet->connect("MouseLeft", &UIManager::HideTab, &ui, 0);

	auto enemySheet = ButtonCreator::Create("EnemySheetHover.png", Position(297, 0));
	guiPtr->add(enemySheet, "EnemySheet");
	enemySheet->connect("Clicked", &UIManager::ActivateTab, &ui, 1);
	enemySheet->connect("MouseEntered", &UIManager::ShowButton, &ui, "EnemySheet");
	enemySheet->connect("MouseLeft", &UIManager::HideTab, &ui, 1);

	auto abilityList = ButtonCreator::Create("AbilityListHover.png", Position(513, 0));
	guiPtr->add(abilityList, "AbilityList");
	abilityList->connect("Clicked", &UIManager::ActivateTab, &ui, 2);
	abilityList->connect("MouseEntered", &UIManager::ShowButton, &ui, "AbilityList");
	abilityList->connect("MouseLeft", &UIManager::HideTab, &ui, 2);

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

void UIManager::ActivateTab(unsigned int tabID) {
	switch (tabID) {
	case 0:
		if (!playerTabActive) {
			if (enemyTabActive) {
				enemyTabActive = false;
				guiPtr->get("EnemySheet")->setOpacity(0);
			}
			else if (abilityTabActive) {
				abilityTabActive = false;
				guiPtr->get("AbilityList")->setOpacity(0);
			}
			playerTabActive = true;
		}
		break;
	case 1:
		if (!enemyTabActive) {
			if (playerTabActive) {
				playerTabActive = false;
				guiPtr->get("PlayerSheet")->setOpacity(0);
			}
			else if (abilityTabActive) {
				abilityTabActive = false;
				guiPtr->get("AbilityList")->setOpacity(0);
			}
			enemyTabActive = true;
		}
		break;
	case 2:
		if (!abilityTabActive) {
			if (playerTabActive) {
				playerTabActive = false;
				guiPtr->get("PlayerSheet")->setOpacity(0);
			}
			else if (enemyTabActive) {
				enemyTabActive = false;
				guiPtr->get("EnemySheet")->setOpacity(0);
			}
			abilityTabActive = true;
		}
		break;
	}
}

void UIManager::HideTab(unsigned int tabID) {
	switch (tabID) {
	case 0:
		if (!playerTabActive) {
			guiPtr->get("PlayerSheet")->setOpacity(0);
		}
		break;
	case 1:
		if (!enemyTabActive) {
			guiPtr->get("EnemySheet")->setOpacity(0);
		}
		break;
	case 2:
		if (!abilityTabActive) {
			guiPtr->get("AbilityList")->setOpacity(0);
		}
		break;
	}
}

void UIManager::QuitProgram(StateMachine* machine) {
	machine->Quit();
}
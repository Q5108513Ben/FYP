#include "Managers/UIManager.hpp"
#include "Additional/spriteCreator.hpp"
#include "includeStates.hpp"

UIManager UIManager::ui;

UIManager::UIManager() {
	//Define appearance of widgets
	sf::Font stndFont;
	stndFont.loadFromFile("UnbeknownstStnd.ttf");
	//EditBox
	editBox = tgui::EditBox::create();
	editBox->getRenderer()->setBackgroundColor(sf::Color(0, 0, 0, 0));
	editBox->getRenderer()->setCaretColor(sf::Color(130, 130, 130, 255));
	editBox->getRenderer()->setTextColor(sf::Color(130, 130, 130, 255));
	editBox->getRenderer()->setBorders(tgui::Borders(0));
	editBox->getRenderer()->setSelectedTextColor(sf::Color(243, 243, 243, 255));
	editBox->getRenderer()->setSelectedTextBackgroundColor(sf::Color(51, 51, 51, 255));

	editBox->setCaretWidth(2);
	editBox->setFont(stndFont);
	editBox->setTextSize(16);
	
	editBox->setOpacity(0);
	editBox->hide();
	editBox->disable();
	//ListBox
	listBox = tgui::ListBox::create();
	listBox->getRenderer()->setBackgroundColor(sf::Color(0, 0, 0, 0));
	listBox->getRenderer()->setTextColor(sf::Color(130, 130, 130, 255));
	listBox->getRenderer()->setBorders(tgui::Borders(0));
	listBox->getRenderer()->setSelectedTextColor(sf::Color(243, 243, 243, 255));
	listBox->getRenderer()->setSelectedBackgroundColor(sf::Color(51, 51, 51, 255));
	listBox->getRenderer()->setHoverBackgroundColor(sf::Color(0, 0, 0, 0));

	listBox->getScrollbar()->setOpacity(0);
	listBox->getScrollbar()->disable();

	listBox->setAutoScroll(false);
	listBox->setFont(stndFont);
	listBox->setTextSize(16);
	listBox->hide();
	listBox->disable();

}

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
	help->connect("Clicked", &UIManager::ToggleButton, &ui, 2);
	help->connect("MouseEntered", &UIManager::ShowButton, &ui, "Help");
	help->connect("MouseLeft", &UIManager::HideButtonToggle, &ui, 2);

	auto play = ButtonCreator::Create("PlayHover.png", Position(21, 15));
	guiPtr->add(play, "Play");
	play->connect("Clicked", &UIManager::ToggleButton, &ui, 0);
	play->connect("MouseEntered", &UIManager::ShowButton, &ui, "Play");
	play->connect("MouseLeft", &UIManager::HideButtonToggle, &ui, 0);

	auto pause = ButtonCreator::Create("PauseHover.png", Position(45, 15));
	pause->setOpacity(100);
	guiPtr->add(pause, "Pause");
	pause->connect("Clicked", &UIManager::ToggleButton, &ui, 1);
	pause->connect("MouseEntered", &UIManager::ShowButton, &ui, "Pause");
	pause->connect("MouseLeft", &UIManager::HideButtonToggle, &ui, 1);

	auto playerSheet = ButtonCreator::Create("PlayerSheetHover.png", Position(81,0));
	guiPtr->add(playerSheet, "PlayerSheet");
	playerSheet->connect("Clicked", &UIManager::ActivateTab, &ui, 0, machine);
	playerSheet->connect("MouseEntered", &UIManager::ShowButton, &ui, "PlayerSheet");
	playerSheet->connect("MouseLeft", &UIManager::HideTab, &ui, 0);

	auto enemySheet = ButtonCreator::Create("EnemySheetHover.png", Position(297, 0));
	guiPtr->add(enemySheet, "EnemySheet");
	enemySheet->connect("Clicked", &UIManager::ActivateTab, &ui, 1, machine);
	enemySheet->connect("MouseEntered", &UIManager::ShowButton, &ui, "EnemySheet");
	enemySheet->connect("MouseLeft", &UIManager::HideTab, &ui, 1);

	auto abilityList = ButtonCreator::Create("AbilityListHover.png", Position(513, 0));
	guiPtr->add(abilityList, "AbilityList");
	abilityList->connect("Clicked", &UIManager::ActivateTab, &ui, 2, machine);
	abilityList->connect("MouseEntered", &UIManager::ShowButton, &ui, "AbilityList");
	abilityList->connect("MouseLeft", &UIManager::HideTab, &ui, 2);

	guiPtr->add(editBox, "EditBox");
	guiPtr->add(listBox, "ListBox");
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

void UIManager::HideButtonToggle(unsigned int buttonID) {
	switch (buttonID) {
	case 0:
		if (!playButtonActive) {
			guiPtr->get("Play")->setOpacity(0);
		}
		break;
	case 1:
		if (!pauseButtonActive) {
			guiPtr->get("Pause")->setOpacity(0);
		}
		break;
	case 2:
		if (!helpButtonActive) {
			guiPtr->get("Help")->setOpacity(0);
		}
		break;
	}
}

void UIManager::ToggleButton(unsigned int buttonID) {
	switch (buttonID) {
	case 0:
		if (!playButtonActive) {
			playButtonActive = true;
			pauseButtonActive = false;
			guiPtr->get("Play")->setOpacity(100);
			guiPtr->get("Pause")->setOpacity(0);
		}
		break;
	case 1:
		if (!pauseButtonActive) {
			pauseButtonActive = true;
			playButtonActive = false;
			guiPtr->get("Pause")->setOpacity(100);
			guiPtr->get("Play")->setOpacity(0);
		}
		break;
	case 2:
		if (helpButtonActive) {
			helpButtonActive = false;
			guiPtr->get("Help")->setOpacity(0);
		}
		else {
			helpButtonActive = true;
			guiPtr->get("Help")->setOpacity(100);
		}
		break;
	}
}

void UIManager::ActivateTab(unsigned int tabID, StateMachine* machine) {
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
			machine->PushState(CharacterEditState::Instance());
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
			machine->PushState(EnemyEditState::Instance());
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
			machine->PushState(AbilityEditState::Instance());
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
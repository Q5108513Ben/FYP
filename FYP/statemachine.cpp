#include "statemachine.hpp"
#include "virtualstate.hpp"
#include "SpriteCreator.hpp"

#include <iostream>

StateMachine::StateMachine() : window(sf::VideoMode(1020, 675), "Final Year Project - Ben Holdsworth | Q5108513", sf::Style::None),
							   gui(window) {
	windowPtr = &window;
	guiPtr = &gui;
	this->Initialise();
}

void StateMachine::Initialise() {
	isRunning = true;

	sprites.push_back(SpriteCreator::Create("Background.png"));

	auto button = tgui::Picture::create();
	button->setTexture("Images/ExitHover.png", true);
	button->scale(3, 3);
	gui.add(button);
	button->connect("clicked", [&]() {window.close(); });
}

void StateMachine::CleanUp() {
	while (!states.empty()) {
		states.back()->CleanUp();
		states.pop_back();
	}

	currentState = nullptr;
	previousState = nullptr;
}

void StateMachine::PushState(State* state) {
	
	if (CheckStates(state)) {
		return;
	}
	
	if (!states.empty()) {
		currentState->Pause();
		previousState = currentState;
	}

	states.push_back(state);
	states.back()->Initialise(windowPtr);
	currentState = state;
}

void StateMachine::SwitchState(State* state) {
	
	if (!CheckStates(state)) {
		return;
	}

	if (state != currentState) {
		currentState->Pause();
		previousState = currentState;

		state->Resume();
		currentState = state;
	}
}

void StateMachine::PopState() {
	if (!states.empty()) {
		states.back()->CleanUp();
		states.pop_back();
		State* tempCurrState = currentState;
		currentState = nullptr;

		if (!states.empty()) {
			currentState = previousState;
			previousState = tempCurrState;
			previousState->Resume();
		}
		else {
			isRunning = false;
		}
	}
}

void StateMachine::HandleEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
			std::cout << event.type << std::endl;
			case sf::Event::MouseButtonPressed:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (sf::Mouse::getPosition().y < window.getPosition().y + 40) {
						grabbedOffset = window.getPosition() - sf::Mouse::getPosition();
						grabbedWindow = true;
					}
				}
				break;

			case sf::Event::MouseButtonReleased:
				grabbedWindow = false;
				break;
		}

		gui.handleEvent(event);
	}
	
	currentState->HandleEvents(this);
}

void StateMachine::Update() {
	currentState->Update(this);
}

void StateMachine::Render() {
	window.clear();

	if (grabbedWindow) {
		window.setPosition(sf::Mouse::getPosition() + grabbedOffset);
	}

	for (auto sprite : sprites) {
		sprite.scale(3, 3);
		window.draw(sprite);
	}

	currentState->Render(this);
	gui.draw();
	window.display();
}

void StateMachine::Quit() {
	isRunning = false;
	windowPtr->close();
}

bool StateMachine::CheckStates(State* state) {
	int counter{ 0 };

	for (auto statePtr : states) {
		if (state == statePtr) {
			return true;
		}
		else {
			counter++;
			if (counter == states.size()) {
				return false;
			}
		}
	}

	return false;
}
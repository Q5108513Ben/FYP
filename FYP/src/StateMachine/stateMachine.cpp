#include "StateMachine/stateMachine.hpp"
#include "StateMachine/virtualState.hpp"
#include "Managers/UIManager.hpp"

#include <iostream>

StateMachine::StateMachine() : window(sf::VideoMode(1020, 675), "Final Year Project - Ben Holdsworth | Q5108513", sf::Style::None),
							   gui(window) {
	windowPtr = &window;
	guiPtr = &gui;
	this->Initialise();
}

void StateMachine::Initialise() {
	isRunning = true;

	UIManager::Instance()->LoadBaseUI(windowPtr, this, guiPtr);
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
		SwitchState(state);
		return;
	}
	
	if (!states.empty()) {
		currentState->Pause();
		previousState = currentState;
	}

	states.push_back(state);
	states.back()->Initialise(windowPtr, guiPtr);
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
		currentState->HandleEvent(this, event);
		gui.handleEvent(event);
	}
}

void StateMachine::Update() {
	currentState->Update(this);
}

void StateMachine::Render() {
	window.clear();

	UIManager::Instance()->Render();
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
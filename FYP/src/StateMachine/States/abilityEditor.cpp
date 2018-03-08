#include "includeStates.hpp"

AbilityEditState AbilityEditState::abilitystate;

void AbilityEditState::Initialise(sf::RenderWindow* window) {
	windowRef = window;
}

void AbilityEditState::CleanUp() {

}

void AbilityEditState::Pause() {

}

void AbilityEditState::Resume() {

}

void AbilityEditState::HandleEvent(StateMachine* machine, sf::Event event) {

}

void AbilityEditState::Update(StateMachine* machine) {

}

void AbilityEditState::Render(StateMachine* machine) {
	windowRef->clear();
	windowRef->display();
}
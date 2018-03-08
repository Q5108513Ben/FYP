#include "includestates.hpp"

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

void AbilityEditState::HandleEvents(StateMachine* machine) {

}

void AbilityEditState::Update(StateMachine* machine) {

}

void AbilityEditState::Render(StateMachine* machine) {
	windowRef->clear();
	windowRef->display();
}
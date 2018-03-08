#include "includestates.hpp"

CharacterEditState CharacterEditState::characterstate;

void CharacterEditState::Initialise(sf::RenderWindow* window) {
	windowRef = window;
}

void CharacterEditState::CleanUp() {

}

void CharacterEditState::Pause() {

}

void CharacterEditState::Resume() {

}

void CharacterEditState::HandleEvents(StateMachine* machine) {

}

void CharacterEditState::Update(StateMachine* machine) {

}

void CharacterEditState::Render(StateMachine* machine) {
	windowRef->clear();
	windowRef->display();
}
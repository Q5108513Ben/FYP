#include "includeStates.hpp"

PlayState PlayState::playstate;

void PlayState::Initialise(sf::RenderWindow* window) {
	windowRef = window;
}

void PlayState::CleanUp() {

}

void PlayState::Pause() {

}

void PlayState::Resume() {

}

void PlayState::HandleEvent(StateMachine* machine, sf::Event event) {

}

void PlayState::Update(StateMachine* machine) {

}

void PlayState::Render(StateMachine* machine) {
	windowRef->clear();
	windowRef->display();
}
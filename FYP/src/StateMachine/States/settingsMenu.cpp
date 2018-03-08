#include "includeStates.hpp"

SettingState SettingState::settingstate;

void SettingState::Initialise(sf::RenderWindow* window) {
	windowRef = window;
}

void SettingState::CleanUp() {

}

void SettingState::Pause() {

}

void SettingState::Resume() {

}

void SettingState::HandleEvent(StateMachine* machine, sf::Event event) {

}

void SettingState::Update(StateMachine* machine) {

}

void SettingState::Render(StateMachine* machine) {
	windowRef->clear();
	windowRef->display();
}
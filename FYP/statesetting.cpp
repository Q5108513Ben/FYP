#include "includestates.hpp"

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

void SettingState::HandleEvents(StateMachine* machine) {

}

void SettingState::Update(StateMachine* machine) {

}

void SettingState::Render(StateMachine* machine) {
	windowRef->clear();
	windowRef->display();
}
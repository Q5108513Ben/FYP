#include "includeStates.hpp"

EnemyEditState EnemyEditState::enemystate;

void EnemyEditState::Initialise(sf::RenderWindow* window) {
	windowRef = window;
}

void EnemyEditState::CleanUp() {

}

void EnemyEditState::Pause() {

}

void EnemyEditState::Resume() {

}

void EnemyEditState::HandleEvents(StateMachine* machine) {

}

void EnemyEditState::Update(StateMachine* machine) {

}

void EnemyEditState::Render(StateMachine* machine) {
	windowRef->clear();
	windowRef->display();
}
#include "statemachine.hpp"
#include "statetitlescreen.hpp"

void main() {
	StateMachine statemachine;
	statemachine.PushState(TitleScreenState::Instance());

	while (statemachine.Running()) {
		statemachine.HandleEvents();
		statemachine.Update();
		statemachine.Render();
	}

	statemachine.CleanUp();
}
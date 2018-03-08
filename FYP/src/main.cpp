#include "StateMachine/stateMachine.hpp"
#include "StateMachine/States/introScreen.hpp"

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
#pragma once

#include "statemachine.hpp"

class State {
	public:
		virtual void Initialise(sf::RenderWindow* window) = 0;
		virtual void CleanUp() = 0;
		virtual void Pause() = 0;
		virtual void Resume() = 0;
		virtual void HandleEvents(StateMachine* machine) = 0;
		virtual void Update(StateMachine* machine) = 0;
		virtual void Render(StateMachine* machine) = 0;
	protected:
		State() {}
};
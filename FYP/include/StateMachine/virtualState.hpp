#pragma once

#include "StateMachine/stateMachine.hpp"

class State {
	public:
		virtual void Initialise(sf::RenderWindow* window) = 0;
		virtual void CleanUp() = 0;
		virtual void Pause() = 0;
		virtual void Resume() = 0;
		virtual void HandleEvent(StateMachine* machine, sf::Event event) = 0;
		virtual void Update(StateMachine* machine) = 0;
		virtual void Render(StateMachine* machine) = 0;
	protected:
		State() {}
};
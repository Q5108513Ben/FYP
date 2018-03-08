#pragma once

#include "StateMachine/virtualState.hpp"

class CharacterEditState : public State {
	public:
		void Initialise(sf::RenderWindow* window);
		void CleanUp();

		void Pause();
		void Resume();

		void HandleEvent(StateMachine* machine, sf::Event event);
		void Update(StateMachine* machine);
		void Render(StateMachine* machine);

		static CharacterEditState* Instance() { return &characterstate; }

	protected:
		CharacterEditState() { }

	private:
		static CharacterEditState characterstate;
		sf::RenderWindow* windowRef{ nullptr };
};
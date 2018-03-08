#pragma once

#include "virtualstate.hpp"

class CharacterEditState : public State {
	public:
		void Initialise(sf::RenderWindow* window);
		void CleanUp();

		void Pause();
		void Resume();

		void HandleEvents(StateMachine* machine);
		void Update(StateMachine* machine);
		void Render(StateMachine* machine);

		static CharacterEditState* Instance() { return &characterstate; }

	protected:
		CharacterEditState() { }

	private:
		static CharacterEditState characterstate;
		sf::RenderWindow* windowRef{ nullptr };
};
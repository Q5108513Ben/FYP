#pragma once

#include "StateMachine/virtualState.hpp"

class EnemyEditState : public State {
	public:
		void Initialise(sf::RenderWindow* window);
		void CleanUp();

		void Pause();
		void Resume();

		void HandleEvents(StateMachine* machine);
		void Update(StateMachine* machine);
		void Render(StateMachine* machine);

		static EnemyEditState* Instance() { return &enemystate; }

	protected:
		EnemyEditState() { }

	private:
		static EnemyEditState enemystate;
		sf::RenderWindow* windowRef{ nullptr };
};
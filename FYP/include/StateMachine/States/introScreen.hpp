#pragma once

#include "StateMachine/virtualState.hpp"

class TitleScreenState : public State {
	public:
		void Initialise(sf::RenderWindow* window);
		void CleanUp();

		void Pause();
		void Resume();

		void HandleEvent(StateMachine* machine, sf::Event event);
		void Update(StateMachine* machine);
		void Render(StateMachine* machine);

		static TitleScreenState* Instance() { return &titlestate; }

	protected:
		TitleScreenState() { }

	private:
		static TitleScreenState titlestate;
		sf::RenderWindow* windowRef{ nullptr };

		std::vector<sf::Sprite> sprites;
};
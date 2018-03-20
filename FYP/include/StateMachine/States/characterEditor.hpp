#pragma once

#include "StateMachine/virtualState.hpp"

class CharacterEditState : public State {
	public:
		void Initialise(sf::RenderWindow* window, tgui::Gui* gui);
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
		std::vector<sf::Sprite> sprites;

		void ShowSearch(sf::String imageName, sf::String searchName);
		void UnfocusSearch(sf::String imageName, sf::String searchName);
		void LoadCharacter();
		
		bool CheckListSelected();
		
		static CharacterEditState characterstate;
		sf::RenderWindow* windowRef{ nullptr };
		tgui::Gui* guiRef{ nullptr };
};
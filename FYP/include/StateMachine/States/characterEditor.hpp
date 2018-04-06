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
		enum UI {
			CharacterList,
			CharacterInfo,
			ClassInfo
		};

		std::vector<sf::Sprite> sprites;

		void ShowSearch(sf::String imageName, sf::String searchName);
		void UnfocusSearch(sf::String imageName, sf::String searchName);
		void LoadCharacter();
		void LoadClass();
		
		bool CheckListSelected(sf::String listName);

		void CheckNameChange();
		void CheckClassNameChange();
		void UpdateStatTotal(int index);

		void HideUI(UI ui);

		void CheckSearchBar();
		bool searchEntered{ false };

		sf::String nameSaved{ "" };
		sf::String nameEdited{ "" };
		bool nameChanged = false;

		sf::String classNameSaved{ "" };
		sf::String classNameEdited{ "" };
		bool classNameChanged = false;

		int val0{ 0 }, val1{ 0 }, val2{ 0 }, val3{ 0 }, val4{ 0 }, val5{ 0 };
		int statRemaining{ 12 };
		void IncStatRemaining(int& stat, int newValue);
		bool DecStatRemaining(int& stat, int newValue);
		
		static CharacterEditState characterstate;
		sf::RenderWindow* windowRef{ nullptr };
		tgui::Gui* guiRef{ nullptr };
};
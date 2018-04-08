#pragma once

#include "StateMachine/virtualState.hpp"

class EnemyEditState : public State {
	public:
		void Initialise(sf::RenderWindow* window, tgui::Gui* gui);
		void CleanUp();

		void Pause();
		void Resume();

		void HandleEvent(StateMachine* machine, sf::Event event);
		void Update(StateMachine* machine);
		void Render(StateMachine* machine);

		static EnemyEditState* Instance() { return &enemystate; }

	protected:
		EnemyEditState() { }

	private:
		enum UI {
			EnemyList,
			EnemyInfo,
			StatInfo,
			AbilityInfo,
			AIInfo,
			DropInfo
		};

		std::vector<sf::Sprite> sprites;

		void ShowSearch(sf::String imageName, sf::String searchName);
		void UnfocusSearch(sf::String imageName, sf::String searchName);
		void LoadEnemy();

		bool CheckListSelected(sf::String listName);

		void CheckNameChange();

		void HideUI(UI ui);

		void CheckSearchBar();
		bool searchEntered{ false };

		sf::String nameSaved{ "" };
		sf::String nameEdited{ "" };
		bool nameChanged = false;

		static EnemyEditState enemystate;
		sf::RenderWindow* windowRef{ nullptr };
		tgui::Gui* guiRef{ nullptr };
};
#pragma once

#include "StateMachine/virtualState.hpp"

class AbilityEditState : public State {
public:
	void Initialise(sf::RenderWindow* window, tgui::Gui* gui);
	void CleanUp();

	void Pause();
	void Resume();

	void HandleEvent(StateMachine* machine, sf::Event event);
	void Update(StateMachine* machine);
	void Render(StateMachine* machine);

	static AbilityEditState* Instance() { return &abilitystate; }

protected:
	AbilityEditState() { }

private:
	enum UI {
		AbilityList,
		AbilityInfo,
		GeneralInfo
	};

	std::vector<sf::Sprite> sprites;

	void ShowSearch(sf::String imageName, sf::String searchName);
	void UnfocusSearch(sf::String imageName, sf::String searchName);
	void LoadAbility();
	void LoadEffect();
	void OpenTab();

	bool CheckListSelected(sf::String listName);

	void CheckNameChange();

	void HideUI(UI ui);

	void CheckSearchBar();
	bool searchEntered{ false };

	sf::String nameSaved{ "" };
	sf::String nameEdited{ "" };
	bool nameChanged = false;

	bool isTabSelected{ false };

	static AbilityEditState abilitystate;
	sf::RenderWindow* windowRef{ nullptr };
	tgui::Gui* guiRef{ nullptr };
};
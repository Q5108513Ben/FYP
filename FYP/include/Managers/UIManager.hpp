#pragma once
#include "TGUI/TGUI.hpp"
#include "StateMachine/stateMachine.hpp"

class UIManager {
	public:
		void LoadBaseUI(sf::RenderWindow* window, StateMachine* machine, tgui::Gui* gui);

		void Render();

		bool isGrabbed() { return grabbedWindow; }

		static UIManager* Instance() { return &ui; }

	protected:
		UIManager();

	private:
		void WindowDragOn();

		void ShowButton(std::string buttonName);
		void HideButton(std::string buttonName);
		void HideButtonToggle(unsigned int buttonID);
		void ToggleButton(unsigned int buttonID);

		void ActivateTab(unsigned int tabID, StateMachine* machine);
		void HideTab(unsigned int tabID);

		void QuitProgram(StateMachine* machine);

		std::vector<sf::Sprite> sprites;
		sf::RenderWindow* windowPtr{ nullptr };
		tgui::Gui* guiPtr{ nullptr };

		sf::Vector2i grabbedOffset;
		bool grabbedWindow{ false };

		bool playButtonActive{ false };
		bool pauseButtonActive{ true };
		bool helpButtonActive{ false };
		bool playerTabActive{ false };
		bool enemyTabActive{ false };
		bool abilityTabActive{ false };

		tgui::EditBox::Ptr editBox;
		tgui::ListBox::Ptr listBox;
		tgui::ComboBox::Ptr comboBox;

		static UIManager ui;
};
#pragma once

#include "StateMachine/virtualState.hpp"

class SettingState : public State {
public:
	void Initialise(sf::RenderWindow* window);
	void CleanUp();

	void Pause();
	void Resume();

	void HandleEvent(StateMachine* machine, sf::Event event);
	void Update(StateMachine* machine);
	void Render(StateMachine* machine);

	static SettingState* Instance() { return &settingstate; }

protected:
	SettingState() { }

private:
	static SettingState settingstate;
	sf::RenderWindow* windowRef{ nullptr };
};
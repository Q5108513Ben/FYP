#pragma once

#include "virtualstate.hpp"

class SettingState : public State {
public:
	void Initialise(sf::RenderWindow* window);
	void CleanUp();

	void Pause();
	void Resume();

	void HandleEvents(StateMachine* machine);
	void Update(StateMachine* machine);
	void Render(StateMachine* machine);

	static SettingState* Instance() { return &settingstate; }

protected:
	SettingState() { }

private:
	static SettingState settingstate;
	sf::RenderWindow* windowRef{ nullptr };
};
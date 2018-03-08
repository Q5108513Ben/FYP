#pragma once

#include "virtualstate.hpp"

class AbilityEditState : public State {
public:
	void Initialise(sf::RenderWindow* window);
	void CleanUp();

	void Pause();
	void Resume();

	void HandleEvents(StateMachine* machine);
	void Update(StateMachine* machine);
	void Render(StateMachine* machine);

	static AbilityEditState* Instance() { return &abilitystate; }

protected:
	AbilityEditState() { }

private:
	static AbilityEditState abilitystate;
	sf::RenderWindow* windowRef{ nullptr };
};
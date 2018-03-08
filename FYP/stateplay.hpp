#pragma once

#include "virtualstate.hpp"

class PlayState : public State {
public:
	void Initialise(sf::RenderWindow* window);
	void CleanUp();

	void Pause();
	void Resume();

	void HandleEvents(StateMachine* machine);
	void Update(StateMachine* machine);
	void Render(StateMachine* machine);

	static PlayState* Instance() { return &playstate; }

protected:
	PlayState() { }

private:
	static PlayState playstate;
	sf::RenderWindow* windowRef{ nullptr };
};
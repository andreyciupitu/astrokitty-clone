#pragma once

#include <string>

#include <Component/SimpleScene.h>
#include <AstroKitty/Character.h>
#include <AstroKitty/Platform.h>

class GameWorld : public SimpleScene
{
public:
	GameWorld() {}
	virtual ~GameWorld();
	virtual void Init() override;

private:
	virtual void FrameStart() override;
	void Simulate(float deltaTimeSeconds);
	virtual void Update(float deltaTimeSeconds) override;
	virtual void FrameEnd() override {};

	virtual void OnKeyPress(int key, int mods) override {};
	virtual void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;

private:
	Character *astronaut;
	std::vector<Platform*> platforms;
	std::vector<Asteroid*> asteroids;
};
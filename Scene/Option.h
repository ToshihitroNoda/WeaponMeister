#ifndef OPTION_H_
#define OPTION_H_

#include "Scene.h"
#include "SceneManager.h"
#include "../GameManager.h"

class Option : public Scene
{
public:
	GameManager& gm = GameManager::GetInstance();
	SceneManager& sm = SceneManager::GetInstance();

	Option() : Scene()
	{
		this->tag = "Option";
	}

	void Init() override;
	void Final() override;
	void Update() override;
	void Change() override;
	void Draw() override;

private:
	int cursorX = 590;
};

#endif
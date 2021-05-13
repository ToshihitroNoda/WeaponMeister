#ifndef GAMEGLEAR_H_
#define GAMECLEAR_H_

#include "Scene.h"
#include "SceneManager.h"
#include "GameManager.h"

class GameClear : public Scene
{
public:
	GameManager& gm  = GameManager::GetInstance();
	SceneManager& sm = SceneManager::GetInstance();

	GameClear() : Scene()
	{
		this->tag = "GameClear";
	}

	void Init() override;
	void Final() override;
	void Update() override;
	void Draw() override;
};

#endif


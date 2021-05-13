#ifndef GAMEOVER_H_
#define GAMEOVER_H_

#include "Scene.h"
#include "SceneManager.h"
#include "GameManager.h"

class GameOver : public Scene
{
public:
	GameManager& gm  = GameManager::GetInstance();
	SceneManager& sm = SceneManager::GetInstance();

	GameOver() : Scene()
	{
		this->tag = "GameOver";
	}

	void Init() override;
	void Final() override;
	void Update() override;
	void Draw() override;
};

#endif

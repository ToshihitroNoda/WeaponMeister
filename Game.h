#ifndef GAME_H_
#define GAME_H_

#include <DxLib.h>

#include "SceneManager.h"
#include "Scene.h"
#include "GameManager.h"

class Game
{
public:
	SceneManager& sm = SceneManager::GetInstance();
	GameManager&  gm = GameManager::GetInstance();

	Game() {};
	~Game() {};

	void Init();
	void Update();
	void Draw();
};

#endif


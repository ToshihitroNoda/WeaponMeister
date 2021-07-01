#ifndef GAME_H_
#define GAME_H_

#include <DxLib.h>

#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "GameManager.h"

class Game
{
public:
	SceneManager& sm = SceneManager::GetInstance();
	GameManager& gm  = GameManager::GetInstance();

	Game()  = default;
	~Game() = default;

	void Init();
	void Update();
	void Draw();
private:
	bool is_mousePos_outsideWindow_ = false;
};

#endif


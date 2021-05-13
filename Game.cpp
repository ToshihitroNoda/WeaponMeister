#include "Game.h"

#include "MyRandom.h"
#include "Input.h"
#include "Image.h"

void Game::Init()
{
	Image::Load();
	Input::Init();
	MyRandom::Init();
	ChangeFont("UD デジタル 教科書体 N-B");
	ChangeFontType(DX_FONTTYPE_EDGE);

	gm.money = gm.defaultMoney;

	sm.LoadScene("Title");
}

void Game::Update()
{
	Input::Update();

	sm.currentScene->Update();

	if (sm.prevScene->isDead == true)
		sm.prevScene.~shared_ptr();
}

void Game::Draw()
{
	sm.currentScene->Draw();
}

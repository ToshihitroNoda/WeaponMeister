#include "Game.h"

#include "MyRandom.h"
#include "Input.h"
#include "Music.h"

void Game::Init()
{
	Input::Init();
	MyRandom::Init();
	ChangeFont("UD �f�W�^�� ���ȏ��� N-B");
	ChangeFontType(DX_FONTTYPE_EDGE);
	Music::Load();

	gm.money = gm.defaultMoney;

	sm.LoadScene("Title");
}

void Game::Update()
{
	Input::Update();

	sm.currentScene->Update(); 
}

void Game::Draw()
{
	sm.currentScene->Draw();
}

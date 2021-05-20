#ifndef GAMEGLEAR_H_
#define GAMECLEAR_H_

#include "Scene.h"
#include "Screen.h"
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

private:
	const int WindowHeight = 280;
	const int WindowX_ = 5;
	const int WindowY_ = Screen::height - WindowHeight;
	const int CursorX_ = 1150;
	const int CursorY_ = 630;
	const int DrawFlashTiming_ = 20;
	const int Divisor_ = 30;

	int IconFlashCount_ = 0;

	std::string filePath_ = "";

	bool massegeEnd_ = false;
};

#endif


#ifndef GAMEOVER_H_
#define GAMEOVER_H_

#include "Scene.h"
#include "Screen.h"
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

private:
	const int WindowHeight = 280;
	const int WindowX_ = 5;
	const int WindowY_ = Screen::height - WindowHeight;
	const int CursorX_ = 1150;
	const int CursorY_ = 630;
	const int DrawFlashTiming_ = 20;
	const int Divisor_ = 30;

	const int FontSize_ = 30;
	const int TitleX_   = 400;
	const int TitleY_	= 300;
	const int DayX_		= 600;
	const int DayY_		= 400; 
	const int NextMassegeX_ = 900;
	const int NextMassegeY_ = 600;

	int IconFlashCount_ = 0;

	std::string filePath_ = "";

	bool massegeEnd_ = false;
};

#endif

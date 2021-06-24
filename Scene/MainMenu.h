#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "Scene.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "DataLoad.h"

class MainMenu : public Scene
{
public:
	GameManager& gm  = GameManager::GetInstance();
	SceneManager& sm = SceneManager::GetInstance(); // シーンマネージャへの参照

	MainMenu() : Scene()
	{
		this->tag = "MainMenu";
	}

	void Init() override;
	void Final() override;
	void Update() override;
	void Draw() override;

private:
	DataLoad dataLoad_;

	const int MenuStrX_Init_ = 1000;
	const int MenuStrY_Init_ = 500;
	const int MenuStrY_Dist_ = 80;
	const int FontSize_      = 30;

	int CursorY_Init_ = 490;
	int CursorX_      = 930;
	int CursorY_      = CursorY_Init_;
	int CursorY_Dist_ = 80;

	const int DrawFlashTiming_ = 20;
	const int Divisor_         = 30;
	int count_                 = 0;

	std::vector<std::string> MenuStr_{ "Start","Continue","Exit" };
};

#endif


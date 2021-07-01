#ifndef GAMEGLEAR_H_
#define GAMECLEAR_H_

#include "Scene.h"
#include "../Screen.h"
#include "SceneManager.h"
#include "../GameManager.h"

class GameClear : public Scene
{
public:
	GameManager& gm =  GameManager::GetInstance();
	SceneManager& sm = SceneManager::GetInstance();

	GameClear() : Scene()
	{
		this->tag = "GameClear";
	}

	void Init() override;
	void Final() override;
	void Update() override;
	void Change() override;
	void Draw() override;

private:
	const int WindowHeight_    = 280;
	const int WindowX_         = 5;
	const int WindowY_         = Screen::height - WindowHeight_;
	const int CursorX_         = 1150;
	const int CursorY_         = 630;
	const int OptionMenuX_     = 800;
	const int OptionMenuY_     = 690;
	const int DrawFlashTiming_ = 20;
	const int Divisor_         = 30;
	const int AutoSpeed_       = 180;
	const int SkipSpeed_       = 10;
	const int RentLastDay_     = 2800;

	const int CsvSkipCsell_        = 2;
	const int CsvWeaponIdCsll_     = 0;
	const int CsvQuality_1Cell_    = 1;
	const int CsvQuality_2Cell_    = 2;
	const int CsvEvaluation_1Cell_ = 3;
	const int CsvEvaluation_2Cell_ = 4;
	const int CsvEvaluation_3Cell_ = 5;

	int IconFlashCount_ = 0;
	int autoCounter_    = 0;
	int skipCounter_    = 0;

	int sold_weapon_         = 0;
	int sold_weapon_quality_ = 0;
	int evaluation_          = 0;


	std::string filePath_ = "";

	bool autoMode_   = false;
	bool skipMode_   = false;
	bool messageEnd_ = false;
};

#endif


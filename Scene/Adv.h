#ifndef ADV_H_
#define ADV_H_

#include "Scene.h"
#include "SceneManager.h"
#include "../GameManager.h"
#include "../Screen.h"

class Adv : public Scene
{
public:
	GameManager& gm  = GameManager::GetInstance();
	SceneManager& sm = SceneManager::GetInstance(); // シーンマネージャへの参照

	Adv() : Scene()
	{
		this->tag = "Adv";
	}

	void Init() override;
	void Final() override;
	void Update() override;
	void Change() override;
	void Draw() override;

	static int day;

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
	const int AutoSpeed_       = 120;
	const int SkipSpeed_       = 5;

	int IconFlashCount_ = 0;
	int autoCounter_    = 0;
	int skipCounter_    = 0;

	std::string filePath_ = "";

	bool autoMode_ = false;
	bool skipMode_ = false;
};

#endif


#ifndef TITLE_H_
#define TITLE_H_

#include "Scene.h"
#include "SceneManager.h"
#include "GameManager.h"

class Title : public Scene
{
public:
	GameManager& gm  = GameManager::GetInstance();
	SceneManager& sm = SceneManager::GetInstance(); // シーンマネージャへの参照

	Title() : Scene()
	{
		this->tag = "Title";
	}

	void Init() override;
	void Final() override;
	void Update() override;
	void Draw() override;

private:
	const int DrawFlashTiming_	= 20;
	const int Divisor_			= 30;
	const int DrawButtonX_		= 50;
	const int DrawButtonY_		= 600;
	const int TitleLogoBackX_	= 274;
	const int TitleLogoBackY_	= 100;

	int count_ = 0;

};

#endif

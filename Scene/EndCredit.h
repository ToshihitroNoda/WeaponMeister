#ifndef ENDCREDIT_H_
#define ENDCREDIT_H_

#include "Scene.h"
#include "SceneManager.h"
#include "GameManager.h"

class EndCredit : public Scene
{
public:
	GameManager& gm  = GameManager::GetInstance();
	SceneManager& sm = SceneManager::GetInstance();

	EndCredit() : Scene()
	{
		tag = "EndCredit";
	}
	~EndCredit() = default;

	void Init() override;
	void Final() override;
	void Update() override;
	void Draw() override;

private:
	int totalSoundTime_   = 0;
	int scrollCounter_    = 0;

	float creditGraphY_   = 0.0;

	bool creditScrollEnd_ = false;
};

#endif
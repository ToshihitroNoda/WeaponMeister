#ifndef REPORT_H_
#define REPORT_H_

#include "Scene.h"
#include "SceneManager.h"
#include "GameManager.h"

class Report :  public Scene
{
public:
	GameManager& gm = GameManager::GetInstance(); // ゲームマネージャーへの参照
	SceneManager& sm = SceneManager::GetInstance(); // シーンマネージャーへの参照

	Report() : Scene() // コンストラクタ
	{
		this->tag = "Report";
	}
	~Report() = default;

	void Init() override;
	void Final() override;
	void Update() override;
	void Draw() override;

private:
	const int LastDay_ = 14;

	const int NextMassegeX_ = 900;
	const int NextMassegeY_ = 600;
};

#endif
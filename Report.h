#ifndef REPORT_H_
#define REPORT_H_

#include "Scene.h"
#include "SceneManager.h"
#include "GameManager.h"

class Report :  public Scene
{
public:
	GameManager& gm = GameManager::GetInstance(); // �Q�[���}�l�[�W���[�ւ̎Q��
	SceneManager& sm = SceneManager::GetInstance(); // �V�[���}�l�[�W���[�ւ̎Q��

	Report() : Scene() // �R���X�g���N�^
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
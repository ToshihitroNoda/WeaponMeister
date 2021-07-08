#ifndef PLAYER_H_
#define PLAYER_H_

#include "../GameManager.h"
#include "GameObject.h"
#include "../Screen.h"

enum class State
{
	collect,
	run,
	wait
};

class Player : public GameObject
{
public:
	GameManager& gm = GameManager::GetInstance();

	Player() = default;
	Player(Vector3 position)
	{
		this->position = position;
		tag = "Player";

		// �摜�s�N�Z����
		imageWidth          = 64;
		imageHeight         = 64;
		imageLength         = 64;
		// �����蔻��̍��[�̃I�t�Z�b�g
		hitboxOffsetLeft    = 0;
		hitboxOffsetRight   = 0;
		hitboxOffsetTop     = 0;
		hitboxOffsetBottom  = 0;
		hitboxOffsetForward = 0;
		hitboxOffsetBack    = 0;

		if (isRotaGraph == true)
		{   // �摜�̒��S���N�_�ɕ`���ꍇ�̂���
			rotaGraphShift = { (float)imageWidth / 2, (float)imageHeight / 2, (float)imageLength / 2 };
		}

		// �~�h���̒l���������̂Ƃ��Ɍv�Z���ČŒ�l�𓾂�
		collisionDetectionMiddleX_ = (GetRight() - GetLeft()) / 2;
		collisionDetectionMiddleZ_ = (GetForward() - GetBack()) / 2;

		SetMousePoint(Screen::width / 2, Screen::height / 2); // �}�E�X�J�[�\��������

		camDistanceFromPlayer_ = 250; // �v���C������J�����܂ł�Y���ʏ�̋���
		camHeightFromTerrain_  = -200; // �n�ʂ���J�����܂ł�Y������̍���

	};
	~Player() = default;

	void Init();
	void Update() override;
	void Draw() override;
	void OnCollision(std::shared_ptr<GameObject> other);


	int backX = 0;

private:
	void HandleInput();

	void AnimationAttach(int AtnimIndex);
	void PlayAnimation(float ConstPlayTime, bool isLoop);

	int attachIndex_     = 0;
	int prevAttachIndex_ = 0;
	int prevAnimIndex_   = 0;
	int tapSoundTimer_   = 0;

	float totalTime_                  = 0.0f;
	float playTime_                   = 0.0f;
	float modelAngle_                 = 0.0f;
	float moveSpeedMax_               = 15.0f;
	float moveSpeed_                  = 0.0f;
	float camDistanceFromPlayer_      = 0.0f;
	float camHeightFromTerrain_       = 0.0f;
	float collisionDetectionMiddleX_  = 0.0f;
	float collisionDetectionMiddleZ_  = 0.0f;

	bool collectAttach_          = false;
	bool runAttach_              = false;
	bool waitAttach_             = false;
	std::vector<bool> attachCheck_{ collectAttach_, runAttach_, waitAttach_ };

	const int DrawStrPosX_  = 500;
	const int DrawStrPosY_  = 500;
	const int TapSoundTime_ = 30;

	const float IncreaseSpeed_ = 0.5f;
	const float DecreaseSpeed_ = 0.8f;
};

#endif
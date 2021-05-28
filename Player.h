#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameManager.h"
#include "GameObject.h"
#include "Screen.h"

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
	Player(float x, float y, float z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		tag = "Player";

		// 画像ピクセル数
		imageWidth          = 64;
		imageHeight         = 64;
		imageLength         = 64;
		// 当たり判定の左端のオフセット
		hitboxOffsetLeft    = 0;
		hitboxOffsetRight   = 0;
		hitboxOffsetTop     = 0;
		hitboxOffsetBottom  = 0;
		hitboxOffsetForward = 0;
		hitboxOffsetBack    = 0;

		if (isRotaGraph == true)
		{   // 画像の中心を起点に描く場合のずれ
			rotaGraphShiftX = (float)imageWidth / 2;
			rotaGraphShiftY = (float)imageHeight / 2;
			rotaGraphShiftZ = (float)imageLength / 2;
		}

		// ミドルの値を初期化のときに計算して固定値を得る
		collisionDetectionMiddleX_ = (GetRight() - GetLeft()) / 2;
		collisionDetectionMiddleZ_ = (GetForward() - GetBack()) / 2;

		SetMousePoint(Screen::width / 2, Screen::height / 2); // マウスカーソル初期化

		camDistanceFromPlayer_ = 250; // プレイヤからカメラまでのY平面上の距離
		camHeightFromTerrain_  = -200; // 地面からカメラまでのY方向上の高さ

	};
	~Player() = default;

	void HandleInput();

	void MoveX();
	void MoveY();
	void MoveZ();

	void Init();
	void Update();
	void Draw();
	void OnCollision(std::shared_ptr<GameObject> other);

	void AnimationAttach(int AtnimIndex);
	void PlayAnimation(float ConstPlayTime, bool isLoop);

	const int BackImageWidth = 8192;
	int backX = 0;

private:
	int mouseX_          = 0;
	int mouseY_          = 0;
	int prevMouseX_      = 0;
	int attachIndex_     = 0;
	int prevAttachIndex_ = 0;
	int prevAnimIndex_   = 0;
	int tapSoundTimer_   = 0;

	float totalTime_                  = 0.0f;
	float playTime_                   = 0.0f;
	float modelAngle_                 = 0.0f;
	float moveSpeedMax_               = 15.0f;
	float moveSpeed_                  = 0.0f;
	float moveSpeedLateral_           = 0.0f;
	float camDistanceFromPlayer_      = 0.0f;
	float camHeightFromTerrain_       = 0.0f;
	float nowCamAngle_                = 0.0f;
	float percentAngleByCursorDis_    = 0.0f; // マウスの移動距離に応じて角度変える
	float percentAngleByCursorDis_BG_ = 0.0f;
	float collisionDetectionMiddleX_  = 0.0f;
	float collisionDetectionMiddleZ_  = 0.0f;

	bool doLateralMove_ = false;
	bool canAngleInit_  = false;
	bool collectAttach_ = false;
	bool runAttach_     = false;
	bool waitAttach_    = false;
	std::vector<bool> attachCheck_{ collectAttach_, runAttach_, waitAttach_ };

	const int MaxAngle     = 360;
	const int DrawStrPosX  = 500;
	const int DrawStrPosY  = 500;
	const int TapSoundTime = 30;

	const float IncreaseSpeed = 0.3f;
	const float DecreaseSpeed = 0.9f;
};

#endif
#include "Player.h"

#include <DxLib.h>
#include "../MyLib/Input.h"
#include "../MyLib/MyMath.h"
#include "../Map.h"
#include "../Music.h"

#include <cmath> 

void Player::Init()
{
	AnimationAttach((int)State::wait);

	// プレイヤーモデルの角度
	modelAngle_ = -((camera.nowCamAngle_ - 90) * MyMath::Deg2Rad);

	// カメラ位置
	Vector3 cameraPos
	{ /* X座標 */gm.player->position.x + (camDistanceFromPlayer_ * std::cos(camera.nowCamAngle_ * MyMath::Deg2Rad)),
		/* Y座標 */ gm.player->position.y - camHeightFromTerrain_,
		/* Z座標 */ gm.player->position.z + (camDistanceFromPlayer_ * std::sin(camera.nowCamAngle_ * MyMath::Deg2Rad)) };
	camera.SetPosition(cameraPos);

	//カメラはプレイヤの方を見る
	Vector3 lookPos{ gm.player->position.x, gm.player->position.y + 100, gm.player->position.z };
	camera.LookAt(lookPos);
}

void Player::HandleInput()
{
	if (!attachCheck_[(int)State::collect])
	{
		if (Input::GetButton(PAD_INPUT_4))              // A
		{
			moveSpeed_ += IncreaseSpeed_;
			if (moveSpeed_ > moveSpeedMax_)
				moveSpeed_ = moveSpeedMax_;      //Maxスピードで止める
			if (!attachCheck_[(int)State::run] && !attachCheck_[(int)State::collect])
				AnimationAttach((int)State::run);
			modelAngle_ = -(camera.nowCamAngle_ * MyMath::Deg2Rad);
		}
		else if (Input::GetButton(PAD_INPUT_6))         // D
		{
			moveSpeed_ += IncreaseSpeed_;
			if (moveSpeed_ < -moveSpeedMax_)
				moveSpeed_ = -moveSpeedMax_;     //Maxスピードで止める
			if (!attachCheck_[(int)State::run] && !attachCheck_[(int)State::collect])
				AnimationAttach((int)State::run);
			modelAngle_ = -((camera.nowCamAngle_ - 180) * MyMath::Deg2Rad);
		}

		if (Input::GetButton(PAD_INPUT_8))              // W
		{
			moveSpeed_ += IncreaseSpeed_;
			if (moveSpeed_ > moveSpeedMax_)
				moveSpeed_ = moveSpeedMax_;             //Maxスピードで止める
			if (!attachCheck_[(int)State::run] && !attachCheck_[(int)State::collect])
				AnimationAttach((int)State::run);
			modelAngle_ = -((camera.nowCamAngle_ - 90) * MyMath::Deg2Rad);
		}
		else if (Input::GetButton(PAD_INPUT_5))         // S
		{
			moveSpeed_ += IncreaseSpeed_;
			if (moveSpeed_ < -moveSpeedMax_)
				moveSpeed_ = -moveSpeedMax_;           //Maxスピードで止める
			if (!attachCheck_[(int)State::run] && !attachCheck_[(int)State::collect])
				AnimationAttach((int)State::run);
			modelAngle_ = -((camera.nowCamAngle_ + 90) * MyMath::Deg2Rad);
		}

		if (Input::GetButton(PAD_INPUT_8) && Input::GetButton(PAD_INPUT_4)) // 左前
		{
			modelAngle_ = -((camera.nowCamAngle_ - 45) * MyMath::Deg2Rad);
		}
		else if (Input::GetButton(PAD_INPUT_8) && Input::GetButton(PAD_INPUT_6)) // 右前
		{
			modelAngle_ = -((camera.nowCamAngle_ - 135) * MyMath::Deg2Rad);
		}
		else if (Input::GetButton(PAD_INPUT_5) && Input::GetButton(PAD_INPUT_4)) // 左後ろ
		{
			modelAngle_ = -((camera.nowCamAngle_ + 45) * MyMath::Deg2Rad);
		}
		else if (Input::GetButton(PAD_INPUT_5) && Input::GetButton(PAD_INPUT_6)) // 右後ろ
		{
			modelAngle_ = -((camera.nowCamAngle_ + 135) * MyMath::Deg2Rad);
		}

		if (!Input::GetButton(PAD_INPUT_4) &&
			!Input::GetButton(PAD_INPUT_6) &&
			!Input::GetButton(PAD_INPUT_5) &&
			!Input::GetButton(PAD_INPUT_8))
		{
			if (!attachCheck_[(int)State::wait] && !attachCheck_[(int)State::collect])
				AnimationAttach((int)State::wait);
		}
		else
		{
			if (tapSoundTimer_ >= TapSoundTime_)
			{
				PlaySoundMem(Music::run_SE, DX_PLAYTYPE_BACK);
				tapSoundTimer_ = 0;
			}
			tapSoundTimer_++;
		}
	}
}

// 更新処理
void Player::Update()
{
	camera.Move();
	backX = camera.backX;

	velocity = 0;

	moveSpeed_ *= DecreaseSpeed_;                // 移動速度も減速する

	// 入力を受けての処理 
	HandleInput();

	if (modelAngle_ > 0)
		modelAngle_ -= 360.0f * MyMath::Deg2Rad; // プレイヤーの角度のずれを直す

	float vx = (float)std::sin(modelAngle_) * moveSpeed_ * (modelAngle_ / std::abs(modelAngle_));
	float vz = (float)std::cos(modelAngle_) * moveSpeed_ * (modelAngle_ / std::abs(modelAngle_));
	velocity = { vx, 0.0f, vz };

	if ((Input::GetButton(PAD_INPUT_8) && Input::GetButton(PAD_INPUT_4)) ||
		(Input::GetButton(PAD_INPUT_8) && Input::GetButton(PAD_INPUT_6)) ||
		(Input::GetButton(PAD_INPUT_5) && Input::GetButton(PAD_INPUT_4)) ||
		(Input::GetButton(PAD_INPUT_5) && Input::GetButton(PAD_INPUT_6)))
	{
		velocity /= MyMath::Sqrt2;
	}

	// 実際に位置を動かす
	position += velocity;

	// カメラ位置
	Vector3 cameraPos
	{ /* X座標 */ gm.player->position.x + (camDistanceFromPlayer_ * std::cos(camera.nowCamAngle_ * MyMath::Deg2Rad)),
	  /* Y座標 */ gm.player->position.y - camHeightFromTerrain_,
	  /* Z座標 */ gm.player->position.z + (camDistanceFromPlayer_ * std::sin(camera.nowCamAngle_ * MyMath::Deg2Rad)) };
	camera.SetPosition(cameraPos);

	//カメラはプレイヤの方を見る
	Vector3 lookPos{ gm.player->position.x, gm.player->position.y + 100, gm.player->position.z };
	camera.LookAt(lookPos);

	if (attachCheck_[(int)State::collect])
		PlayAnimation(0.5f, FALSE);
	else if (attachCheck_[(int)State::run])
		PlayAnimation(0.6f, TRUE);
	else
		PlayAnimation(0.07f, TRUE);

	// マウス位置の初期化
	SetMousePoint(Screen::width / 2, Screen::height / 2);
}

// 描画処理
void Player::Draw()
{
	// プレイヤーモデルを回転させる
	MV1SetRotationXYZ(gm.image.Player, VGet(0, modelAngle_, 0));
	MV1SetPosition(gm.image.Player, position.Vec3ToVec());
	MV1SetScale(gm.image.Player, VGet(0.8f, 0.8f, 0.8f));
	MV1DrawModel(gm.image.Player);
	//DrawHitBox(); 
}


void  Player::OnCollision(std::shared_ptr<GameObject> other)
{
	if (other->tag == "FieldItem")
	{
		if (Input::GetButtonDown(PAD_INPUT_1) && gm.pouch.size() < gm.MaxPouchSize)
		{
			if (!attachCheck_[(int)State::collect])
				AnimationAttach((int)State::collect);
		}
		else if (Input::GetButtonDown(PAD_INPUT_1) && gm.pouch.size() >= gm.MaxPouchSize)
		{
			PlaySoundMem(Music::error_SE, DX_PLAYTYPE_BACK);
		}
	}

	else if (other->tag != "Bush_1" && other->tag != "Bush_2"      && other->tag != "Bush_3" &&
		     other->tag != "Bush_4" && other->tag != "BushLarge_1" && other->tag != "BushLarge_2")
	{
		if (
			(GetBack() + 10.0f < other->GetForward() && GetForward() - 10.0f > other->GetBack()) &&
			((GetLeft() - 1.0f < other->GetRight() || GetRight() + 1.0f > other->GetLeft()))
			)
		{
			if (GetLeft() < other->GetRight() &&
				GetLeft() > other->GetLeft())
			{
				SetLeft(other->GetRight() + 1.0f);
				return;
			}
			else if (GetRight() > other->GetLeft() &&
				GetRight() < other->GetRight())
			{
				SetRight(other->GetLeft() - 1.0f);
				return;
			}
		}
		else
		{
			if (GetBack() < other->GetForward() &&
				GetBack() > other->GetBack())
			{
				SetBack(other->GetForward() + 1.0f);
				return;
			}
			else if (GetForward() > other->GetBack() &&
				GetForward() < other->GetForward())
			{
				SetForward(other->GetBack() - 1.0f);
				return;
			}
		}
	}
}

void Player::AnimationAttach(int AnimIndex)
{
	attachCheck_[prevAnimIndex_] = false;             // 前回立てたフラグの初期化

	MV1DetachAnim(gm.image.Player, prevAttachIndex_); // アニメーションのデタッチ

	prevAnimIndex_   = AnimIndex;                     // 次フラグを初期化するために保存
	prevAttachIndex_ = attachIndex_;                  // 今のアニメを次デタッチするために保存

	/*-----アタッチ処理-----*/
	attachIndex_ = MV1AttachAnim(gm.image.Player, AnimIndex, -1, FALSE);
	totalTime_   = MV1GetAttachAnimTotalTime(gm.image.Player, attachIndex_);
	playTime_    = 0.0f;
	MV1SetAttachAnimTime(gm.image.Player, attachIndex_, playTime_);

	/*---------------*/

	attachCheck_[AnimIndex] = true; // アニメーションによってフラグを立てる	
}

void Player::PlayAnimation(float ConstPlayTime, bool isLoop)
{
	if (isLoop)
	{
		playTime_ += ConstPlayTime;

		if (playTime_ >= totalTime_)
		{
			playTime_ = 0.0f;
		}
		MV1SetAttachAnimTime(gm.image.Player, attachIndex_, playTime_);
	}
	else
	{
		playTime_ += ConstPlayTime;

		if (playTime_ >= totalTime_)
		{
			for (int i = 0; i < attachCheck_.size(); i++)
			{
				attachCheck_[i] = false;
			}
		}

		MV1SetAttachAnimTime(gm.image.Player, attachIndex_, playTime_);
	}
}

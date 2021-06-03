#include "Player.h"

#include <DxLib.h>
#include "Input.h"
#include "MyMath.h"
#include "Map.h"
#include "Music.h"

#include <cmath> 

void Player::Init()
{
	AnimationAttach((int)State::wait);

	// プレイヤーモデルの角度
	modelAngle_ = -((nowCamAngle_ - 90) * MyMath::Deg2Rad);

	// カメラ位置
	camera.SetPosition
	/* X座標 */(gm.player->x + (camDistanceFromPlayer_ * std::cos(nowCamAngle_ * MyMath::Deg2Rad)),
	/* Y座標 */  gm.player->y - camHeightFromTerrain_,
	/* Z座標 */  gm.player->z + (camDistanceFromPlayer_ * std::sin(nowCamAngle_ * MyMath::Deg2Rad)));

	//カメラはプレイヤの方を見る
	camera.LookAt(gm.player->x, gm.player->y + 100, gm.player->z);

}

void Player::HandleInput()
{
	if (!attachCheck_[(int)State::collect])
	{
		if (Input::GetButton(PAD_INPUT_4))              // A
		{
			doLateralMove_ = true;
			moveSpeedLateral_ += IncreaseSpeed_;
			if (moveSpeedLateral_ > moveSpeedMax_)
				moveSpeedLateral_ = moveSpeedMax_;      //Maxスピードで止める
			if (!attachCheck_[(int)State::run] && !attachCheck_[(int)State::collect])
				AnimationAttach((int)State::run);
			modelAngle_ = -(nowCamAngle_ * MyMath::Deg2Rad);
		}
		else if (Input::GetButton(PAD_INPUT_6))         // D
		{
			doLateralMove_ = true;
			moveSpeedLateral_ -= IncreaseSpeed_;
			if (moveSpeedLateral_ < -moveSpeedMax_)
				moveSpeedLateral_ = -moveSpeedMax_;     //Maxスピードで止める
			if (!attachCheck_[(int)State::run] && !attachCheck_[(int)State::collect])
				AnimationAttach((int)State::run);
			modelAngle_ = -((nowCamAngle_ - 180) * MyMath::Deg2Rad);
		}

		if (Input::GetButton(PAD_INPUT_8))              // W
		{
			doLateralMove_ = false;
			moveSpeed_ += IncreaseSpeed_;
			if (moveSpeed_ > moveSpeedMax_)
				moveSpeed_ = moveSpeedMax_;             //Maxスピードで止める
			if (!attachCheck_[(int)State::run] && !attachCheck_[(int)State::collect])
				AnimationAttach((int)State::run);
			modelAngle_ = -((nowCamAngle_ - 90) * MyMath::Deg2Rad);
		}
		else if (Input::GetButton(PAD_INPUT_5))         // S
		{
			doLateralMove_ = false;
			moveSpeed_ -= IncreaseSpeed_;
			if (moveSpeed_ < -moveSpeedMax_)
				moveSpeed_ = -moveSpeedMax_;           //Maxスピードで止める
			if (!attachCheck_[(int)State::run] && !attachCheck_[(int)State::collect])
				AnimationAttach((int)State::run);
			modelAngle_ = -((nowCamAngle_ + 90) * MyMath::Deg2Rad);
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
	GetMousePoint(&mouseX_, &mouseY_);              // マウスカーソル座標取得

	// マウスがウィンドウ内にあったらカメラ移動
	if (mouseX_ > 0 && mouseX_ < Screen::width &&
		mouseY_ > 0 && mouseY_ < Screen::height)
	{
		if (mouseX_ > prevMouseX_)                  //　マウスが右に動いていたら
		{

		    // マウスの移動距離を度数変換、360 : x = Screen::Width * 1.2f : MouseX - prevMouseX
		    //                             x(Screen::Width * 1.2f) = 360(MouseX - prevMouseX)
		    //                             x = (360(MouseX - prevMouseX)) / (Screen::Width * 1.2f)

			percentAngleByCursorDis_    = (float)((MaxAngle_ * (mouseX_ - prevMouseX_)) / (Screen::width * 1.2f));
			percentAngleByCursorDis_BG_ = (float)((MaxAngle_ * (mouseX_ - prevMouseX_)) / (BackImageWidth / 60));

			// PercentAngleByCursor初期化
			if (!canAngleInit_)
			{
				percentAngleByCursorDis_    = 0;
				percentAngleByCursorDis_BG_ = 0;
				canAngleInit_               = true;
			}

			nowCamAngle_ += percentAngleByCursorDis_;   // 度数分足す

			backX += percentAngleByCursorDis_BG_;
			if (backX <= -BackImageWidth + Screen::width)
				backX = 0;
		}
		else                                        // マウスが左に動いていたら
		{
			percentAngleByCursorDis_    = (float)((MaxAngle_ * (prevMouseX_ - mouseX_)) / (Screen::width * 1.2f));
			percentAngleByCursorDis_BG_ = (float)((MaxAngle_ * (mouseX_ - prevMouseX_)) / (BackImageWidth / 60));

			// PercentAngleByCursor初期化
			if (!canAngleInit_)
			{
				percentAngleByCursorDis_    = 0;
				percentAngleByCursorDis_BG_ = 0;
				canAngleInit_               = true;
			}

			nowCamAngle_ -= percentAngleByCursorDis_;

			backX += percentAngleByCursorDis_BG_;
			if (backX > BackImageWidth)
				backX = 0;
		}
	}

	// カメラが360度で1周するように
	if (nowCamAngle_ <= 0)        nowCamAngle_ = (float)MaxAngle_ - 1;
	if (nowCamAngle_ >= MaxAngle_) nowCamAngle_ = 1;

	prevMouseX_ = mouseX_;                               // マウスカーソル座標を保存

	vx = 0;                                              // x方向移動速度
	vy = 0;                                              // y方向移動速度
	vz = 0;                                              // z方向移動速度

	moveSpeed_        *= DecreaseSpeed_;                 // 移動速度も減速する
	moveSpeedLateral_ *= DecreaseSpeed_;

	// 入力を受けての処理 
	HandleInput();

	// 進行方向角度をX方向とZ方向の速度に変える
	if (!doLateralMove_)
	{
		vx = (float)std::cos((nowCamAngle_ + MaxAngle_ / 2) * MyMath::Deg2Rad) * moveSpeed_;
		vz = (float)std::sin((nowCamAngle_ + MaxAngle_ / 2) * MyMath::Deg2Rad) * moveSpeed_;
	}
	else
	{
		vx = (float)std::cos((nowCamAngle_ + MaxAngle_ - (MaxAngle_ / 4)) * MyMath::Deg2Rad) * moveSpeedLateral_;
		vz = (float)std::sin((nowCamAngle_ + MaxAngle_ - (MaxAngle_ / 4)) * MyMath::Deg2Rad) * moveSpeedLateral_;
	}

	if ((Input::GetButton(PAD_INPUT_8) && Input::GetButton(PAD_INPUT_4)) ||
		(Input::GetButton(PAD_INPUT_8) && Input::GetButton(PAD_INPUT_6)) ||
		(Input::GetButton(PAD_INPUT_5) && Input::GetButton(PAD_INPUT_4)) ||
		(Input::GetButton(PAD_INPUT_5) && Input::GetButton(PAD_INPUT_6)))
	{
		vx = (float)std::cos((nowCamAngle_ + MaxAngle_ / 2) * MyMath::Deg2Rad) * moveSpeed_;
		if ((nowCamAngle_ >= 45 && nowCamAngle_ < 135) || (nowCamAngle_ >= 225 && nowCamAngle_ < 315))
			vx = (float)std::cos((nowCamAngle_ + MaxAngle_ - (MaxAngle_ / 4)) * MyMath::Deg2Rad) * moveSpeedLateral_;
		vz = (float)std::sin((nowCamAngle_ + MaxAngle_ - (MaxAngle_ / 4)) * MyMath::Deg2Rad) * moveSpeedLateral_;
		if ((nowCamAngle_ >= 45 && nowCamAngle_ < 135) || (nowCamAngle_ >= 225 && nowCamAngle_ < 315))
			vz = (float)std::sin((nowCamAngle_ + MaxAngle_ / 2) * MyMath::Deg2Rad) * moveSpeed_;

		vx /= MyMath::Sqrt2;
		vx /= MyMath::Sqrt2;
	}

	// 実際に位置を動かす

	MoveX();
	MoveY();
	MoveZ();

	// カメラ位置
	camera.SetPosition
	/* X座標 */(gm.player->x + (camDistanceFromPlayer_ * std::cos(nowCamAngle_ * MyMath::Deg2Rad)),
	/* Y座標 */ gm.player->y - camHeightFromTerrain_,
	/* Z座標 */ gm.player->z + (camDistanceFromPlayer_ * std::sin(nowCamAngle_ * MyMath::Deg2Rad)));

	//カメラはプレイヤの方を見る
	camera.LookAt(gm.player->x, gm.player->y + 100, gm.player->z);

	if (attachCheck_[(int)State::collect])
		PlayAnimation(0.5f, FALSE);
	else if (attachCheck_[(int)State::run])
		PlayAnimation(0.6f, TRUE);
	else
		PlayAnimation(0.07f, TRUE);
}

// 横の移動処理
void Player::MoveX()
{
	// 横に移動する
	x += vx;
}

// Z奥行き方向の移動処理
void Player::MoveZ()
{
	// Z奥行き方向に移動する
	z += vz;
}


// 縦の移動処理
void Player::MoveY()
{
	// 縦に移動する
	y += vy;
}

// 描画処理
void Player::Draw()
{
	// プレイヤーモデルを回転させる
	MV1SetRotationXYZ(gm.image.Player, VGet(0, modelAngle_, 0));
	MV1SetPosition(gm.image.Player, VGet(x, y, z));
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

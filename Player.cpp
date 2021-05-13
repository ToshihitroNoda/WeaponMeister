#include "Player.h"

#include <DxLib.h>
#include "Input.h"
#include "Image.h"
#include "MyMath.h"
#include "Camera.h"
#include "Map.h"

#include <cmath> 

void Player::Init()
{
	AnimationAttach((int)State::wait);

	// プレイヤーモデルの角度
	modelAngle_ = -((nowCamAngle_ - 90) * MyMath::Deg2Rad);
}

void Player::HandleInput()
{
	if (Input::GetButton(PAD_INPUT_4))				// A
	{
		doLateralMove_ = true;
		MoveSpeedLateral_ += IncreaseSpeed_;
		if (MoveSpeedLateral_ > MoveSpeedMax_)
			MoveSpeedLateral_ = MoveSpeedMax_;		//Maxスピードで止める
		if (!AttachCheck_[(int)State::run] && !AttachCheck_[(int)State::collect])
			AnimationAttach((int)State::run);
		modelAngle_ = -(nowCamAngle_ * MyMath::Deg2Rad);
	}
	else if (Input::GetButton(PAD_INPUT_6))			// D
	{
		doLateralMove_ = true;
		MoveSpeedLateral_ -= IncreaseSpeed_;
		if (MoveSpeedLateral_ < -MoveSpeedMax_)
			MoveSpeedLateral_ = -MoveSpeedMax_;		//Maxスピードで止める
		if (!AttachCheck_[(int)State::run] && !AttachCheck_[(int)State::collect])
			AnimationAttach((int)State::run);
		modelAngle_ = -((nowCamAngle_ - 180) * MyMath::Deg2Rad);
	}
	if (Input::GetButton(PAD_INPUT_8))				// W
	{
		doLateralMove_ = false;
		MoveSpeed_ += IncreaseSpeed_;
		if (MoveSpeed_ > MoveSpeedMax_)
			MoveSpeed_ = MoveSpeedMax_;				//Maxスピードで止める
		if (!AttachCheck_[(int)State::run] && !AttachCheck_[(int)State::collect])
			AnimationAttach((int)State::run);
		modelAngle_ = -((nowCamAngle_ - 90) * MyMath::Deg2Rad);
	}
	else if (Input::GetButton(PAD_INPUT_5))			// S
	{
		doLateralMove_ = false;
		MoveSpeed_ -= IncreaseSpeed_;
		if (MoveSpeed_ < -MoveSpeedMax_)
			MoveSpeed_ = -MoveSpeedMax_;			//Maxスピードで止める
		if (!AttachCheck_[(int)State::run] && !AttachCheck_[(int)State::collect])
			AnimationAttach((int)State::run);
		modelAngle_ = -((nowCamAngle_ + 90) * MyMath::Deg2Rad);
	}

	if (!Input::GetButton(PAD_INPUT_4) &&
		!Input::GetButton(PAD_INPUT_6) &&
		!Input::GetButton(PAD_INPUT_5) &&
		!Input::GetButton(PAD_INPUT_8))
	{
		if (!AttachCheck_[(int)State::wait] && !AttachCheck_[(int)State::collect])
			AnimationAttach((int)State::wait);
	}
}

// 更新処理
void Player::Update()
{
	GetMousePoint(&MouseX_, &MouseY_);				// マウスカーソル座標取得

	// マウスがウィンドウ内にあったらカメラ移動
	if (MouseX_ > 0 && MouseX_ < Screen::Width &&
		MouseY_ > 0 && MouseY_ < Screen::Height)
	{
		if (MouseX_ > prevMouseX_)					//　マウスが右に動いていたら
		{

			// マウスの移動距離を度数変換、360 : x = Screen::Width * 2 : MouseX - prevMouseX
			//							   x(Screen::Width * 2) = 360(MouseX - prevMouseX)
			//							   x = (360(MouseX - prevMouseX)) / (Screen::Width * 2)

			PercentAngleByCursorDis_ = (float)((MaxAngle_ * (MouseX_ - prevMouseX_)) / (Screen::Width * 2));

			// PercentAngleByCursor初期化
			if (!canAngleInit_)
			{
				PercentAngleByCursorDis_ = 0;
				canAngleInit_ = true;
			}

			nowCamAngle_ += PercentAngleByCursorDis_;	// 度数分足す
		}
		else if (MouseX_ < prevMouseX_)					// マウスが左に動いていたら
		{
			PercentAngleByCursorDis_ = (float)((360 * (prevMouseX_ - MouseX_)) / (Screen::Width * 2));
			nowCamAngle_ -= PercentAngleByCursorDis_;
		}
	}

	// カメラが360度で1周するように
	if (nowCamAngle_ <= 0)		  nowCamAngle_ = (float)MaxAngle_ - 1;
	if (nowCamAngle_ >= MaxAngle_) nowCamAngle_ = 1;

	prevMouseX_ = MouseX_;								 // マウスカーソル座標を保存

	vx = 0;												 // x方向移動速度
	vy = 0;												 // y方向移動速度
	vz = 0;												 // z方向移動速度

	MoveSpeed_ *= DecreaseSpeed_;					 // 移動速度も減速する
	MoveSpeedLateral_ *= DecreaseSpeed_;

	// 入力を受けての処理 
	HandleInput();

	// ↓進行方向角度をX方向とZ方向の速度に変える
	if (!doLateralMove_)
	{
		vx = (float)std::cos((nowCamAngle_ + MaxAngle_ / 2) * MyMath::Deg2Rad) * MoveSpeed_;
		vz = (float)std::sin((nowCamAngle_ + MaxAngle_ / 2) * MyMath::Deg2Rad) * MoveSpeed_;
	}
	else
	{
		vx = (float)std::cos((nowCamAngle_ + MaxAngle_ - (MaxAngle_ / 4)) * MyMath::Deg2Rad) * MoveSpeedLateral_;
		vz = (float)std::sin((nowCamAngle_ + MaxAngle_ - (MaxAngle_ / 4)) * MyMath::Deg2Rad) * MoveSpeedLateral_;
	}


	// 実際に位置を動かす

	MoveX();
	MoveY();
	MoveZ();

	// カメラ位置
	Camera::SetPosition
	/* X座標 */ (gm.player->x + (camDistanceFromPlayer_ * std::cos(nowCamAngle_ * MyMath::Deg2Rad)),
	/* Y座標 */  gm.player->y - camHeightFromTerrain_,
	/* Z座標 */  gm.player->z + (camDistanceFromPlayer_ * std::sin(nowCamAngle_ * MyMath::Deg2Rad)));

	//カメラはプレイヤの方を見る
	Camera::LookAt(gm.player->x, gm.player->y + 100, gm.player->z);

	if (AttachCheck_[(int)State::collect])
		PlayAnimation(0.5f, FALSE);
	else if (AttachCheck_[(int)State::run])
		PlayAnimation(0.6f, TRUE);
	else
		PlayAnimation(0.07f, TRUE);
}

// 横の移動処理
void Player::MoveX()
{
	// 横に移動する
	x += vx;

	// 当たり判定の四隅の座標を取得
	float left = GetLeft();
	float right = GetRight() - 0.01f;
	float back = GetBack();
	float middle = back + collisionDetectionMiddleZ_;
	float forward = GetForward() - 0.01f;

	// 左端が壁にめりこんでいるか？
	if (gm.map->IsWall(left, back) ||		// 壁か？
		gm.map->IsWall(left, middle) ||		// 壁か？
		gm.map->IsWall(left, forward))		// 壁か？
	{
		float wallRight = left - (float)std::fmod(left, gm.map->CellSize) + gm.map->CellSize; // 壁の右端
		SetLeft(wallRight); // プレイヤーの左端を壁の右端に沿わす
	}
	// 右端が壁にめりこんでいるか？
	else if (
		gm.map->IsWall(right, back) ||		// 右上が壁か？
		gm.map->IsWall(right, middle) ||    // 壁か？
		gm.map->IsWall(right, forward))		// 右下が壁か？
	{
		float wallLeft = right - (float)std::fmod(right, gm.map->CellSize); // 壁の左端
		SetRight(wallLeft); // プレイヤーの右端を壁の左端に沿わす
	}
}

// Z奥行き方向の移動処理
void Player::MoveZ()
{
	// Z奥行き方向に移動する
	z += vz;

	// 当たり判定の四隅の座標を取得
	float left = GetLeft();
	float middle = left + collisionDetectionMiddleX_;
	float right = GetRight() - 0.01f;
	float back = GetBack();
	float forward = GetForward() - 0.01f;

	// 手前側が壁にめりこんでいるか？
	if (gm.map->IsWall(left, back) ||		// 壁か？
		gm.map->IsWall(middle, back) ||		// 壁か？
		gm.map->IsWall(right, back))		// 壁か？
	{
		float wallForward = back - (float)std::fmod(back, gm.map->CellSize) + gm.map->CellSize; // 壁の奥行き方向
		SetBack(wallForward); // プレイヤーの背中を壁のフォワードに沿わす
	}
	// 奥行き側が壁にめりこんでいるか？
	else if (
		gm.map->IsWall(left, forward) ||		// 壁か？
		gm.map->IsWall(middle, forward) ||		// 壁か？
		gm.map->IsWall(right, forward))			// 壁か？
	{
		float wallBack = forward - (float)std::fmod(forward, gm.map->CellSize); // 壁の手前側
		SetForward(wallBack); // プレイヤーのおでこを壁のバックに沿わす
	}
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
	MV1SetRotationXYZ(Image::Player, VGet(0, modelAngle_, 0));
	MV1SetPosition(Image::Player, VGet(x, y, z));
	MV1SetScale(Image::Player, VGet(0.8f, 0.8f, 0.8f));
	MV1DrawModel(Image::Player);
}


void  Player::OnCollision(std::shared_ptr<GameObject> other) {
	if (other->tag == "FieldItem")
	{
		if (Input::GetButtonDown(PAD_INPUT_1))
		{
			if (!AttachCheck_[(int)State::collect])
				AnimationAttach((int)State::collect);
			other->isDead = true;
		}
	}
}

void Player::AnimationAttach(int AnimIndex)
{
	AttachCheck_[prevAnimIndex_] = false;			 // 前回立てたフラグの初期化

	MV1DetachAnim(Image::Player, prevAttachIndex_);	 // アニメーションのデタッチ

	prevAnimIndex_	 = AnimIndex;						 // 次フラグを初期化するために保存
	prevAttachIndex_ = AttachIndex_;				 // 今のアニメを次デタッチするために保存

	/*-----アタッチ処理-----*/
	AttachIndex_ = MV1AttachAnim(Image::Player, AnimIndex, -1, FALSE);
	TotalTime_	 = MV1GetAttachAnimTotalTime(Image::Player, AttachIndex_);
	PlayTime_	 = 0.0f;
	MV1SetAttachAnimTime(Image::Player, AttachIndex_, PlayTime_);

	/*---------------*/

	AttachCheck_[AnimIndex] = true;					 // アニメーションによってフラグを立てる	
}

void Player::PlayAnimation(float ConstPlayTime, bool isLoop)
{
	if (isLoop)
	{
		PlayTime_ += ConstPlayTime;

		if (PlayTime_ >= TotalTime_)
		{
			PlayTime_ = 0.0f;
		}
		MV1SetAttachAnimTime(Image::Player, AttachIndex_, PlayTime_);
	}
	else
	{
		PlayTime_ += ConstPlayTime;

		if (PlayTime_ >= TotalTime_)
		{
			for (int i = 0; i < AttachCheck_.size(); i++)
			{
				AttachCheck_[i] = false;
			}
		}

		MV1SetAttachAnimTime(Image::Player, AttachIndex_, PlayTime_);
	}
}

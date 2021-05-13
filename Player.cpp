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

	// �v���C���[���f���̊p�x
	modelAngle_ = -((nowCamAngle_ - 90) * MyMath::Deg2Rad);
}

void Player::HandleInput()
{
	if (Input::GetButton(PAD_INPUT_4))				// A
	{
		doLateralMove_ = true;
		MoveSpeedLateral_ += IncreaseSpeed_;
		if (MoveSpeedLateral_ > MoveSpeedMax_)
			MoveSpeedLateral_ = MoveSpeedMax_;		//Max�X�s�[�h�Ŏ~�߂�
		if (!AttachCheck_[(int)State::run] && !AttachCheck_[(int)State::collect])
			AnimationAttach((int)State::run);
		modelAngle_ = -(nowCamAngle_ * MyMath::Deg2Rad);
	}
	else if (Input::GetButton(PAD_INPUT_6))			// D
	{
		doLateralMove_ = true;
		MoveSpeedLateral_ -= IncreaseSpeed_;
		if (MoveSpeedLateral_ < -MoveSpeedMax_)
			MoveSpeedLateral_ = -MoveSpeedMax_;		//Max�X�s�[�h�Ŏ~�߂�
		if (!AttachCheck_[(int)State::run] && !AttachCheck_[(int)State::collect])
			AnimationAttach((int)State::run);
		modelAngle_ = -((nowCamAngle_ - 180) * MyMath::Deg2Rad);
	}
	if (Input::GetButton(PAD_INPUT_8))				// W
	{
		doLateralMove_ = false;
		MoveSpeed_ += IncreaseSpeed_;
		if (MoveSpeed_ > MoveSpeedMax_)
			MoveSpeed_ = MoveSpeedMax_;				//Max�X�s�[�h�Ŏ~�߂�
		if (!AttachCheck_[(int)State::run] && !AttachCheck_[(int)State::collect])
			AnimationAttach((int)State::run);
		modelAngle_ = -((nowCamAngle_ - 90) * MyMath::Deg2Rad);
	}
	else if (Input::GetButton(PAD_INPUT_5))			// S
	{
		doLateralMove_ = false;
		MoveSpeed_ -= IncreaseSpeed_;
		if (MoveSpeed_ < -MoveSpeedMax_)
			MoveSpeed_ = -MoveSpeedMax_;			//Max�X�s�[�h�Ŏ~�߂�
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

// �X�V����
void Player::Update()
{
	GetMousePoint(&MouseX_, &MouseY_);				// �}�E�X�J�[�\�����W�擾

	// �}�E�X���E�B���h�E���ɂ�������J�����ړ�
	if (MouseX_ > 0 && MouseX_ < Screen::Width &&
		MouseY_ > 0 && MouseY_ < Screen::Height)
	{
		if (MouseX_ > prevMouseX_)					//�@�}�E�X���E�ɓ����Ă�����
		{

			// �}�E�X�̈ړ�������x���ϊ��A360 : x = Screen::Width * 2 : MouseX - prevMouseX
			//							   x(Screen::Width * 2) = 360(MouseX - prevMouseX)
			//							   x = (360(MouseX - prevMouseX)) / (Screen::Width * 2)

			PercentAngleByCursorDis_ = (float)((MaxAngle_ * (MouseX_ - prevMouseX_)) / (Screen::Width * 2));

			// PercentAngleByCursor������
			if (!canAngleInit_)
			{
				PercentAngleByCursorDis_ = 0;
				canAngleInit_ = true;
			}

			nowCamAngle_ += PercentAngleByCursorDis_;	// �x��������
		}
		else if (MouseX_ < prevMouseX_)					// �}�E�X�����ɓ����Ă�����
		{
			PercentAngleByCursorDis_ = (float)((360 * (prevMouseX_ - MouseX_)) / (Screen::Width * 2));
			nowCamAngle_ -= PercentAngleByCursorDis_;
		}
	}

	// �J������360�x��1������悤��
	if (nowCamAngle_ <= 0)		  nowCamAngle_ = (float)MaxAngle_ - 1;
	if (nowCamAngle_ >= MaxAngle_) nowCamAngle_ = 1;

	prevMouseX_ = MouseX_;								 // �}�E�X�J�[�\�����W��ۑ�

	vx = 0;												 // x�����ړ����x
	vy = 0;												 // y�����ړ����x
	vz = 0;												 // z�����ړ����x

	MoveSpeed_ *= DecreaseSpeed_;					 // �ړ����x����������
	MoveSpeedLateral_ *= DecreaseSpeed_;

	// ���͂��󂯂Ă̏��� 
	HandleInput();

	// ���i�s�����p�x��X������Z�����̑��x�ɕς���
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


	// ���ۂɈʒu�𓮂���

	MoveX();
	MoveY();
	MoveZ();

	// �J�����ʒu
	Camera::SetPosition
	/* X���W */ (gm.player->x + (camDistanceFromPlayer_ * std::cos(nowCamAngle_ * MyMath::Deg2Rad)),
	/* Y���W */  gm.player->y - camHeightFromTerrain_,
	/* Z���W */  gm.player->z + (camDistanceFromPlayer_ * std::sin(nowCamAngle_ * MyMath::Deg2Rad)));

	//�J�����̓v���C���̕�������
	Camera::LookAt(gm.player->x, gm.player->y + 100, gm.player->z);

	if (AttachCheck_[(int)State::collect])
		PlayAnimation(0.5f, FALSE);
	else if (AttachCheck_[(int)State::run])
		PlayAnimation(0.6f, TRUE);
	else
		PlayAnimation(0.07f, TRUE);
}

// ���̈ړ�����
void Player::MoveX()
{
	// ���Ɉړ�����
	x += vx;

	// �����蔻��̎l���̍��W���擾
	float left = GetLeft();
	float right = GetRight() - 0.01f;
	float back = GetBack();
	float middle = back + collisionDetectionMiddleZ_;
	float forward = GetForward() - 0.01f;

	// ���[���ǂɂ߂肱��ł��邩�H
	if (gm.map->IsWall(left, back) ||		// �ǂ��H
		gm.map->IsWall(left, middle) ||		// �ǂ��H
		gm.map->IsWall(left, forward))		// �ǂ��H
	{
		float wallRight = left - (float)std::fmod(left, gm.map->CellSize) + gm.map->CellSize; // �ǂ̉E�[
		SetLeft(wallRight); // �v���C���[�̍��[��ǂ̉E�[�ɉ��킷
	}
	// �E�[���ǂɂ߂肱��ł��邩�H
	else if (
		gm.map->IsWall(right, back) ||		// �E�オ�ǂ��H
		gm.map->IsWall(right, middle) ||    // �ǂ��H
		gm.map->IsWall(right, forward))		// �E�����ǂ��H
	{
		float wallLeft = right - (float)std::fmod(right, gm.map->CellSize); // �ǂ̍��[
		SetRight(wallLeft); // �v���C���[�̉E�[��ǂ̍��[�ɉ��킷
	}
}

// Z���s�������̈ړ�����
void Player::MoveZ()
{
	// Z���s�������Ɉړ�����
	z += vz;

	// �����蔻��̎l���̍��W���擾
	float left = GetLeft();
	float middle = left + collisionDetectionMiddleX_;
	float right = GetRight() - 0.01f;
	float back = GetBack();
	float forward = GetForward() - 0.01f;

	// ��O�����ǂɂ߂肱��ł��邩�H
	if (gm.map->IsWall(left, back) ||		// �ǂ��H
		gm.map->IsWall(middle, back) ||		// �ǂ��H
		gm.map->IsWall(right, back))		// �ǂ��H
	{
		float wallForward = back - (float)std::fmod(back, gm.map->CellSize) + gm.map->CellSize; // �ǂ̉��s������
		SetBack(wallForward); // �v���C���[�̔w����ǂ̃t�H���[�h�ɉ��킷
	}
	// ���s�������ǂɂ߂肱��ł��邩�H
	else if (
		gm.map->IsWall(left, forward) ||		// �ǂ��H
		gm.map->IsWall(middle, forward) ||		// �ǂ��H
		gm.map->IsWall(right, forward))			// �ǂ��H
	{
		float wallBack = forward - (float)std::fmod(forward, gm.map->CellSize); // �ǂ̎�O��
		SetForward(wallBack); // �v���C���[�̂��ł���ǂ̃o�b�N�ɉ��킷
	}
}


// �c�̈ړ�����
void Player::MoveY()
{
	// �c�Ɉړ�����
	y += vy;
}

// �`�揈��
void Player::Draw()
{
	// �v���C���[���f������]������
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
	AttachCheck_[prevAnimIndex_] = false;			 // �O�񗧂Ă��t���O�̏�����

	MV1DetachAnim(Image::Player, prevAttachIndex_);	 // �A�j���[�V�����̃f�^�b�`

	prevAnimIndex_	 = AnimIndex;						 // ���t���O�����������邽�߂ɕۑ�
	prevAttachIndex_ = AttachIndex_;				 // ���̃A�j�������f�^�b�`���邽�߂ɕۑ�

	/*-----�A�^�b�`����-----*/
	AttachIndex_ = MV1AttachAnim(Image::Player, AnimIndex, -1, FALSE);
	TotalTime_	 = MV1GetAttachAnimTotalTime(Image::Player, AttachIndex_);
	PlayTime_	 = 0.0f;
	MV1SetAttachAnimTime(Image::Player, AttachIndex_, PlayTime_);

	/*---------------*/

	AttachCheck_[AnimIndex] = true;					 // �A�j���[�V�����ɂ���ăt���O�𗧂Ă�	
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

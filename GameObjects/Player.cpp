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

	// �v���C���[���f���̊p�x
	modelAngle_ = -((camera.nowCamAngle_ - 90) * MyMath::Deg2Rad);

	// �J�����ʒu
	Vector3 cameraPos
	{ /* X���W */gm.player->position.x + (camDistanceFromPlayer_ * std::cos(camera.nowCamAngle_ * MyMath::Deg2Rad)),
		/* Y���W */ gm.player->position.y - camHeightFromTerrain_,
		/* Z���W */ gm.player->position.z + (camDistanceFromPlayer_ * std::sin(camera.nowCamAngle_ * MyMath::Deg2Rad)) };
	camera.SetPosition(cameraPos);

	//�J�����̓v���C���̕�������
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
				moveSpeed_ = moveSpeedMax_;      //Max�X�s�[�h�Ŏ~�߂�
			if (!attachCheck_[(int)State::run] && !attachCheck_[(int)State::collect])
				AnimationAttach((int)State::run);
			modelAngle_ = -(camera.nowCamAngle_ * MyMath::Deg2Rad);
		}
		else if (Input::GetButton(PAD_INPUT_6))         // D
		{
			moveSpeed_ += IncreaseSpeed_;
			if (moveSpeed_ < -moveSpeedMax_)
				moveSpeed_ = -moveSpeedMax_;     //Max�X�s�[�h�Ŏ~�߂�
			if (!attachCheck_[(int)State::run] && !attachCheck_[(int)State::collect])
				AnimationAttach((int)State::run);
			modelAngle_ = -((camera.nowCamAngle_ - 180) * MyMath::Deg2Rad);
		}

		if (Input::GetButton(PAD_INPUT_8))              // W
		{
			moveSpeed_ += IncreaseSpeed_;
			if (moveSpeed_ > moveSpeedMax_)
				moveSpeed_ = moveSpeedMax_;             //Max�X�s�[�h�Ŏ~�߂�
			if (!attachCheck_[(int)State::run] && !attachCheck_[(int)State::collect])
				AnimationAttach((int)State::run);
			modelAngle_ = -((camera.nowCamAngle_ - 90) * MyMath::Deg2Rad);
		}
		else if (Input::GetButton(PAD_INPUT_5))         // S
		{
			moveSpeed_ += IncreaseSpeed_;
			if (moveSpeed_ < -moveSpeedMax_)
				moveSpeed_ = -moveSpeedMax_;           //Max�X�s�[�h�Ŏ~�߂�
			if (!attachCheck_[(int)State::run] && !attachCheck_[(int)State::collect])
				AnimationAttach((int)State::run);
			modelAngle_ = -((camera.nowCamAngle_ + 90) * MyMath::Deg2Rad);
		}

		if (Input::GetButton(PAD_INPUT_8) && Input::GetButton(PAD_INPUT_4)) // ���O
		{
			modelAngle_ = -((camera.nowCamAngle_ - 45) * MyMath::Deg2Rad);
		}
		else if (Input::GetButton(PAD_INPUT_8) && Input::GetButton(PAD_INPUT_6)) // �E�O
		{
			modelAngle_ = -((camera.nowCamAngle_ - 135) * MyMath::Deg2Rad);
		}
		else if (Input::GetButton(PAD_INPUT_5) && Input::GetButton(PAD_INPUT_4)) // �����
		{
			modelAngle_ = -((camera.nowCamAngle_ + 45) * MyMath::Deg2Rad);
		}
		else if (Input::GetButton(PAD_INPUT_5) && Input::GetButton(PAD_INPUT_6)) // �E���
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

// �X�V����
void Player::Update()
{
	camera.Move();
	backX = camera.backX;

	velocity = 0;

	moveSpeed_ *= DecreaseSpeed_;                // �ړ����x����������

	// ���͂��󂯂Ă̏��� 
	HandleInput();

	if (modelAngle_ > 0)
		modelAngle_ -= 360.0f * MyMath::Deg2Rad; // �v���C���[�̊p�x�̂���𒼂�

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

	// ���ۂɈʒu�𓮂���
	position += velocity;

	// �J�����ʒu
	Vector3 cameraPos
	{ /* X���W */ gm.player->position.x + (camDistanceFromPlayer_ * std::cos(camera.nowCamAngle_ * MyMath::Deg2Rad)),
	  /* Y���W */ gm.player->position.y - camHeightFromTerrain_,
	  /* Z���W */ gm.player->position.z + (camDistanceFromPlayer_ * std::sin(camera.nowCamAngle_ * MyMath::Deg2Rad)) };
	camera.SetPosition(cameraPos);

	//�J�����̓v���C���̕�������
	Vector3 lookPos{ gm.player->position.x, gm.player->position.y + 100, gm.player->position.z };
	camera.LookAt(lookPos);

	if (attachCheck_[(int)State::collect])
		PlayAnimation(0.5f, FALSE);
	else if (attachCheck_[(int)State::run])
		PlayAnimation(0.6f, TRUE);
	else
		PlayAnimation(0.07f, TRUE);

	// �}�E�X�ʒu�̏�����
	SetMousePoint(Screen::width / 2, Screen::height / 2);
}

// �`�揈��
void Player::Draw()
{
	// �v���C���[���f������]������
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
	attachCheck_[prevAnimIndex_] = false;             // �O�񗧂Ă��t���O�̏�����

	MV1DetachAnim(gm.image.Player, prevAttachIndex_); // �A�j���[�V�����̃f�^�b�`

	prevAnimIndex_   = AnimIndex;                     // ���t���O�����������邽�߂ɕۑ�
	prevAttachIndex_ = attachIndex_;                  // ���̃A�j�������f�^�b�`���邽�߂ɕۑ�

	/*-----�A�^�b�`����-----*/
	attachIndex_ = MV1AttachAnim(gm.image.Player, AnimIndex, -1, FALSE);
	totalTime_   = MV1GetAttachAnimTotalTime(gm.image.Player, attachIndex_);
	playTime_    = 0.0f;
	MV1SetAttachAnimTime(gm.image.Player, attachIndex_, playTime_);

	/*---------------*/

	attachCheck_[AnimIndex] = true; // �A�j���[�V�����ɂ���ăt���O�𗧂Ă�	
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

#include "Camera.h"
#include "MyLib/MyMath.h"

// �J�����𓮂���
void Camera::Move()
{
	GetMousePoint(&mouseX_, &mouseY_);              // �}�E�X�J�[�\�����W�擾

	// �}�E�X���E�B���h�E���ɂ�������J�����ړ�
	if (mouseX_ > 0 && mouseX_ < Screen::width &&
		mouseY_ > 0 && mouseY_ < Screen::height)
	{
		if (mouseX_ > Screen::width / 2)                  //�@�}�E�X���E�ɓ����Ă�����
		{

			// �}�E�X�̈ړ�������x���ϊ��A360 : x = Screen::Width * 1.2f : MouseX - Screen::width / 2
			//                             x(Screen::Width * 1.2f) = 360(MouseX - Screen::width / 2)
			//                             x = (360(MouseX - Screen::width / 2)) / (Screen::Width * 1.2f)

			percentAngleByCursorDis_ = (float)((MaxAngle_ * (mouseX_ - Screen::width / 2)) / (Screen::width * 1.2f));
			percentAngleByCursorDis_BG_ = (float)((MaxAngle_ * (mouseX_ - Screen::width / 2)) / (BackImageWidth / 60));

			// PercentAngleByCursor������
			if (!canAngleInit_)
			{
				percentAngleByCursorDis_ = 0;
				percentAngleByCursorDis_BG_ = 0;
				canAngleInit_ = true;
			}

			nowCamAngle_ += percentAngleByCursorDis_;   // �x��������

			backX += percentAngleByCursorDis_BG_;
			if (backX <= -BackImageWidth + Screen::width)
				backX = 0;
		}
		else                                        // �}�E�X�����ɓ����Ă�����
		{
			percentAngleByCursorDis_ = (float)((MaxAngle_ * (Screen::width / 2 - mouseX_)) / (Screen::width * 1.2f));
			percentAngleByCursorDis_BG_ = (float)((MaxAngle_ * (mouseX_ - Screen::width / 2)) / (BackImageWidth / 60));

			// PercentAngleByCursor������
			if (!canAngleInit_)
			{
				percentAngleByCursorDis_ = 0;
				percentAngleByCursorDis_BG_ = 0;
				canAngleInit_ = true;
			}

			nowCamAngle_ -= percentAngleByCursorDis_;

			backX += percentAngleByCursorDis_BG_;
			if (backX > BackImageWidth)
				backX = 0;
		}
	}

	// �J������360�x��1������悤��
	if (nowCamAngle_ <= 0.0f)             nowCamAngle_ = (float)MaxAngle_ - 1.0f;
	if (nowCamAngle_ >= (float)MaxAngle_) nowCamAngle_ = 1.0f;
}

// �J�����̈ʒu���Z�b�g����ʍ���̃��[���h2D���W�n�Ƃ��ĕۑ�
void Camera::SetPosition(Vector3 v3)
{   // ��ʍ���̃��[���h���W�n�Ƃ��ĕۑ�
	position = v3;
	cameraPos = position.Vec3ToVec(position); // �J�����̈ʒu�̕ۑ�(cameraPos�͓ǂݏo����p)
}

// �w�肳�ꂽ���[���h���W����ʂ̒��S�ɗ���悤�ɁA�J�����̈ʒu��ύX����
void Camera::LookAt(Vector3 v3)
{
	// �J�����̈ʒu�ƌ�����ݒ�
	{
		// �����_�̓^�[�Q�b�g�̍��W���� CAMERA_LOOK_AT_HEIGHT �����������ʒu
		VECTOR TargetPosition = VGet(v3.x, v3.y + cameraLookAtHeight, v3.z);
		// �J�����̈ʒu�̐ݒ�
		VECTOR CameraPosition = position.Vec3ToVec(position);
		// �J�������^�[�Q�b�g�̂ق��������悤�ɂ���
		VECTOR CameraLookAtPosition = TargetPosition;

		// �J�����̐ݒ�ɔ��f����
		SetCameraPositionAndTarget_UpVecY(CameraPosition, CameraLookAtPosition);
		// �J�����ʒu�̕ۑ�(cameraPos�͓ǂݏo����p)
		cameraPos = CameraPosition;
	}
}

int Camera::SetCameraPositionAndTarget_UpVecY(VECTOR Position, VECTOR Target)
{
	// �E��E����n��Y�����̕����ɏ]�����W��ϊ�
	VECTOR Position_COVERT_XYZ = VGet(Position.x, Position.y, Position.z);
	VECTOR Target_COVERT_XYZ = VGet(Target.x, Target.y, Target.z);
	return DxLib::SetCameraPositionAndTarget_UpVecY(Position_COVERT_XYZ, Target_COVERT_XYZ);
}

/// <summary>
/// �l�p�`�i�g���̂݁j��`�悷��
/// </summary>
/// <param name="left">���[</param>
/// <param name="top">��[</param>
/// <param name="right">�E�[</param>
/// <param name="bottom">���[</param>
/// <param name="color">�F</param>
void Camera::DrawLineBox(float left, float top, float right, float bottom, unsigned int color, float leftTopZ, float rightBottomZ)
{
	if (leftTopZ == 0 && rightBottomZ == 0)
	{   // 2D��
		DrawBox(
			(int)(left - position.x + 0.5f),
			(int)(top - position.y + 0.5f),
			(int)(right - position.x + 0.5f),
			(int)(bottom - position.y + 0.5f),
			color,
			FALSE);
	}
	else
	{   // 3D��
		DrawCube3D
		(VGet(left, top, leftTopZ),
			VGet(right, bottom, rightBottomZ),
			color, color, FALSE);
	}
}
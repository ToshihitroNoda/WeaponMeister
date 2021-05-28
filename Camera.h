#ifndef CAMERA_H_
#define CAMERA_H_

#include <DxLib.h>
#include "MyMath.h"
#include "Screen.h"

class Camera
{
public:
	// �J�����̈ʒu�B
	// ��ʍ���̃��[���h���W��\���B
	float x = 0;
	float y = 0;
	float z = 0;

	float cameraLookAtHeight = 0;

	VECTOR cameraPos = DxLib::VGet(Screen::width / 2, Screen::height / 2, -100.0f);

	Camera() = default;

	~Camera() = default;

	// �J�����̈ʒu���Z�b�g����ʍ���̃��[���h2D���W�n�Ƃ��ĕۑ�
	void SetPosition(float worldX, float worldY, float worldZ)
	{   // ��ʍ���̃��[���h���W�n�Ƃ��ĕۑ�
		x = worldX;
		y = worldY;
		z = worldZ;
		cameraPos = VGet(x, y, z); // �J�����̈ʒu�̕ۑ�(cameraPos�͓ǂݏo����p)
	}

	// �w�肳�ꂽ���[���h���W����ʂ̒��S�ɗ���悤�ɁA�J�����̈ʒu��ύX����
	void LookAt(float targetX, float targetY, float targetZ)
	{
		// �J�����̈ʒu�ƌ�����ݒ�
		{
			// �����_�̓^�[�Q�b�g�̍��W���� CAMERA_LOOK_AT_HEIGHT �����������ʒu
			VECTOR TargetPosition = VGet(targetX, targetY + cameraLookAtHeight, targetZ);
			// �J�����̈ʒu�̐ݒ�
			VECTOR CameraPosition = VGet(x, y, z);
			// �J�������^�[�Q�b�g�̂ق��������悤�ɂ���
			VECTOR CameraLookAtPosition = TargetPosition;

			// �J�����̐ݒ�ɔ��f����
			SetCameraPositionAndTarget_UpVecY(CameraPosition, CameraLookAtPosition);
			// �J�����ʒu�̕ۑ�(cameraPos�͓ǂݏo����p)
			cameraPos = CameraPosition;
		}
	}

	int SetCameraPositionAndTarget_UpVecY(VECTOR Position, VECTOR Target)
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
	void DrawLineBox(float left, float top, float right, float bottom, unsigned int color, float leftTopZ = 0, float rightBottomZ = 0)
	{
		if (leftTopZ == 0 && rightBottomZ == 0)
		{   // 2D��
			DrawBox(
				(int)(left - x + 0.5f),
				(int)(top - y + 0.5f),
				(int)(right - x + 0.5f),
				(int)(bottom - y + 0.5f),
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
};

#endif
#ifndef CAMERA_H_
#define CAMERA_H_

#include <DxLib.h>
#include "Screen.h"
#include "Vector3.h"

class Camera
{
public:
	// �J�����̈ʒu�B
	// ��ʍ���̃��[���h���W��\���B
	Vector3 position{ 0.0f, 0.0f, 0.0f };

	float cameraLookAtHeight = 0.0f;

	VECTOR cameraPos = DxLib::VGet(Screen::width / 2, Screen::height / 2, -100.0f);

	Camera() = default;

	~Camera() = default;

	// �J�����𓮂���
	void Move();

	// �J�����̈ʒu���Z�b�g����ʍ���̃��[���h2D���W�n�Ƃ��ĕۑ�
	void SetPosition(Vector3 v3);

	// �w�肳�ꂽ���[���h���W����ʂ̒��S�ɗ���悤�ɁA�J�����̈ʒu��ύX����
	void LookAt(Vector3 v3);

	int SetCameraPositionAndTarget_UpVecY(VECTOR Position, VECTOR Target);

	/// <summary>
	/// �l�p�`�i�g���̂݁j��`�悷��
	/// </summary>
	/// <param name="left">���[</param>
	/// <param name="top">��[</param>
	/// <param name="right">�E�[</param>
	/// <param name="bottom">���[</param>
	/// <param name="color">�F</param>
	void DrawLineBox(float left, float top, float right, float bottom, unsigned int color, float leftTopZ = 0, float rightBottomZ = 0);

	int backX = 0;
	float nowCamAngle_ = 0.0f;

private:
	int mouseX_ = 0;
	int mouseY_ = 0;

	float percentAngleByCursorDis_    = 0.0f; // �}�E�X�̈ړ������ɉ����Ċp�x�ς���
	float percentAngleByCursorDis_BG_ = 0.0f;

	bool canAngleInit_ = false;

	const int MaxAngle_      = 360;
	const int BackImageWidth = 8192;
};

#endif
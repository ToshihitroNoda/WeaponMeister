#include "Camera.h"

float Camera::x = 0;
float Camera::y = 0;
float Camera::z = 0;

// �|���S���̃L�����͏�ɃJ���������ɖʂ�������悤�ɂ��邽�߂̊p�x
float Camera::anglePlaneChara		= 0;
float Camera::anglePlaneCharaRotate = 0;

float Camera::cameraLookAtHeight	= 0;

VECTOR Camera::cameraPos = DxLib::VGet(Screen::Width / 2, Screen::Height / 2, -100.0f);
#ifndef MAPTERRAIN_H_
#define MAPTERRAIN_H_

#include <DxLib.h>
#include "../GameManager.h"
#include "GameObject.h"

class MapTerrain : public GameObject
{
public:
	GameManager& gm = GameManager::GetInstance();

	MapTerrain(Vector3 position, std::string TerrainName)
	{
		this->position = position;
		tag = TerrainName;

		imageWidth  = 32;   // �摜�̉��s�N�Z����
		imageHeight = 32;   // �摜�̏c�s�N�Z����
		imageLength = 32;   // �摜��Z�����̌��݂̃s�N�Z����
		hitboxOffsetLeft    = -10;  // �����蔻��̍��[�̃I�t�Z�b�g
		hitboxOffsetRight   = -10;  // �����蔻��̉E�[�̃I�t�Z�b�g
		hitboxOffsetTop     = 0;    // �����蔻��̏�[�̃I�t�Z�b�g
		hitboxOffsetBottom  = 0;    // �����蔻��̉��[�̃I�t�Z�b�g
		hitboxOffsetForward = -10;  // �����蔻��̉������̃I�t�Z�b�g
		hitboxOffsetBack    = -10;  // �����蔻��̎�O�����̃I�t�Z�b�g
	};

	~MapTerrain() = default;

	void Update() override {};
	void Draw() override;
	void DrawModel(int MV1Handle);

};

#endif

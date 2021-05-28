#ifndef MAPTERRAIN_H_
#define MAPTERRAIN_H_

#include <DxLib.h>
#include "GameManager.h"
#include "GameObject.h"

class MapTerrain : public GameObject
{
public:
	GameManager& gm = GameManager::GetInstance();

	MapTerrain(float x, float y, float z, std::string TerrainName)
	{
		this->x = x;
		this->y = y;
		this->z = z;
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

	void Init();
	void Update();
	void Draw();
	void OnCollision(std::shared_ptr<GameObject> other);
	void DrawModel(int MV1Handle);

};

#endif

#ifndef MAPTERRAIN_H_
#define MAPTERRAIN_H_

#include <DxLib.h>
#include "GameManager.h"
#include "GameObject.h"
#include "Image.h"

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

		imageWidth = 32;	// �摜�̉��s�N�Z����
		imageHeight = 32;	// �摜�̏c�s�N�Z����
		imageLength = 32;	// �摜��Z�����̌��݂̃s�N�Z����
		hitboxOffsetLeft = -10;	// �����蔻��̍��[�̃I�t�Z�b�g
		hitboxOffsetRight = -10;	// �����蔻��̉E�[�̃I�t�Z�b�g
		hitboxOffsetTop = 0;	// �����蔻��̏�[�̃I�t�Z�b�g
		hitboxOffsetBottom = 0;	// �����蔻��̉��[�̃I�t�Z�b�g
		hitboxOffsetForward = -10;	// �����蔻��̉������̃I�t�Z�b�g
		hitboxOffsetBack = -10;	// �����蔻��̎�O�����̃I�t�Z�b�g
	};

	~MapTerrain() {};

	void Init() {};
	void Update() {};
	void Draw()
	{
		if (tag == "Grass")
		{
			DrawModel(Image::Terrain_Block_1);
		}
		if (tag == "Sand")
		{
			DrawModel(Image::Terrain_Block_2);
		}
		if (tag == "Stone")
		{
			DrawModel(Image::Terrain_Block_3);
		}
		if (tag == "Volcano")
		{
			DrawModel(Image::Terrain_Block_4);
		}
	};
	void OnCollision(std::shared_ptr<GameObject> other) {};
	void DrawModel(int MV1Handle)
	{
		MV1SetPosition(MV1Handle, VGet(x, y, z));
		MV1SetScale(MV1Handle, VGet(0.162f, 0.25f, 0.162f));
		MV1DrawModel(MV1Handle);
	}

};

#endif

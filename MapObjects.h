#ifndef MAPOBJECTS_H_
#define MAPOBJECTS_H_

#include <DxLib.h>
#include "GameManager.h"
#include "GameObject.h"

class MapObjects : public GameObject
{
public:
	GameManager& gm = GameManager::GetInstance();

	MapObjects(float x, float y, float z, float Width, float Length, std::string ObjectsName)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		tag = ObjectsName;

		imageWidth          = Width * 0.5f;   // �摜�̉��s�N�Z����
		imageHeight         = 32;             // �摜�̏c�s�N�Z����
		imageLength         = Length * 0.5f;  // �摜��Z�����̌��݂̃s�N�Z����
		hitboxOffsetLeft    = 0;              // �����蔻��̍��[�̃I�t�Z�b�g
		hitboxOffsetRight   = 0;              // �����蔻��̉E�[�̃I�t�Z�b�g
		hitboxOffsetTop     = 0;              // �����蔻��̏�[�̃I�t�Z�b�g
		hitboxOffsetBottom  = 0;              // �����蔻��̉��[�̃I�t�Z�b�g
		hitboxOffsetForward = 0;              // �����蔻��̉������̃I�t�Z�b�g
		hitboxOffsetBack    = 0;              // �����蔻��̎�O�����̃I�t�Z�b�g

		if (isRotaGraph == true)
		{   // �摜�̒��S���N�_�ɕ`���ꍇ�̂���
			rotaGraphShiftX = (float)imageWidth / 2;
			rotaGraphShiftY = (float)imageHeight / 2;
			rotaGraphShiftZ = (float)imageLength / 2;
		}
	};

	~MapObjects() = default;

	void Init();
	void Update();
	void Draw();
	void OnCollision(std::shared_ptr<GameObject> other);
	void DrawModel(int MV1Handle);

	std::vector<int> objectModelHandles
	{ gm.image.Spruce_1,       gm.image.Spruce_2,       gm.image.Spruce_3,     gm.image.Trunk,        gm.image.Branch_1,     gm.image.Branch_2,
	  gm.image.Branch_3,       gm.image.Branch_4,       gm.image.Branch_group, gm.image.Bush_1,       gm.image.Bush_2,       gm.image.Bush_3,
	  gm.image.Bush_4,         gm.image.Bush_large_1,   gm.image.Bush_large_2, gm.image.Cliff_rock_1, gm.image.Cliff_rock_2, gm.image.Cliff_rock_3,
	  gm.image.Cliff_rock_4,   gm.image.Cliff_rock_5,   gm.image.Rock_1,       gm.image.Rock_2,       gm.image.Rock_3,       gm.image.Rock_4,
	  gm.image.Rock_5,         gm.image.Crystal_1,      gm.image.Crystal_2,    gm.image.Crystal_3,    gm.image.Crystal_4,    gm.image.Crystal_5
	};

};

#endif

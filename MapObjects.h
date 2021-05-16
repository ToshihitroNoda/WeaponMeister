#ifndef MAPOBJECTS_H_
#define MAPOBJECTS_H_

#include <DxLib.h>
#include "GameManager.h"
#include "GameObject.h"
#include "Image.h"

class MapObjects : public GameObject
{
public:
	GameManager& gm = GameManager::GetInstance();

	MapObjects(float x, float y, float z, std::string ObjectsName)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		tag = ObjectsName;

		imageWidth = 32;	// �摜�̉��s�N�Z����
		imageHeight = 32;	// �摜�̏c�s�N�Z����
		imageLength = 32;	// �摜��Z�����̌��݂̃s�N�Z����
		hitboxOffsetLeft = -10;	// �����蔻��̍��[�̃I�t�Z�b�g
		hitboxOffsetRight = -10;	// �����蔻��̉E�[�̃I�t�Z�b�g
		hitboxOffsetTop = 0;	// �����蔻��̏�[�̃I�t�Z�b�g
		hitboxOffsetBottom = 0;	// �����蔻��̉��[�̃I�t�Z�b�g
		hitboxOffsetForward = -10;	// �����蔻��̉������̃I�t�Z�b�g
		hitboxOffsetBack = -10;	// �����蔻��̎�O�����̃I�t�Z�b�g

		if (isRotaGraph == true)
		{   // �摜�̒��S���N�_�ɕ`���ꍇ�̂���
			rotaGraphShiftX = (float)imageWidth / 2;
			rotaGraphShiftY = (float)imageHeight / 2;
			rotaGraphShiftZ = (float)imageLength / 2;
		}
	};

	~MapObjects() {};

	void Init();
	void Update();
	void Draw();
	void OnCollision(std::shared_ptr<GameObject> other);
	void DrawModel(int MV1Handle);

private:
	std::vector<int> ObjectModelHandles
	{ Image::Spruce_1,Image::Spruce_2,Image::Spruce_3,Image::Trunk,Image::Branch_1, Image::Branch_2, Image::Branch_3, Image::Branch_4, Image::Branch_group,
	  Image::Bush_1, Image::Bush_2, Image::Bush_3, Image::Bush_4, Image::Bush_large_1, Image::Bush_large_2,
	  Image::Cliff_rock_1, Image::Cliff_rock_2, Image::Cliff_rock_2, Image::Cliff_rock_3, Image::Cliff_rock_4, Image::Cliff_rock_5,
	  Image::Rock_1, Image::Rock_2, Image::Rock_3, Image::Rock_4, Image::Rock_5,
	  Image::Crystal_1,Image::Crystal_2,Image::Crystal_3,Image::Crystal_4,Image::Crystal_5
	};

};

#endif

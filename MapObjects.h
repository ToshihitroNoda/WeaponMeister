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

	void Init() {};
	void Update() {};
	void Draw() 
	{
		if (tag == "Spruce_1")
		{
			DrawModel(Image::Spruce_1);
		}
	};
	void OnCollision(std::shared_ptr<GameObject> other) {};
	void DrawModel(int MV1Handle)
	{
		MV1SetPosition(MV1Handle, VGet(x, y, z));
		MV1SetScale(MV1Handle, VGet(0.5f, 0.5f, 0.5f));
		MV1DrawModel(MV1Handle);
	}

};

#endif

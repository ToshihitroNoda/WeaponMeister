#ifndef FIELDITEM_H_
#define FIELDITEM_H_

#include "GameObject.h"
#include "../GameManager.h"

class FieldItem : public GameObject
{
public:
	GameManager& gm = GameManager::GetInstance();

	FieldItem() = default;

	FieldItem(Vector3 position)
	{
		this->position = position;
		tag = "FieldItem";

		imageWidth          = 32;   // �摜�̉��s�N�Z����
		imageHeight         = 32;   // �摜�̏c�s�N�Z����
		imageLength         = 32;   // �摜��Z�����̌��݂̃s�N�Z����
		hitboxOffsetLeft    = -30;  // �����蔻��̍��[�̃I�t�Z�b�g
		hitboxOffsetRight   = -30;  // �����蔻��̉E�[�̃I�t�Z�b�g
		hitboxOffsetTop     = 0;    // �����蔻��̏�[�̃I�t�Z�b�g
		hitboxOffsetBottom  = 0;    // �����蔻��̉��[�̃I�t�Z�b�g
		hitboxOffsetForward = -30;  // �����蔻��̉������̃I�t�Z�b�g
		hitboxOffsetBack    = -30;  // �����蔻��̎�O�����̃I�t�Z�b�g

		if (isRotaGraph == true)
		{   // �摜�̒��S���N�_�ɕ`���ꍇ�̂���
			rotaGraphShift = { (float)imageWidth / 2, (float)imageHeight / 2, (float)imageLength / 2 };
		}
	};

	~FieldItem() = default;

	void Init();
	void Update();
	void Draw();
	void OnCollision(std::shared_ptr<GameObject> other);

	bool isOnCollisionPlayer = false;
};

#endif 

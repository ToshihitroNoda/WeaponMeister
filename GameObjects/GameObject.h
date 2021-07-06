#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string> 
#include <memory> 
#include "../Camera.h" 
#include "../Vector3.h"

// �Q�[����ɕ\������镨�̂̊��N���X�B
class GameObject
{
public:
	Camera camera;

	// �R���X�g���N�^
	GameObject() = default;

	// ���z�f�X�g���N�^
	virtual ~GameObject() = default;

	// �X�V����
	virtual void Update() = 0;

	// �`�揈��
	virtual void Draw()   = 0;

	// �Փ˂����Ƃ��̊֐�
	virtual void OnCollision(std::shared_ptr<GameObject> other) {};

	// �����蔻���`��i�f�o�b�O�p�j
	virtual void DrawHitBox()
	{
		// �l�pBox��`��
		camera.DrawLineBox
		(GetLeft(), 0,
		 GetRight(), 0,
		 GetColor(255, 0, 0),
		 GetBack(), GetForward());
	}

	// �����蔻��̍��[���擾
	virtual float GetLeft()
	{
		return (position.x - rotaGraphShift.x) + hitboxOffsetLeft;
	}

	// �E�[���擾
	virtual float GetRight()
	{
		return (position.x - rotaGraphShift.x) + imageWidth - hitboxOffsetRight;
	}

	// ��[���擾
	virtual float GetTop()
	{
		return position.y + hitboxOffsetTop;
	}

	// ���[���擾����
	virtual float GetBottom()
	{
		return position.y + imageHeight - hitboxOffsetBottom;
	}

	// �����蔻���Z��O�����擾
	virtual float GetBack()
	{
		return (position.z - rotaGraphShift.z) + hitboxOffsetBack;
	}

	// Z���s�������ʒu���擾
	virtual float GetForward()
	{
		return (position.z - rotaGraphShift.z) + imageLength - hitboxOffsetForward;
	}

	std::string tag = "";
	bool isDead = false;            // ���񂾁i�폜�Ώہj�t���O

protected:
	Vector3 position{ 0.0f, 0.0f, 0.0f }; // ���W
	Vector3 velocity{ 0.0f, 0.0f, 0.0f }; // ���x

	int imageWidth          = 0;    // �摜�̉��s�N�Z����
	int imageHeight         = 0;    // �摜�̏c�s�N�Z����
	int imageLength         = 0;    // �摜��Z�����̌��݂̃s�N�Z����
	int hitboxOffsetLeft    = 0;    // �����蔻��̍��[�̃I�t�Z�b�g
	int hitboxOffsetRight   = 0;    // �����蔻��̉E�[�̃I�t�Z�b�g
	int hitboxOffsetTop     = 0;    // �����蔻��̏�[�̃I�t�Z�b�g
	int hitboxOffsetBottom  = 0;    // �����蔻��̉��[�̃I�t�Z�b�g
	int hitboxOffsetForward = 0;    // �����蔻��̉������̃I�t�Z�b�g
	int hitboxOffsetBack    = 0;    // �����蔻��̎�O�����̃I�t�Z�b�g

	bool isRotaGraph = true;        // �摜�̒��S���N�_�ɕ`�����H

	// �摜�̒��S���N�_�ɕ`���ꍇ�̂���
	Vector3 rotaGraphShift{ 0.0f, 0.0f, 0.0f };

	Vector3 prevPosition{ 0.0f, 0.0f, 0.0f };

	float prevLeft    = 0;          // 1�t���[���O�̍��[
	float prevRight   = 0;          // 1�t���[���O�̉E�[
	float prevTop     = 0;          // 1�t���[���O�̏�[
	float prevBottom  = 0;          // 1�t���[���O�̉��[ 
	float prevForward = 0;          // 1�t���[���O�̑O��
	float prevBack    = 0;          // 1�t���[���O�̌�� 

	// ���[���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
	virtual void SetLeft(float left)
	{
		position.x = left - hitboxOffsetLeft + rotaGraphShift.x;
	}

	// �E�[���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
	virtual void SetRight(float right)
	{
		position.x = right + hitboxOffsetRight - imageWidth + rotaGraphShift.x;
	}

	// ��[���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
	virtual void SetTop(float top)
	{
		position.y = top - hitboxOffsetTop;
	}

	// ���[���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
	virtual void SetBottom(float bottom)
	{
		position.y = bottom + hitboxOffsetBottom - imageHeight;
	}

	// Z��O�����w�肷�邱�Ƃɂ��ʒu��ݒ肷��
	virtual void SetBack(float back)
	{
		position.z = back - hitboxOffsetBack + rotaGraphShift.z;
	}

	// Z���s�������ʒu���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
	virtual void SetForward(float forward)
	{
		position.z = forward + hitboxOffsetForward - imageLength + rotaGraphShift.z;
	}

	// 1�t���[���O����̈ړ��ʁix�����j
	virtual float GetDeltaX()
	{
		return position.x - prevPosition.x;
	}

	// 1�t���[���O����̈ړ��ʁiy�����j
	virtual float GetDeltaY()
	{
		return position.y - prevPosition.y;
	}

	// 1�t���[���O����̈ړ��ʁiz�����j
	virtual float GetDeltaZ()
	{
		return position.z - prevPosition.z;
	}


	// 1�t���[���O�̍��[���擾����
	virtual float GetPrevLeft()
	{
		return prevLeft;
	}

	// 1�t���[���O�̉E�[���擾����
	virtual float GetPrevRight()
	{
		return prevRight;
	}

	// 1�t���[���O�̏�[���擾����
	virtual float GetPrevTop()
	{
		return prevTop;
	}

	// 1�t���[���O�̉��[���擾����
	virtual float GetPrevBottom()
	{
		return prevBottom;
	}

	// 1�t���[���O�̑O�����擾����
	virtual float GetPrevForward()
	{
		return prevForward;
	}

	// 1�t���[���O�̌�����擾����
	virtual float GetPrevBack()
	{
		return prevBack;
	}

	// 1�t���[���O�̏ꏊ�Ɠ����蔻����L������
	virtual void StorePostionAndHitBox()
	{
		prevPosition.x = position.x;
		prevPosition.y = position.y;
		prevPosition.z = position.z;
		prevLeft    = GetLeft();
		prevRight   = GetRight();
		prevTop     = GetTop();
		prevBottom  = GetBottom();
		prevForward = GetForward();
		prevBack    = GetBack();
	}
};

#endif
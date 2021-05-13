#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string> 
#include <memory> 
#include "Camera.h" 

// �Q�[����ɕ\������镨�̂̊��N���X�B
class GameObject
{
public:
    std::string tag = "";
    float x  = 0;                   // x���W
    float y  = 0;                   // y���W
    float z  = 0;                   // z���W
    float vx = 0;                   // x�����̑��x
    float vy = 0;                   // y�����̑��x
    float vz = 0;                   // z�����̑��x

    bool isDead = false;            // ���񂾁i�폜�Ώہj�t���O

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
    float rotaGraphShiftX = 0.0;
    float rotaGraphShiftY = 0.0;
    float rotaGraphShiftZ = 0.0;

    // �_�ɏ��n�̂��߂�1�t���[���O�ϐ��Q
    float prevX = 0;                // 1�t���[���O��x���W
    float prevY = 0;                // 1�t���[���O��y���W
    float prevZ = 0;                // 1�t���[���O��z���W

    float prevLeft    = 0;          // 1�t���[���O�̍��[
    float prevRight   = 0;          // 1�t���[���O�̉E�[
    float prevTop     = 0;          // 1�t���[���O�̏�[
    float prevBottom  = 0;          // 1�t���[���O�̉��[ 
    float prevForward = 0;          // 1�t���[���O�̑O��
    float prevBack    = 0;          // 1�t���[���O�̌�� 

    // �R���X�g���N�^
    GameObject() = default;

    // ���z�f�X�g���N�^
    virtual ~GameObject() = default;

    // �����蔻��̍��[���擾
    virtual float GetLeft()
    {
        return (x - rotaGraphShiftX) + hitboxOffsetLeft;
    }

    // ���[���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
    virtual void SetLeft(float left)
    {
        x = left - hitboxOffsetLeft + rotaGraphShiftX;
    }

    // �E�[���擾
    virtual float GetRight()
    {
        return (x - rotaGraphShiftX) + imageWidth - hitboxOffsetRight;
    }

    // �E�[���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
    virtual void SetRight(float right)
    {
        x = right + hitboxOffsetRight - imageWidth + rotaGraphShiftX;
    }

    // ��[���擾
    virtual float GetTop()
    {
        return y + hitboxOffsetTop;
    }

    // ��[���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
    virtual void SetTop(float top)
    {
        y = top - hitboxOffsetTop;
    }

    // ���[���擾����
    virtual float GetBottom()
    {
        return y + imageHeight - hitboxOffsetBottom;
    }

    // ���[���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
    virtual void SetBottom(float bottom)
    {
        y = bottom + hitboxOffsetBottom - imageHeight;
    }

    // �����蔻���Z��O�����擾
    virtual float GetBack()
    {
        return (z - rotaGraphShiftZ) + hitboxOffsetBack;
    }

    // Z��O�����w�肷�邱�Ƃɂ��ʒu��ݒ肷��
    virtual void SetBack(float back)
    {
        z = back - hitboxOffsetBack + rotaGraphShiftZ;
    }

    // Z���s�������ʒu���擾
    virtual float GetForward()
    {
        return (z - rotaGraphShiftZ) + imageLength - hitboxOffsetForward;
    }

    // Z���s�������ʒu���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
    virtual void SetForward(float forward)
    {
        z = forward + hitboxOffsetForward - imageLength + rotaGraphShiftZ;
    }

    // �_�ɏ��n�̂��߂�1�t���[���O�����֐��Q
    // 1�t���[���O����̈ړ��ʁix�����j
    virtual float GetDeltaX()
    {
        return x - prevX;
    }

    // 1�t���[���O����̈ړ��ʁiy�����j
    virtual float GetDeltaY()
    {
        return y - prevY;
    }

    // 1�t���[���O����̈ړ��ʁiz�����j
    virtual float GetDeltaZ()
    {
        return z - prevZ;
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
        prevX       = x;
        prevY       = y;
        prevZ       = z;
        prevLeft    = GetLeft();
        prevRight   = GetRight();
        prevTop     = GetTop();
        prevBottom  = GetBottom();
        prevForward = GetForward();
        prevBack    = GetBack();
    }

    // �X�V����
    virtual void Update() = 0; 

    // �`�揈��
    virtual void Draw() = 0;

    // �Փ˂����Ƃ��̊֐�
    virtual void OnCollision(std::shared_ptr<GameObject> other) {};

    // �����蔻���`��i�f�o�b�O�p�j
    virtual void DrawHitBox()
    {

        // �l�pBox��`��
        Camera::DrawLineBox
            (GetLeft(), 0,
            GetRight(), 0,
            GetColor(255, 0, 0),
            GetBack(), GetForward());
    }
};

#endif
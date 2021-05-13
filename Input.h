#ifndef INPUT_H_
#define INPUT_H_

#include "DxLib.h"

// ���̓N���X
class Input
{
public:
    static int prevState; // 1�t���[���O�̏�
    static int currentState; // ���݂̏��

    // �������B�ŏ���1�񂾂��Ă�ł��������B
    static void Init();

    // �ŏ��̓��͏󋵂ɍX�V���鏈���B
    // ���t���[���̍ŏ��Ɂi�Q�[���̏�������Ɂj�ǂ�ł��������B
    static void Update();

    // �{�^����������Ă��邩�H
    static bool GetButton(int buttonId);

    // �{�^���������ꂽ�u�Ԃ��H
    static bool GetButtonDown(int buttonId);

    // �{�^���������ꂽ�u�Ԃ��H
    static bool GetButtonUp(int buttonId);
};

#endif // !INPUT_H_


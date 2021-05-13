#include "Input.h"

int Input::prevState{ 0 };
int Input::currentState{ 0 };

void Input::Init()
{
    prevState = 0;
    currentState = 0;
}
void Input::Update()
{
    prevState = currentState;

    currentState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
}
bool Input::GetButton(int buttonId)
{
    // ���{�^����������Ă��邩�ǂ�����ԋp
    return (currentState & buttonId) != 0;
}
bool Input::GetButtonDown(int buttonId)
{
    // ���͉�����Ă��āA����1�t���[���O�͉�����Ă��Ȃ��ꍇ��true��ԋp
    return ((currentState & buttonId) & ~(prevState & buttonId)) != 0;
}
bool Input::GetButtonUp(int buttonId)
{
    // 1�t���[���O�͉�����Ă��āA�����͉�����Ă��Ȃ��ꍇ��true��ԋp
    return ((prevState & buttonId) & ~(currentState & buttonId)) != 0;
}
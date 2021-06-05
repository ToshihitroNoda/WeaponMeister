#include "Input.h"

int Input::prevState{ 0 };
int Input::currentState{ 0 };
int Input::prevKeyState{ 0 };
int Input::currentKeyState{ 0 };

void Input::Init()
{
    prevState = 0;
    currentState = 0;
    prevKeyState = 0;
    currentKeyState = 0;
}
void Input::Update()
{
    prevState = currentState;
    currentState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    prevKeyState = currentKeyState;
    currentKeyState = CheckHitKeyAll();
}
bool Input::GetButton(int buttonId)
{
    // 今ボタンが押されているかどうかを返却
    return (currentState & buttonId) != 0;
}
bool Input::GetButtonDown(int buttonId)
{
    // 今は押されていて、かつ1フレーム前は押されていない場合はtrueを返却
    return ((currentState & buttonId) & ~(prevState & buttonId)) != 0;
}
bool Input::GetButtonUp(int buttonId)
{
    // 1フレーム前は押されていて、かつ今は押されていない場合はtrueを返却
    return ((prevState & buttonId) & ~(currentState & buttonId)) != 0;
}

bool Input::GetKey(int keyId)
{
    return CheckHitKey(keyId);
}

bool Input::GetKeyDown(int keyId)
{
    if (prevKeyState != 0) return false;
    return CheckHitKey(keyId);
}
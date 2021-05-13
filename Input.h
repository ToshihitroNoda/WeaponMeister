#ifndef INPUT_H_
#define INPUT_H_

#include "DxLib.h"

// 入力クラス
class Input
{
public:
    static int prevState; // 1フレーム前の状況
    static int currentState; // 現在の状態

    // 初期化。最初に1回だけ呼んでください。
    static void Init();

    // 最初の入力状況に更新する処理。
    // 毎フレームの最初に（ゲームの処理より先に）読んでください。
    static void Update();

    // ボタンが押されているか？
    static bool GetButton(int buttonId);

    // ボタンが押された瞬間か？
    static bool GetButtonDown(int buttonId);

    // ボタンが離された瞬間か？
    static bool GetButtonUp(int buttonId);
};

#endif // !INPUT_H_


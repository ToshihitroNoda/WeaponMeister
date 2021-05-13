#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string> 
#include <memory> 
#include "Camera.h" 

// ゲーム上に表示される物体の基底クラス。
class GameObject
{
public:
    std::string tag = "";
    float x  = 0;                   // x座標
    float y  = 0;                   // y座標
    float z  = 0;                   // z座標
    float vx = 0;                   // x方向の速度
    float vy = 0;                   // y方向の速度
    float vz = 0;                   // z方向の速度

    bool isDead = false;            // 死んだ（削除対象）フラグ

    int imageWidth          = 0;    // 画像の横ピクセル数
    int imageHeight         = 0;    // 画像の縦ピクセル数
    int imageLength         = 0;    // 画像のZ方向の厚みのピクセル数
    int hitboxOffsetLeft    = 0;    // 当たり判定の左端のオフセット
    int hitboxOffsetRight   = 0;    // 当たり判定の右端のオフセット
    int hitboxOffsetTop     = 0;    // 当たり判定の上端のオフセット
    int hitboxOffsetBottom  = 0;    // 当たり判定の下端のオフセット
    int hitboxOffsetForward = 0;    // 当たり判定の奥方向のオフセット
    int hitboxOffsetBack    = 0;    // 当たり判定の手前方向のオフセット

    bool isRotaGraph = true;        // 画像の中心を起点に描くか？

    // 画像の中心を起点に描く場合のずれ
    float rotaGraphShiftX = 0.0;
    float rotaGraphShiftY = 0.0;
    float rotaGraphShiftZ = 0.0;

    // 雲に乗る系のための1フレーム前変数群
    float prevX = 0;                // 1フレーム前のx座標
    float prevY = 0;                // 1フレーム前のy座標
    float prevZ = 0;                // 1フレーム前のz座標

    float prevLeft    = 0;          // 1フレーム前の左端
    float prevRight   = 0;          // 1フレーム前の右端
    float prevTop     = 0;          // 1フレーム前の上端
    float prevBottom  = 0;          // 1フレーム前の下端 
    float prevForward = 0;          // 1フレーム前の前方
    float prevBack    = 0;          // 1フレーム前の後方 

    // コンストラクタ
    GameObject() = default;

    // 仮想デストラクタ
    virtual ~GameObject() = default;

    // 当たり判定の左端を取得
    virtual float GetLeft()
    {
        return (x - rotaGraphShiftX) + hitboxOffsetLeft;
    }

    // 左端を指定することにより位置を設定する
    virtual void SetLeft(float left)
    {
        x = left - hitboxOffsetLeft + rotaGraphShiftX;
    }

    // 右端を取得
    virtual float GetRight()
    {
        return (x - rotaGraphShiftX) + imageWidth - hitboxOffsetRight;
    }

    // 右端を指定することにより位置を設定する
    virtual void SetRight(float right)
    {
        x = right + hitboxOffsetRight - imageWidth + rotaGraphShiftX;
    }

    // 上端を取得
    virtual float GetTop()
    {
        return y + hitboxOffsetTop;
    }

    // 上端を指定することにより位置を設定する
    virtual void SetTop(float top)
    {
        y = top - hitboxOffsetTop;
    }

    // 下端を取得する
    virtual float GetBottom()
    {
        return y + imageHeight - hitboxOffsetBottom;
    }

    // 下端を指定することにより位置を設定する
    virtual void SetBottom(float bottom)
    {
        y = bottom + hitboxOffsetBottom - imageHeight;
    }

    // 当たり判定のZ手前側を取得
    virtual float GetBack()
    {
        return (z - rotaGraphShiftZ) + hitboxOffsetBack;
    }

    // Z手前側を指定することにより位置を設定する
    virtual void SetBack(float back)
    {
        z = back - hitboxOffsetBack + rotaGraphShiftZ;
    }

    // Z奥行き方向位置を取得
    virtual float GetForward()
    {
        return (z - rotaGraphShiftZ) + imageLength - hitboxOffsetForward;
    }

    // Z奥行き方向位置を指定することにより位置を設定する
    virtual void SetForward(float forward)
    {
        z = forward + hitboxOffsetForward - imageLength + rotaGraphShiftZ;
    }

    // 雲に乗る系のための1フレーム前処理関数群
    // 1フレーム前からの移動量（x方向）
    virtual float GetDeltaX()
    {
        return x - prevX;
    }

    // 1フレーム前からの移動量（y方向）
    virtual float GetDeltaY()
    {
        return y - prevY;
    }

    // 1フレーム前からの移動量（z方向）
    virtual float GetDeltaZ()
    {
        return z - prevZ;
    }


    // 1フレーム前の左端を取得する
    virtual float GetPrevLeft()
    {
        return prevLeft;
    }

    // 1フレーム前の右端を取得する
    virtual float GetPrevRight()
    {
        return prevRight;
    }

    // 1フレーム前の上端を取得する
    virtual float GetPrevTop()
    {
        return prevTop;
    }

    // 1フレーム前の下端を取得する
    virtual float GetPrevBottom()
    {
        return prevBottom;
    }

    // 1フレーム前の前方を取得する
    virtual float GetPrevForward()
    {   
        return prevForward;
    }

    // 1フレーム前の後方を取得する
    virtual float GetPrevBack()
    {  
        return prevBack;
    }

    // 1フレーム前の場所と当たり判定を記憶する
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

    // 更新処理
    virtual void Update() = 0; 

    // 描画処理
    virtual void Draw() = 0;

    // 衝突したときの関数
    virtual void OnCollision(std::shared_ptr<GameObject> other) {};

    // 当たり判定を描画（デバッグ用）
    virtual void DrawHitBox()
    {

        // 四角Boxを描画
        Camera::DrawLineBox
            (GetLeft(), 0,
            GetRight(), 0,
            GetColor(255, 0, 0),
            GetBack(), GetForward());
    }
};

#endif
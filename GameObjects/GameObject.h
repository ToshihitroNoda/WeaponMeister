#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string> 
#include <memory> 
#include "../Camera.h" 
#include "../Vector3.h"

// ゲーム上に表示される物体の基底クラス。
class GameObject
{
public:
	Camera camera;

	// コンストラクタ
	GameObject() = default;

	// 仮想デストラクタ
	virtual ~GameObject() = default;

	// 更新処理
	virtual void Update() = 0;

	// 描画処理
	virtual void Draw()   = 0;

	// 衝突したときの関数
	virtual void OnCollision(std::shared_ptr<GameObject> other) {};

	// 当たり判定を描画（デバッグ用）
	virtual void DrawHitBox()
	{
		// 四角Boxを描画
		camera.DrawLineBox
		(GetLeft(), 0,
		 GetRight(), 0,
		 GetColor(255, 0, 0),
		 GetBack(), GetForward());
	}

	// 当たり判定の左端を取得
	virtual float GetLeft()
	{
		return (position.x - rotaGraphShift.x) + hitboxOffsetLeft;
	}

	// 右端を取得
	virtual float GetRight()
	{
		return (position.x - rotaGraphShift.x) + imageWidth - hitboxOffsetRight;
	}

	// 上端を取得
	virtual float GetTop()
	{
		return position.y + hitboxOffsetTop;
	}

	// 下端を取得する
	virtual float GetBottom()
	{
		return position.y + imageHeight - hitboxOffsetBottom;
	}

	// 当たり判定のZ手前側を取得
	virtual float GetBack()
	{
		return (position.z - rotaGraphShift.z) + hitboxOffsetBack;
	}

	// Z奥行き方向位置を取得
	virtual float GetForward()
	{
		return (position.z - rotaGraphShift.z) + imageLength - hitboxOffsetForward;
	}

	std::string tag = "";
	bool isDead = false;            // 死んだ（削除対象）フラグ

protected:
	Vector3 position{ 0.0f, 0.0f, 0.0f }; // 座標
	Vector3 velocity{ 0.0f, 0.0f, 0.0f }; // 速度

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
	Vector3 rotaGraphShift{ 0.0f, 0.0f, 0.0f };

	Vector3 prevPosition{ 0.0f, 0.0f, 0.0f };

	float prevLeft    = 0;          // 1フレーム前の左端
	float prevRight   = 0;          // 1フレーム前の右端
	float prevTop     = 0;          // 1フレーム前の上端
	float prevBottom  = 0;          // 1フレーム前の下端 
	float prevForward = 0;          // 1フレーム前の前方
	float prevBack    = 0;          // 1フレーム前の後方 

	// 左端を指定することにより位置を設定する
	virtual void SetLeft(float left)
	{
		position.x = left - hitboxOffsetLeft + rotaGraphShift.x;
	}

	// 右端を指定することにより位置を設定する
	virtual void SetRight(float right)
	{
		position.x = right + hitboxOffsetRight - imageWidth + rotaGraphShift.x;
	}

	// 上端を指定することにより位置を設定する
	virtual void SetTop(float top)
	{
		position.y = top - hitboxOffsetTop;
	}

	// 下端を指定することにより位置を設定する
	virtual void SetBottom(float bottom)
	{
		position.y = bottom + hitboxOffsetBottom - imageHeight;
	}

	// Z手前側を指定することにより位置を設定する
	virtual void SetBack(float back)
	{
		position.z = back - hitboxOffsetBack + rotaGraphShift.z;
	}

	// Z奥行き方向位置を指定することにより位置を設定する
	virtual void SetForward(float forward)
	{
		position.z = forward + hitboxOffsetForward - imageLength + rotaGraphShift.z;
	}

	// 1フレーム前からの移動量（x方向）
	virtual float GetDeltaX()
	{
		return position.x - prevPosition.x;
	}

	// 1フレーム前からの移動量（y方向）
	virtual float GetDeltaY()
	{
		return position.y - prevPosition.y;
	}

	// 1フレーム前からの移動量（z方向）
	virtual float GetDeltaZ()
	{
		return position.z - prevPosition.z;
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
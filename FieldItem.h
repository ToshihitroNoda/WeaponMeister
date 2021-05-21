#ifndef FIELDITEM_H_
#define FIELDITEM_H_

#include "GameObject.h"
#include "GameManager.h"

class FieldItem : public GameObject
{
public:
	GameManager& gm = GameManager::GetInstance();

	FieldItem() = default;

	FieldItem(float x, float y, float z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		tag = "FieldItem";

		imageWidth			= 32;	// 画像の横ピクセル数
		imageHeight			= 32;	// 画像の縦ピクセル数
		imageLength			= 32;	// 画像のZ方向の厚みのピクセル数
		hitboxOffsetLeft	= -30;	// 当たり判定の左端のオフセット
		hitboxOffsetRight	= -30;	// 当たり判定の右端のオフセット
		hitboxOffsetTop		= 0;	// 当たり判定の上端のオフセット
		hitboxOffsetBottom	= 0;	// 当たり判定の下端のオフセット
		hitboxOffsetForward = -30;	// 当たり判定の奥方向のオフセット
		hitboxOffsetBack	= -30;	// 当たり判定の手前方向のオフセット

		if (isRotaGraph == true)
		{   // 画像の中心を起点に描く場合のずれ
			rotaGraphShiftX = (float)imageWidth / 2;
			rotaGraphShiftY = (float)imageHeight / 2;
			rotaGraphShiftZ = (float)imageLength / 2;
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

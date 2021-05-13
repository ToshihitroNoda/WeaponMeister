#ifndef MAPOBJECTS_H_
#define MAPOBJECTS_H_

#include <DxLib.h>
#include "GameManager.h"
#include "GameObject.h"
#include "Image.h"

class MapObjects : public GameObject
{
public:
	GameManager& gm = GameManager::GetInstance();

	MapObjects(float x, float y, float z, std::string ObjectsName)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		tag = ObjectsName;

		imageWidth = 32;	// 画像の横ピクセル数
		imageHeight = 32;	// 画像の縦ピクセル数
		imageLength = 32;	// 画像のZ方向の厚みのピクセル数
		hitboxOffsetLeft = -10;	// 当たり判定の左端のオフセット
		hitboxOffsetRight = -10;	// 当たり判定の右端のオフセット
		hitboxOffsetTop = 0;	// 当たり判定の上端のオフセット
		hitboxOffsetBottom = 0;	// 当たり判定の下端のオフセット
		hitboxOffsetForward = -10;	// 当たり判定の奥方向のオフセット
		hitboxOffsetBack = -10;	// 当たり判定の手前方向のオフセット

		if (isRotaGraph == true)
		{   // 画像の中心を起点に描く場合のずれ
			rotaGraphShiftX = (float)imageWidth / 2;
			rotaGraphShiftY = (float)imageHeight / 2;
			rotaGraphShiftZ = (float)imageLength / 2;
		}
	};

	~MapObjects() {};

	void Init() {};
	void Update() {};
	void Draw() 
	{
		if (tag == "Spruce_1")
		{
			DrawModel(Image::Spruce_1);
		}
	};
	void OnCollision(std::shared_ptr<GameObject> other) {};
	void DrawModel(int MV1Handle)
	{
		MV1SetPosition(MV1Handle, VGet(x, y, z));
		MV1SetScale(MV1Handle, VGet(0.5f, 0.5f, 0.5f));
		MV1DrawModel(MV1Handle);
	}

};

#endif

#ifndef MAPTERRAIN_H_
#define MAPTERRAIN_H_

#include <DxLib.h>
#include "GameManager.h"
#include "GameObject.h"
#include "Image.h"

class MapTerrain : public GameObject
{
public:
	GameManager& gm = GameManager::GetInstance();

	MapTerrain(float x, float y, float z, std::string TerrainName)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		tag = TerrainName;

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

	~MapTerrain() {};

	void Init() {};
	void Update() {};
	void Draw()
	{
		if (tag == "Grass")
		{
			DrawModel(Image::Terrain_Block_1);
		}
	};
	void OnCollision(std::shared_ptr<GameObject> other) {};
	void DrawModel(int MV1Handle)
	{
		MV1SetPosition(MV1Handle, VGet(x, y, z));
		MV1SetScale(MV1Handle, VGet(0.2f, 0.2f, 0.2f));
		MV1DrawModel(MV1Handle);
	}

};

#endif

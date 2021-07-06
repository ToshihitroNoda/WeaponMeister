#ifndef MAPTERRAIN_H_
#define MAPTERRAIN_H_

#include <DxLib.h>
#include "../GameManager.h"
#include "GameObject.h"

class MapTerrain : public GameObject
{
public:
	GameManager& gm = GameManager::GetInstance();

	MapTerrain(Vector3 position, std::string TerrainName)
	{
		this->position = position;
		tag = TerrainName;

		imageWidth  = 32;   // 画像の横ピクセル数
		imageHeight = 32;   // 画像の縦ピクセル数
		imageLength = 32;   // 画像のZ方向の厚みのピクセル数
		hitboxOffsetLeft    = -10;  // 当たり判定の左端のオフセット
		hitboxOffsetRight   = -10;  // 当たり判定の右端のオフセット
		hitboxOffsetTop     = 0;    // 当たり判定の上端のオフセット
		hitboxOffsetBottom  = 0;    // 当たり判定の下端のオフセット
		hitboxOffsetForward = -10;  // 当たり判定の奥方向のオフセット
		hitboxOffsetBack    = -10;  // 当たり判定の手前方向のオフセット
	};

	~MapTerrain() = default;

	void Update() override {};
	void Draw() override;
	void DrawModel(int MV1Handle);

};

#endif

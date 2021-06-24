#include "MapTerrain.h"

void MapTerrain::Draw()
{
	if (tag == "Grass")
	{
		DrawModel(gm.image.Terrain_Block_1);
	}
	else if (tag == "Sand")
	{
		DrawModel(gm.image.Terrain_Block_2);
	}
	else if (tag == "Stone")
	{
		DrawModel(gm.image.Terrain_Block_3);
	}
	else if (tag == "Volcano")
	{
		DrawModel(gm.image.Terrain_Block_4);
	}
}

void MapTerrain::DrawModel(int MV1Handle)
{
	MV1SetPosition(MV1Handle, VGet(x, y, z));
	MV1SetScale(MV1Handle, VGet(0.162f, 0.25f, 0.162f));
	MV1DrawModel(MV1Handle);
}
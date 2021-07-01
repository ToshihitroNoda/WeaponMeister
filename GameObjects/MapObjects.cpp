#include "MapObjects.h"
#include "../Map.h"

void MapObjects::Draw()
{
	for (int i = 0; i < gm.map->objectIDs.size(); i++)
	{
		if (tag == gm.map->objectNames[i])
		{
			DrawModel(objectModelHandles[i]);
		}
	}
	//DrawHitBox();
}

void MapObjects::DrawModel(int MV1Handle)
{
	MV1SetPosition(MV1Handle, VGet(x, y, z));
	MV1SetScale(MV1Handle, VGet(0.5f, 0.5f, 0.5f));
	MV1DrawModel(MV1Handle);
}


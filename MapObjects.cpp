#include "MapObjects.h"
#include "Map.h"

void MapObjects::Init()
{

}

void MapObjects::Update()
{

}

void MapObjects::Draw()
{
	for (int i = 0; i < gm.map->ObjectIDs.size(); i++)
	{
		if (tag == gm.map->ObjectNames[i])
		{
			DrawModel(ObjectModelHandles[i]);
		}
	}
}

void MapObjects::OnCollision(std::shared_ptr<GameObject> other) {};

void MapObjects::DrawModel(int MV1Handle)
{
	MV1SetPosition(MV1Handle, VGet(x, y, z));
	MV1SetScale(MV1Handle, VGet(0.5f, 0.5f, 0.5f));
	MV1DrawModel(MV1Handle);
}


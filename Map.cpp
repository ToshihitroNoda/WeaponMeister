#include "Map.h"

// �G�o���˒��̎����������y��Ɍv�Z���Ď������z����ƌv�Z���K�v�Ȃ��Ȃ�y����������z
	//�y���ӁIX��Y�̒P�ʂ̓}�X�ځz
void Map::InitSpawnDic(int rangeCellX, int rangeCellY)
{
	SpawnDic.clear();//��U�������N���A����̂ŃQ�[�����̍Đݒ����(�����������Ԃ͂�����)
	// �G�o���˒��̎���������
	// �� X = A cos�� Y = B sin��(���ȉ~�̕�����)
	// �� �ȉ~�̔��a r = ��(A�~A�~cos�Ɓ~cos�� + B�~B�~sin�Ɓ~sin��)
	// �� x��2�� + y��2�� < r�Ȃ�Αȉ~�̓���
	float A2 = (float)(rangeCellX * rangeCellX); // 2��
	float B2 = (float)(rangeCellY * rangeCellY); // 2��
	for (int x = -rangeCellX; x <= rangeCellX; x++)
	{
		for (int y = -rangeCellY; y <= rangeCellY; y++)
		{   //��[�t�O�p�֐�] https://cpprefjp.github.io/reference/cmath/atan2.html
			float theta = (float)std::atan2(y, x); // ��[�t�O�p�֐�]
			float cos_t = std::cos(theta);
			float sin_t = std::sin(theta);
			float r2 = A2 * cos_t * cos_t + B2 * sin_t * sin_t;
			if (x * x + y * y <= r2) // �� x��2�� + y��2�� < r�Ȃ�Αȉ~�̓���
			{   //�ȉ~�̓����Ȃ玫��SpawnDic[(x,y)] = true;�Ƃ��ēo�^
				//�y���ȉ~�ɂ������Ƃ��͂�����zSpawnDic[CellXY(x,y)] = true; //�y��zSpawnDic[(3,2)] = true;
			}
			//�y���l�p�`�ɂ������Ƃ��͂�����z
			SpawnDic[CellXY(x, y)] = true;
		}
	}
}

// �Q�[���I�u�W�F�N�g�`��
void Map::LoadObjects()
{
	if (!objectsLoad)
	{
		for (int cellX = 0; cellX < terrain.Width; cellX++)
		{
			for (int cellY = 0; cellY < terrain.Height; cellY++)
			{
				float x = (float)(cellX * CellSize) + rotaGraphShiftX; //�}�X�ڃT�C�Y/2���炵
				float y = (float)(cellY * CellSize) + rotaGraphShiftY; //�}�X�ڃT�C�Y/2���炵
				int id = -1;
				if (cellY < (int)objects.size()
					&& cellX < (int)objects[cellY].size())
				{
					id = objects[cellY][cellX];
				}
				if (id == Fielditem)
				{
					gm.fieldItems.push_back(std::make_shared<FieldItem>(x, 30, y));
				}
				for (int i = 0; i < ObjectIDs.size(); i++)
				{
					if (id == ObjectIDs[i])
					{
						gm.mapObjects.push_back(std::make_shared<MapObjects>(x, 0, y, ObjectWidths[i], ObjectLengths[i], ObjectNames[i]));
					}
				}
			}
		}
		objectsLoad = true;
	}
}

//���n�`��`��3D�Ή���Y���ʂɕ`��
void Map::LoadTerrain()
{
	if (!terrainLoad)
	{
		for (int cellX = 0; cellX < terrain.Width; cellX++)
		{
			for (int cellY = 0; cellY < terrain.Height; cellY++)
			{
				float x = (float)(cellX * CellSize) + rotaGraphShiftX; //�}�X�ڃT�C�Y/2���炵
				float y = (float)(cellY * CellSize) + rotaGraphShiftY; //�}�X�ڃT�C�Y/2���炵
				int id = -1;
				if (cellY < (signed)terrain.size()
					&& cellX < (signed)terrain[cellY].size())
				{
					id = terrain[cellY][cellX];
				}
				if (id == terrain_grass)
				{
					gm.mapTerrain.push_back(std::make_shared<MapTerrain>(x, -25, y, "Grass"));
				}
				else if (id == terrain_sand)
				{
					gm.mapTerrain.push_back(std::make_shared<MapTerrain>(x, -25, y, "Sand"));
				}
				else if (id == terrain_stone)
				{
					gm.mapTerrain.push_back(std::make_shared<MapTerrain>(x, -25, y, "Stone"));
				}
				else if (id == terrain_volcano)
				{
					gm.mapTerrain.push_back(std::make_shared<MapTerrain>(x, -25, y, "Volcano"));
				}
			}
		}
		terrainLoad = true;
	}
}

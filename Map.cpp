#include "Map.h"

// �G�o���˒��̎����������y��Ɍv�Z���Ď������z����ƌv�Z���K�v�Ȃ��Ȃ�y����������z
	//�y���ӁIX��Y�̒P�ʂ̓}�X�ځz
void Map::InitSpawnDic(int rangeCellX, int rangeCellY)
{
	spawnDic_.clear();//��U�������N���A����̂ŃQ�[�����̍Đݒ����(�����������Ԃ͂�����)
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
			spawnDic_[CellXY(x, y)] = true;
		}
	}
}

// �Q�[���I�u�W�F�N�g�`��
void Map::LoadObjects()
{
	if (!objectsLoad_)
	{
		for (int cellX = 0; cellX < terrain_.Width; cellX++)
		{
			for (int cellY = 0; cellY < terrain_.Height; cellY++)
			{
				float x = (float)(cellX * cellSize_) + rotaGraphShiftX_; //�}�X�ڃT�C�Y/2���炵
				float y = (float)(cellY * cellSize_) + rotaGraphShiftY_; //�}�X�ڃT�C�Y/2���炵
				int id = -1;
				if (cellY < (int)objects_.size()
					&& cellX < (int)objects_[cellY].size())
				{
					id = objects_[cellY][cellX];
				}
				if (id == Fielditem_)
				{
					gm.fieldItems.push_back(std::make_shared<FieldItem>(x, 30, y));
				}
				for (int i = 0; i < objectIDs.size(); i++)
				{
					if (id == objectIDs[i])
					{
						gm.mapObjects.push_back(std::make_shared<MapObjects>(x, 0, y, objectWidths_[i], objectLengths_[i], objectNames[i]));
					}
				}
			}
		}
		objectsLoad_ = true;
	}
	if (!objects2Load_ && objects2_.size() > 0)
	{
		for (int cellX = 0; cellX < terrain_.Width; cellX++)
		{
			for (int cellY = 0; cellY < terrain_.Height; cellY++)
			{
				float x = (float)(cellX * cellSize_) + rotaGraphShiftX_; //�}�X�ڃT�C�Y/2���炵
				float y = (float)(cellY * cellSize_) + rotaGraphShiftY_; //�}�X�ڃT�C�Y/2���炵
				int id = -1;
				if (cellY < (int)objects2_.size()
					&& cellX < (int)objects2_[cellY].size())
				{
					id = objects2_[cellY][cellX];
				}
				for (int i = 0; i < objectIDs.size(); i++)
				{
					if (id == objectIDs[i])
					{
						gm.mapObjects.push_back(std::make_shared<MapObjects>(x, 180, y, objectWidths_[i], objectLengths_[i], objectNames[i]));
					}
				}
			}
		}
		objects2Load_ = true;
	}
	if (!objects3Load_ && objects3_.size() > 0)
	{
		for (int cellX = 0; cellX < terrain_.Width; cellX++)
		{
			for (int cellY = 0; cellY < terrain_.Height; cellY++)
			{
				float x = (float)(cellX * cellSize_) + rotaGraphShiftX_; //�}�X�ڃT�C�Y/2���炵
				float y = (float)(cellY * cellSize_) + rotaGraphShiftY_; //�}�X�ڃT�C�Y/2���炵
				int id = -1;
				if (cellY < (int)objects3_.size()
					&& cellX < (int)objects3_[cellY].size())
				{
					id = objects3_[cellY][cellX];
				}
				for (int i = 0; i < objectIDs.size(); i++)
				{
					if (id == objectIDs[i])
					{
						gm.mapObjects.push_back(std::make_shared<MapObjects>(x, 360, y, objectWidths_[i], objectLengths_[i], objectNames[i]));
					}
				}
			}
		}
		objects3Load_ = true;
	}
}

//���n�`��`��3D�Ή���Y���ʂɕ`��
void Map::LoadTerrain()
{
	if (!terrainLoad_)
	{
		for (int cellX = 0; cellX < terrain_.Width; cellX++)
		{
			for (int cellY = 0; cellY < terrain_.Height; cellY++)
			{
				float x = (float)(cellX * cellSize_) + rotaGraphShiftX_; //�}�X�ڃT�C�Y/2���炵
				float y = (float)(cellY * cellSize_) + rotaGraphShiftY_; //�}�X�ڃT�C�Y/2���炵
				int id = -1;
				if (cellY < (signed)terrain_.size()
					&& cellX < (signed)terrain_[cellY].size())
				{
					id = terrain_[cellY][cellX];
				}
				if (id == Terrain_Grass_)
				{
					gm.mapTerrain.push_back(std::make_shared<MapTerrain>(x, -25, y, "Grass"));
				}
				else if (id == Tterrain_Sand_)
				{
					gm.mapTerrain.push_back(std::make_shared<MapTerrain>(x, -25, y, "Sand"));
				}
				else if (id == Terrain_Stone_)
				{
					gm.mapTerrain.push_back(std::make_shared<MapTerrain>(x, -25, y, "Stone"));
				}
				else if (id == Terrain_Volcano_)
				{
					gm.mapTerrain.push_back(std::make_shared<MapTerrain>(x, -25, y, "Volcano"));
				}
			}
		}
		terrainLoad_ = true;
	}
}

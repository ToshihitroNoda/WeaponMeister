#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <map>  
#include <memory> 
#include <cmath> 
#include <fstream> 
#include <string> 
#include <sstream> 
#include <assert.h> 

#include "Screen.h"
#include "GameManager.h"
#include "GameObject.h"
#include "MyMath.h"
#include "Image.h"
#include "FieldItem.h"
#include "MapObjects.h"
#include "MapTerrain.h"
#include "DataCsv.h"

// CSV�t�@�C���̓Ǎ��� & �����蔻��\�ȃ}�X��
struct CsvCell : public DataCsv
{
	int NoneData	  = -1; // ���̒l��CSV�f�[�^�̓f�[�^���Ȃ��}�X�Ƃ݂Ȃ�
	int CellSize	  = 1;
	CsvCell(int CellSize = 1, std::string filePath = "") : DataCsv(filePath)
	{
		assert(CellSize > 0 && "�}�X�ڃT�C�Y�w��CellSize��1�ȏ�ɐݒ肵�āI" != "");
		this->CellSize = CellSize;
	};
	~CsvCell() { clear(); }; //���|�������͂�����
	// csv�t�@�C���̓ǂݍ���
	void LoadMap(int CellSize, std::string filePath)
	{
		assert(filePath != "" && "�t�@�C����filePath��ݒ肵�āI" != "");
		DataCsv::LoadMap(filePath); // �t�@�C���Ǎ���
	}
};

class Map
{
public:
	GameManager& gm = GameManager::GetInstance();

	const int None			  = -1;   // ���������}�X
	const int terrain_grass   = 0;	  // ���̒n��
	const int terrain_sand	  = 1;	  // ���̒n��
	const int terrain_stone   = 2;	  // �΂̒n��
	const int terrain_volcano = 3;	  // �ΎR�̒n��

	const int Fielditem		  = 0;	  // �t�B�[���h��̃A�C�e��
	const int Spruce_1		  = 1;    // ��1

	//�ǂ���Ȃ�����
	int NotWallNums[2] = { -1,0 };

	// �}�X�ڂ�X��Y��ێ�����f�[�^�^
	struct CellXY
	{
		int X = 0;
		int Y = 0;
		CellXY(int X, int Y) : X{ X }, Y{ Y }
		{};
		bool operator < (const CellXY& otherXY) const {
			if (Y < otherXY.Y) return true;		// Y�D����בւ�
			if (Y > otherXY.Y) return false;
			if (X < otherXY.X) return true;		// Y����������X���r
			if (X > otherXY.X) return false;
			return false;						// ���S��v�̂Ƃ���
		}
	};

	int SpawnRangeX = 30;		// �I�u�W�F�N�g�o���˒��X�|�[�������W�y���ӁIX�̒P�ʂ̓}�X�ځz
	int SpawnRangeY = 30;		// �I�u�W�F�N�g�o���˒��X�|�[�������W�y���ӁIY�̒P�ʂ̓}�X�ځz

	std::map<CellXY, bool> SpawnDic;

	const int CellSize = 32;	// �}�b�v��1�}�X�̃s�N�Z����

	bool isRotaGraph = true;	// DrawRotaGraph���g���Ƃ��̓}�X�ڃT�C�Y/2���炷�K�v������

	// �摜�̒��S���N�_�ɕ`���ꍇ�̂���
	float rotaGraphShiftX = (isRotaGraph) ? (float)CellSize / 2 : 0.0f;
	float rotaGraphShiftY = (isRotaGraph) ? (float)CellSize / 2 : 0.0f;
	float rotaGraphShiftZ = (isRotaGraph) ? (float)CellSize / 2 : 0.0f;

	CsvCell terrain;			// ���n�`�f�[�^
	CsvCell objects;			// �G�z�u�f�[�^

	int TerrainWidth = 0;		// �}�b�v�f�[�^�̉��̃}�X��
	int TerrainHeight = 0;		// �}�b�v�f�[�^�̏c�̃}�X��
	float positionX = 0;		// ���݂̈ʒu�i�}�b�v���[�̍��W�j
	float positionY = 0;		// ���݂̈ʒu�i�}�b�v��[�̍��W�j

	bool objectsLoad = false;
	bool terrainLoad = false;

	// �R���X�g���N�^
	// startPosition : �J�n�ʒu�i�f�o�b�O�⃊�X�^�[�g���ɁA�ʂ̓r������J�n�ł���悤�Ɂj
	// filePath : CSV�t�@�C���̃p�X
	Map(float startPosition, std::string stageName)
	{
		positionX = startPosition;
		objectsLoad = false;

		objects.LoadMap(CellSize, "Resource/Map/" + stageName + "_objects.csv");
		terrain.LoadMap(CellSize, "Resource/Map/" + stageName + "_terrain.csv");


		//DataInfo terrainDataInfo = Load("Map/" + stageName + "_terrain.csv", terrain);
		//TerrainWidth = terrainDataInfo.Width;
		//TerrainHeight = terrainDataInfo.Height;

		assert(SpawnRangeX > 0 && SpawnRangeY > 0); // �����ƓG�o���˒���ݒ肵�Ă�
		// �G�o���˒��̎���������
		InitSpawnDic(SpawnRangeX, SpawnRangeY);
	}

	// �f�X�g���N�^
	~Map()
	{
		// �}�b�v�f�[�^�̂��|��
		objects.clear();
		terrain.clear();
	}

	// �G�o���˒��̎����������y��Ɍv�Z���Ď������z����ƌv�Z���K�v�Ȃ��Ȃ�y����������z
	//�y���ӁIX��Y�̒P�ʂ̓}�X�ځz
	void InitSpawnDic(int rangeCellX, int rangeCellY)
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

	// �w�肳�ꂽ���W�i���[���h���W�j�̒n�`�f�[�^���擾����B
	int GetTerrain(float worldX, float worldY, float worldZ = -10000.0)
	{
		if (worldZ != -10000.0) worldY = worldZ; //���yY��Z��ϊ��zZ�̓��͂�����Ƃ���Z��Y�Ƃ��Ĉ���
		// ���̍��W���w�肳�ꂽ�ꍇ�́A�����������̂Ƃ��Ĉ���
		if (worldX < 0 || worldY < 0)
			return None;

		// �}�b�v���W�n�i�񎟌��z��̍s�Ɨ�j�ɕϊ�����
		int mapX = (int)(worldX / CellSize);
		int mapY = (int)(worldY / CellSize);

		// �񎟌��z��͈̔͊O�́A�����������̂Ƃ��Ĉ���
		if (mapX >= terrain.Width || mapY >= terrain.Height)
			return None;

		return terrain[mapY][mapX]; // �񎟌��z�񂩂�n�`ID�����o���ĕԋp����
	}

	int GetObjects(float worldX, float worldY, float worldZ = -10000.0)
	{
		if (worldZ != -10000.0) worldY = worldZ; //���yY��Z��ϊ��zZ�̓��͂�����Ƃ���Z��Y�Ƃ��Ĉ���
		// ���̍��W���w�肳�ꂽ�ꍇ�́A�����������̂Ƃ��Ĉ���
		if (worldX < 0 || worldY < 0)
			return None;

		// �}�b�v���W�n�i�񎟌��z��̍s�Ɨ�j�ɕϊ�����
		int mapX = (int)(worldX / CellSize);
		int mapY = (int)(worldY / CellSize);

		// �񎟌��z��͈̔͊O�́A�����������̂Ƃ��Ĉ���
		if (mapX >= objects.Width || mapY >= objects.Height)
			return None;

		return objects[mapY][mapX]; // �񎟌��z�񂩂�n�`ID�����o���ĕԋp����
	}

	// �Q�[���I�u�W�F�N�g�`��
	void DrawObjects()
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
					if (id == Spruce_1)
					{
						gm.mapObjects.push_back(std::make_shared<MapObjects>(x, 0, y, "Spruce_1"));
					}
				}
			}
			objectsLoad = true;
		}
	}

	//���n�`��`��3D�Ή���Y���ʂɕ`��
	void DrawTerrain()
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
				}
			}
			terrainLoad = true;
		}
	}
	int count = 0;

	// �w�肳�ꂽ���W�i���[���h���W�j�̒n�`���ǂ����ׂ�
	bool IsWall(float worldX, float worldY, float worldZ = -10000.0)
	{
		int objectsID = GetObjects(worldX, worldY, worldZ); // �w�肳�ꂽ���W�̒n�`��ID���擾

		return IsWall(objectsID);
	}

	//����ID���ǂ��ǂ����������ׂ�
	bool IsWall(int objectsID)
	{
		for (int i = 0; i < sizeof(NotWallNums) / sizeof(NotWallNums[0]); i++)//[�z��̐������߂�ɂ�]https://qiita.com/yohhoy/items/a2ab2900a2bd36c31879
		{   // �ǂ���Ȃ��ԍ��̂Ƃ�
			if (objectsID == NotWallNums[i]) return false;
		}
		//SetTerrain(worldX, worldY, worldZ);
		//if (terrainID == 0) { printfDx("%d ", terrainID); printfDx("(%f %f)", worldX, worldZ); count++; }
		return (objectsID != -1);// (terrainID == Wall); // �n�`���ǂȂ�true�A�Ⴄ�Ȃ�false��ԋp����
	}

};

#endif
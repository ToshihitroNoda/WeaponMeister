#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "Singleton.h"

#include <vector>
#include <memory>
#include <iostream>
#include <map>
#include <DxLib.h>
#include <assert.h>

#include "DataCsv.h"
#include "Image.h"


// CSV�t�@�C���̓Ǎ���
struct MapData : public DataCsv
{
	MapData(std::string filePath = "", std::string csvOption = "DATA") : DataCsv(filePath)
	{
	};
	~MapData() { clear(); };//���|�������͂�����
	// csv�t�@�C���̓ǂݍ���
	void Load(std::string filePath)
	{
		assert(filePath != "" && "�t�@�C����filePath��ݒ肵�āI" != "");
		DataCsv::LoadData(filePath);
	}
};

struct ItemData : public DataCsv
{
	ItemData(std::string filePath = "", std::string csvOption = "DATA") : DataCsv(filePath)
	{
	};
	~ItemData() { clear(); };//���|�������͂�����
	// csv�t�@�C���̓ǂݍ���
	void Load(std::string filePath)
	{
		assert(filePath != "" && "�t�@�C����filePath��ݒ肵�āI" != "");
		DataCsv::LoadData(filePath);
	}
};

struct WeaponData : public DataCsv
{
	WeaponData(std::string filePath = "", std::string csvOption = "DATA") : DataCsv(filePath)
	{
	};
	~WeaponData() { clear(); };//���|�������͂�����
	// csv�t�@�C���̓ǂݍ���
	void Load(std::string filePath)
	{
		assert(filePath != "" && "�t�@�C����filePath��ݒ肵�āI" != "");
		DataCsv::LoadData(filePath);
	}
};

struct ScoreData : public DataCsv
{
	ScoreData(std::string filePath = "", std::string csvOption = "DATA") : DataCsv(filePath)
	{
	};
	~ScoreData() { clear(); };//���|�������͂�����
	// csv�t�@�C���̓ǂݍ���
	void Load(std::string filePath)
	{
		assert(filePath != "" && "�t�@�C����filePath��ݒ肵�āI" != "");
		DataCsv::LoadData(filePath);
	}
};

class Map;
class Player;
class FieldItem;
class MapObjects;
class MapTerrain;

class GameManager : public Singleton<GameManager>
{
public:

	MapData mapData;
	ItemData itemData;
	WeaponData weaponData;
	ScoreData scoreData;
	Image image;

	friend class Singleton<GameManager>;				// Singleton�ł̃C���X�^���X�쐬�͋���

	std::shared_ptr<Map> map{ nullptr };				// �}�b�v

	std::shared_ptr<Player> player{ nullptr };			// ���@�̏�����

	std::vector<std::shared_ptr<FieldItem>> fieldItems; // �t�B�[���h��̃A�C�e��

	std::vector<std::shared_ptr<MapObjects>> mapObjects;
	std::vector<std::shared_ptr<MapTerrain>> mapTerrain;

	// �A�C�e���ۊ�vector
	std::vector<int> pouch;
	std::vector<int> handles;
	std::vector<int> main;
	std::vector<int> weapons;

	// �i���ۊ�vector
	std::vector<int> pouchQuality;
	std::vector<int> handlesQuality;
	std::vector<int> mainQuality;
	std::vector<int> weaponQuality;

	// �폜�����e���v���[�g
	template <typename T, class T_if>
	void EraseRemoveIf(std::vector<T>& v, T_if if_condition)
	{
		v.erase(
			std::remove_if(v.begin(), v.end(), if_condition),
			v.end()
		);
	};

	const int colorWhite = GetColor(255, 255, 255);
	const int colorBrack = GetColor(0, 0, 0);
	const int colorGray  = GetColor(122, 122, 122);
	const int colorRed   = GetColor(255, 0, 0);
	const int colorBlue  = GetColor(0, 100, 200);

	const int DefaultFontSize_ = 15;
	const int LastDay = 14;
	const int MaxPouchSize = 200;

	int money = 0;
	const int defaultMoney = 1000;

protected:
	GameManager()          = default;  // �O������̃C���X�^���X�쐬�͋֎~
	virtual ~GameManager() = default;  // �O������̃C���X�^���X�j�����֎~
};

#endif 


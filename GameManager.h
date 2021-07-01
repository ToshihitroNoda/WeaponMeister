#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <vector>
#include <memory>
#include <iostream>
#include <map>
#include <DxLib.h>
#include <assert.h>

#include "MyLib/Singleton.h"
#include "MyLib/DataCsv.h"
#include "Image.h"

#include "Items/Pouch.h"
#include "Items/HandleItems.h"
#include "Items/MainItems.h"
#include "Items/Weapon.h"

#include "Datas/MapData.h"
#include "Datas/ItemData.h"
#include "Datas/WeaponData.h"
#include "Datas/ScoreData.h"

class Map;
class Player;
class FieldItem;
class MapObjects;
class MapTerrain;

class GameManager : public Singleton<GameManager>
{
public:

	MapData    mapData;
	ItemData   itemData;
	WeaponData weaponData;
	ScoreData  scoreData;
	Image      image;

	Pouch       pouch;
	HandleItems handles;
	MainItems   main;
	Weapon      weapons;

	friend class Singleton<GameManager>;				// Singleton�ł̃C���X�^���X�쐬�͋���

	std::shared_ptr<Map> map{ nullptr };				// �}�b�v

	std::shared_ptr<Player> player{ nullptr };			// ���@�̏�����

	std::vector<std::shared_ptr<FieldItem>> fieldItems; // �t�B�[���h��̃A�C�e��

	std::vector<std::shared_ptr<MapObjects>> mapObjects;
	std::vector<std::shared_ptr<MapTerrain>> mapTerrain;

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


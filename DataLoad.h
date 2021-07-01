#ifndef DATALOAD_H_
#define DATALOAD_H_

#include<fstream>
#include<vector>

#include "Scene/Adv.h"
#include "Scene/StageSelection.h"
#include "GameManager.h"

struct LStatus {
	int day;
	int money;
	int mapCount;
	int pouchSize;
	int weaponSize;
};

class DataLoad
{
public:
	GameManager& gm = GameManager::GetInstance();

	DataLoad()  = default;
	~DataLoad() = default;

	std::fstream file;

	void Load()
	{
		/* セーブするべきものは
		* 日にち、ポーチ内のアイテム・装備、それぞれの品質、所持金
		*/

		LStatus lStatus = { 0 };

		file.open("savedata.dat", std::ios::binary | std::ios::in);

		file.read((char*)&lStatus, sizeof(lStatus));

		Adv::day                 = lStatus.day;
		gm.money                 = lStatus.money;
		StageSelection::mapCount = lStatus.mapCount;

		// ロード前に何かデータが書き込まれていたら重複するのでclear()
		gm.weapons.clear();
		gm.pouch.clear();

		for (int i = 0; i < lStatus.pouchSize; i++)
		{
			int loadItemData;
			int loadQualityData;
			// アイテムIDの読み込み
			file.read((char*)&loadItemData, sizeof(loadItemData)); 
			// ポインタの位置を品質の場所にずらす
			file.seekg((5 + i + lStatus.pouchSize) * sizeof(loadItemData));
			// 品質の読み込み
			file.read((char*)&loadQualityData, sizeof(loadQualityData)); 
			// アイテムIDと品質を追加
			gm.pouch.Add(loadItemData, loadQualityData);
			// ポインタの位置を一つ進める
			file.seekg((6 + i) * sizeof(loadItemData));
		}

		// 武器データが保存されている場所(LStatus数 + pouch数 + pouch品質数)
		int weaponDataPos = 5 + lStatus.pouchSize * 2;
		// ポインタの位置を武器の場所にずらす
		file.seekg((weaponDataPos) * sizeof(int)); 

		for (int i = 0; i < lStatus.weaponSize; i++)
		{
			int loadWeaponData;
			int loadQualityData;
			// 武器IDの読み込み
			file.read((char*)&loadWeaponData, sizeof(loadWeaponData));
			// ポインタの位置を品質の場所にずらす
			file.seekg((weaponDataPos + i + lStatus.weaponSize) * sizeof(loadWeaponData));
			// 品質の読み込み
			file.read((char*)&loadQualityData, sizeof(loadQualityData)); 
			// 武器IDと品質を追加
			gm.weapons.Add(loadWeaponData, loadQualityData);
			// ポインタの位置を一つ進める
			file.seekg((6 + i) * sizeof(loadWeaponData));
		}

		file.close();
	}
};

#endif

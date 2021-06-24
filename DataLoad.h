#ifndef DATALOAD_H_
#define DATALOAD_H_

#include<fstream>
#include<vector>

#include "Adv.h"
#include "StageSelection.h"
#include "GameManager.h"

struct LStatus {
	int day;
	int money;
	int mapCount;
	int pouchSize;
	int pouchQSize;
	int weaponSize;
	int WeaponQSize;
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
		gm.pouch.resize(lStatus.pouchSize);
		gm.pouchQuality.resize(lStatus.pouchQSize);
		gm.weapons.resize(lStatus.weaponSize);
		gm.weaponQuality.resize(lStatus.WeaponQSize);

		for (int i = 0; i < gm.pouch.size(); i++)
		{
			file.read((char*)&gm.pouch[i], sizeof(gm.pouch[i]));
		}
		for (int i = 0; i < gm.pouchQuality.size(); i++)
		{
			file.read((char*)&gm.pouchQuality[i], sizeof(gm.pouchQuality[i]));
		}
		for (int i = 0; i < gm.weapons.size(); i++)
		{
			file.read((char*)&gm.weapons[i], sizeof(gm.weapons[i]));
		}
		for (int i = 0; i < gm.weaponQuality.size(); i++)
		{
			file.read((char*)&gm.weaponQuality[i], sizeof(gm.weaponQuality[i]));
		}

		file.close();
	}
};

#endif

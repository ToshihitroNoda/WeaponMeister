#ifndef DATASAVE_H_
#define DATASAVE_H_

#include<fstream>
#include<vector>

#include "Adv.h"
#include "StageSelection.h"
#include "GameManager.h"

struct SStatus {
	int day;
	int money;
	int mapCount;
	int pouchSize;
	int pouchQSize;
	int weaponSize;
	int WeaponQSize;
};

class DataSave
{
public:
	GameManager& gm = GameManager::GetInstance();

	DataSave()  = default;
	~DataSave() = default;

	void Save()
	{
		/* セーブするべきものは
		* 日にち、ポーチ内のアイテム・装備、それぞれの品質、所持金
		*/

		SStatus sStatus     = { 0 };
		sStatus.day         = Adv::day;
		sStatus.money       = gm.money;
		sStatus.mapCount    = StageSelection::mapCount;
		sStatus.pouchSize   = gm.pouch.size();
		sStatus.pouchQSize  = gm.pouchQuality.size();
		sStatus.weaponSize  = gm.weapons.size();
		sStatus.WeaponQSize = gm.weaponQuality.size();

		std::fstream file;
		file.open("savedata.dat", std::ios::binary | std::ios::out);

		file.write((char*)&sStatus, sizeof(sStatus));

		for (int i = 0; i < gm.pouch.size(); i++)
		{
			file.write((char*)&gm.pouch[i], sizeof(gm.pouch[i]));
		}

		for (int i = 0; i < gm.pouchQuality.size(); i++)
		{
			file.write((char*)&gm.pouchQuality[i], sizeof(gm.pouchQuality[i]));
		}

		for (int i = 0; i < gm.weapons.size(); i++)
		{
			file.write((char*)&gm.weapons[i], sizeof(gm.weapons[i]));
		}

		for (int i = 0; i < gm.weaponQuality.size(); i++)
		{
			file.write((char*)&gm.weaponQuality[i], sizeof(gm.weaponQuality[i]));
		}

		file.close();
	}
};

#endif


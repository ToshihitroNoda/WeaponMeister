#ifndef DATASAVE_H_
#define DATASAVE_H_

#include<fstream>
#include<vector>

#include "Adv.h"
#include "StageSelection.h"
#include "GameManager.h"

struct Status {
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

	void Save();
};

#endif

void DataSave::Save()
{
	/* セーブするべきものは
	* 日にち、ポーチ内のアイテム・装備、それぞれの品質、所持金
	*/

	Status status      = { 0 };
	status.day         = Adv::day;
	status.money       = gm.money;
	status.mapCount    = StageSelection::mapCount;
	status.pouchSize   = gm.pouch.size();
	status.pouchQSize  = gm.pouchQuality.size();
	status.weaponSize  = gm.weapons.size();
	status.WeaponQSize = gm.weaponQuality.size();

	std::fstream file;
	file.open("savedata.dat", std::ios::binary | std::ios::out);

	file.write((char*)&status, sizeof(status));

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


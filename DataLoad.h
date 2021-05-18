#ifndef DATALOAD_H_
#define DATALOAD_H_

#include<stdio.h>

#include "Adv.h"
#include "StageSelection.h"
#include "GameManager.h"

class DataLoad
{
public:
	GameManager& gm = GameManager::GetInstance();

	DataLoad() = default;
	~DataLoad() = default;

	void Load();
};

#endif

void DataLoad::Load()
{
	/* セーブするべきものは
	* 日にち、ポーチ内のアイテム・装備、それぞれの品質、所持金
	*/

	FILE* fp;
	errno_t error;

	if ((error = fopen_s(&fp, "savedata.dat", "rb")) != 0)
	{
		exit(0);
	};

	fread(&Adv::day, sizeof(Adv::day), 1, fp);
	fread(&StageSelection::mapCount, sizeof(StageSelection::mapCount), 1, fp);
	fread(&gm.money, sizeof(gm.money), 1, fp);
	//fread(&gm.pouch[0], gm.pouch.size() * sizeof(gm.pouch[0]), 1, fp);
	//fread(&gm.pouchQuality[0], gm.pouchQuality.size() * sizeof(gm.pouchQuality[0]), 1, fp);
	//fread(&gm.weapons[0], gm.weapons.size() * sizeof(gm.weapons[0]), 1, fp);
	//fread(&gm.weaponQuality[0], gm.weaponQuality.size() * sizeof(gm.weaponQuality[0]), 1, fp);

	fclose(fp);
}


#ifndef DATASAVE_H_
#define DATASAVE_H_

#include<stdio.h>


#include "Adv.h"
#include "StageSelection.h"
#include "GameManager.h"

class DataSave
{
public:
	GameManager& gm = GameManager::GetInstance();

	DataSave() = default;
	~DataSave() = default;

	void Save();
};

#endif

void DataSave::Save()
{
	/* セーブするべきものは
	* 日にち、ポーチ内のアイテム・装備、それぞれの品質、所持金
	*/
	FILE* fp;
	errno_t error;

	if ((error = fopen_s(&fp, "savedata.dat", "wb")) != 0)
	{
		exit(0);
	};

	fwrite(&Adv::day, sizeof(int), 1, fp);
	fwrite(&StageSelection::mapCount, sizeof(int), 1, fp);
	fwrite(&gm.money, sizeof(int), 1, fp);
	//fwrite(&gm.pouch[0], gm.pouch.size() * sizeof(gm.pouch[0]), 1, fp);
	//fwrite(&gm.pouchQuality[0], gm.pouchQuality.size() * sizeof(gm.pouchQuality[0]), 1, fp);
	//fwrite(&gm.weapons[0], gm.weapons.size() * sizeof(gm.weapons[0]), 1, fp);
	//fwrite(&gm.weaponQuality[0], gm.weaponQuality.size() * sizeof(gm.weaponQuality[0]), 1, fp);

	fclose(fp);
}


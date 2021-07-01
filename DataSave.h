#ifndef DATASAVE_H_
#define DATASAVE_H_

#include<fstream>
#include<vector>

#include "Scene/Adv.h"
#include "Scene/StageSelection.h"
#include "GameManager.h"

struct SStatus {
	int day;
	int money;
	int mapCount;
	int pouchSize;
	int weaponSize;
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
		sStatus.weaponSize  = gm.weapons.size();

		std::fstream file;
		file.open("savedata.dat", std::ios::binary | std::ios::out);

		file.write((char*)&sStatus, sizeof(sStatus));

		for (int i = 0; i < gm.pouch.size(); i++)
		{
			int saveData = gm.pouch.get_item_element(i);
			file.write((char*)&saveData, sizeof(saveData));
		}

		for (int i = 0; i < gm.pouch.size(); i++)
		{
			int saveData = gm.pouch.get_quality_element(i);
			file.write((char*)&saveData, sizeof(saveData));
		}

		for (int i = 0; i < gm.weapons.size(); i++)
		{
			int saveData = gm.weapons.get_item_element(i);
			file.write((char*)&saveData, sizeof(saveData));
		}

		for (int i = 0; i < gm.weapons.size(); i++)
		{
			int saveData = gm.weapons.get_quality_element(i);
			file.write((char*)&saveData, sizeof(saveData));
		}

		file.close();
	}
};

#endif


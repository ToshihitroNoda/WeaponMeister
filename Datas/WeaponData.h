#ifndef WEAPONDATA_H_
#define WEAPONDATA_H_

#include "../MyLib/DataCsv.h"

class WeaponData : public DataCsv
{
public:
	WeaponData(std::string filePath = "", std::string csvOption = "DATA") : DataCsv(filePath)
	{
	};
	~WeaponData() { clear(); };//お掃除処理はこちら
	// csvファイルの読み込み
	void Load(std::string filePath)
	{
		assert(filePath != "" && "ファイル名filePathを設定して！" != "");
		DataCsv::LoadData(filePath);
	}
};

#endif
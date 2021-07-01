#ifndef WEAPONDATA_H_
#define WEAPONDATA_H_

#include "../MyLib/DataCsv.h"

class WeaponData : public DataCsv
{
public:
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

#endif
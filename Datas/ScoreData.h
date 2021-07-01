#ifndef SCOREDATA_H_
#define SCOREDATA_H_

#include "../MyLib/DataCsv.h"

class ScoreData : public DataCsv
{
public:
	ScoreData(std::string filePath = "", std::string csvOption = "DATA") : DataCsv(filePath)
	{
	};
	~ScoreData() { clear(); };//���|�������͂�����
	// csv�t�@�C���̓ǂݍ���
	void Load(std::string filePath)
	{
		assert(filePath != "" && "�t�@�C����filePath��ݒ肵�āI" != "");
		DataCsv::LoadData(filePath);
	}
};

#endif
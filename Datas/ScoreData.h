#ifndef SCOREDATA_H_
#define SCOREDATA_H_

#include "../MyLib/DataCsv.h"

class ScoreData : public DataCsv
{
public:
	ScoreData(std::string filePath = "", std::string csvOption = "DATA") : DataCsv(filePath)
	{
	};
	~ScoreData() { clear(); };//お掃除処理はこちら
	// csvファイルの読み込み
	void Load(std::string filePath)
	{
		assert(filePath != "" && "ファイル名filePathを設定して！" != "");
		DataCsv::LoadData(filePath);
	}
};

#endif
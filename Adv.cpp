#include "Adv.h"
#include "Input.h"
#include "Image.h"

void Adv::Init()
{
	day++;

	std::stringstream ss;
	ss << day;
	filePath_ = ("Resource/Massege/Massege_" + ss.str() + ".csv");

	Load();
}

void Adv::Load()
{
	std::ifstream ifs_csv_file(filePath_);
	std::string line;

	while (std::getline(ifs_csv_file, line))
	{
		std::istringstream linestream(line); // 各行の文字列ストリーム
		std::string splitted; // カンマ分割文字列
		while (std::getline(linestream, splitted, { ',' }))
		{
			std::istringstream ss; //文字列ストリームの初期化
			ss = std::istringstream(splitted); //文字列ストリーム
			std::string text; // string型保存用
			ss >> text; // istringstreamをstringに変換したものを保存
			massegeList_.push_back(text); //配列に追加
		}
	}
}


void Adv::Final()
{

}

void Adv::Update()
{
	if (Input::GetButtonDown(PAD_INPUT_2))
	{
		sm.LoadScene("StageSelection");
	}
}

void Adv::Draw()
{
	DrawGraph(WindowX_, WindowY_, Image::textWindow, TRUE);

	DrawString(MassegeX, MassegeY, massegeList_[MassegeCount_].c_str(), gm.colorWhite);

	if (IconFlashCount_ % Divisor_ < DrawFlashTiming_)
	{
		DrawGraph(CursorX_, CursorY_, Image::textCursor, TRUE);
	}
	IconFlashCount_++;
}

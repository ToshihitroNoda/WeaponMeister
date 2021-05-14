#ifndef ADVSIMPLESCRIPT_H_
#define ADVSIMPLESCRIPT_H_

#include <DxLib.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

class ADVSimpleScript
{
public:
	ADVSimpleScript() = default;
	~ADVSimpleScript() = default;

	static void Load(std::string filePath);
	static void Update();
	static void ImageDraw();
	static void MassegeDraw(int MassegeColor, int FontSize = 30, int DefaultFontSize = 20);

	static int MassegeCount;
	static std::vector<std::string> massegeList;

	static bool LoadEnd_;
private:

	static int LineWidth_;
	static std::string filePath_;

	static std::vector<int> ResourceNums_;
	static std::vector<std::string> ResourcePath_;
	static std::vector<int> CX_;
	static std::vector<int> CY_;
	static std::vector<int> CDrawID_;
	static std::vector<std::string> Commands_;
	static int ResourceNum_;
	static int MassegeX_;
	static int MassegeY_;
	static int StringX_;
	static int StringY_;
	static int BGX_;
	static int BGY_;
	static int BGID_;
	static int CDrawCount_;
	static int BreakCount_;
	static int PrevPlayMusic;
	static std::string CName_;
	static bool NowBreak_;
	static bool DrawSkip_;
};

int ADVSimpleScript::MassegeCount = 0;

std::vector<std::string> ADVSimpleScript::massegeList;
std::vector<std::string> ADVSimpleScript::ResourcePath_;
std::vector<std::string> ADVSimpleScript::Commands_
{ "ResourceLoad", "Image", "Music", "PlayMusic", "BGX", "BGY", "BGDraw",
  "MassegeX", "MassegeY", "StringX", "StringY", "CName", "CX", "CY",
  "CDraw", "CDrawEnd", "Break", "BreakEnd" };

std::vector<int> ADVSimpleScript::ResourceNums_;
std::vector<int> ADVSimpleScript::CX_;
std::vector<int> ADVSimpleScript::CY_;
std::vector<int> ADVSimpleScript::CDrawID_;

int ADVSimpleScript::LineWidth_ = 0;
int ADVSimpleScript::ResourceNum_ = -1;
int ADVSimpleScript::MassegeX_ = 0;
int ADVSimpleScript::MassegeY_ = 0;
int ADVSimpleScript::StringX_ = 0;
int ADVSimpleScript::StringY_ = 0;
int ADVSimpleScript::BGX_ = 0;
int ADVSimpleScript::BGY_ = 0;
int ADVSimpleScript::BGID_ = 0;
int ADVSimpleScript::CDrawCount_ = 0;
int ADVSimpleScript::BreakCount_ = 0;
int ADVSimpleScript::PrevPlayMusic = 0;

std::string ADVSimpleScript::filePath_ = "";
std::string ADVSimpleScript::CName_ = "";

bool ADVSimpleScript::NowBreak_ = false;
bool ADVSimpleScript::DrawSkip_ = false;
bool ADVSimpleScript::LoadEnd_ = false;

void ADVSimpleScript::Load(std::string filePath)
{
	std::ifstream ifs_csv_file(filePath);
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
			massegeList.push_back(text); //配列に追加
		}
	}

	for (int i = 0; i < massegeList.size(); i++)
	{
		for (int j = 0; j < Commands_.size(); j++)
		{
			if (massegeList[MassegeCount] == Commands_[j])
				Update(); // csvの頭のコマンドが描画されないように先にUpdate回しておく
			else
			{
				LoadEnd_ = true;
				break;
			}
		}
		if (LoadEnd_)
			break;
	}
}

void ADVSimpleScript::Update()
{
	if (MassegeCount < massegeList.size())
	{
		/*------リソースファイルの読み込み-----*/

		if (massegeList[MassegeCount] == "ResourceLoad")
		{
			DrawSkip_ = true;
			ResourceNum_++;
			ResourceNums_.push_back(ResourceNum_);
			MassegeCount++;
			if (massegeList[MassegeCount] == "Image")
			{
				MassegeCount++;
				ResourcePath_.push_back(massegeList[MassegeCount]);
				ResourceNums_[ResourceNum_] = LoadGraph(ResourcePath_.back().c_str());
			}
			else if (massegeList[MassegeCount] == "Music")
			{
				MassegeCount++;
				ResourcePath_.push_back(massegeList[MassegeCount]);
				ResourceNums_[ResourceNum_] = LoadSoundMem(ResourcePath_.back().c_str());
				PrevPlayMusic = ResourceNums_[ResourceNum_];
			}
			MassegeCount++;
		}

		/*-------------------------------------*/

		/*-----BGMの再生-----*/

		else if (massegeList[MassegeCount] == "PlayBGM")
		{
			DrawSkip_ = true;
			MassegeCount++;
			int playMusic = std::stoi(massegeList[MassegeCount].c_str());
			StopSoundMem(PrevPlayMusic);
			PlaySoundMem(playMusic, DX_PLAYTYPE_LOOP);
			PrevPlayMusic = playMusic;
			MassegeCount++;
		}

		/*-------------------*/

		/*-----背景の座標取得-----*/

		else if (massegeList[MassegeCount] == "BGX")
		{
			DrawSkip_ = true;
			MassegeCount++;
			BGX_ = std::stoi(massegeList[MassegeCount]);
			MassegeCount++;
		}
		else if (massegeList[MassegeCount] == "BGY")
		{
			DrawSkip_ = true;
			MassegeCount++;
			BGY_ = std::stoi(massegeList[MassegeCount]);
			MassegeCount++;
		}

		/*------------------------*/

		/*-----背景の描画-----*/

		else if (massegeList[MassegeCount] == "BGDraw")
		{
			DrawSkip_ = true;
			MassegeCount++;
			BGID_ = std::stoi(massegeList[MassegeCount]);
			MassegeCount++;
		}

		/*--------------------*/

		/*-----メッセージの文字列座標取得-----*/

		else if (massegeList[MassegeCount] == "MassegeX")
		{
			DrawSkip_ = true;
			MassegeCount++;
			MassegeX_ = std::stoi(massegeList[MassegeCount]);
			MassegeCount++;
		}
		else if (massegeList[MassegeCount] == "MassegeY")
		{
			DrawSkip_ = true;
			MassegeCount++;
			MassegeY_ = std::stoi(massegeList[MassegeCount]);
			MassegeCount++;
		}

		/*------------------------------------*/

		/*-----メッセージ以外の文字列座標取得-----*/

		else if (massegeList[MassegeCount] == "StringX")
		{
			DrawSkip_ = true;
			MassegeCount++;
			StringX_ = std::stoi(massegeList[MassegeCount]);
			MassegeCount++;
		}
		else if (massegeList[MassegeCount] == "StringY")
		{
			DrawSkip_ = true;
			MassegeCount++;
			StringY_ = std::stoi(massegeList[MassegeCount]);
			MassegeCount++;
		}

		/*----------------------------------------*/

		/*-----メッセージ以外の文字列の描画-----*/

		else if (massegeList[MassegeCount] == "CName")
		{
			DrawSkip_ = true;
			MassegeCount++;
			CName_ = massegeList[MassegeCount];
			MassegeCount++;
		}

		/*--------------------------------------*/

		/*-----キャラクターの座標取得-----*/

		else if (massegeList[MassegeCount] == "CX")
		{
			DrawSkip_ = true;
			MassegeCount++;
			CX_.push_back(std::stoi(massegeList[MassegeCount]));
			MassegeCount++;
		}
		else if (massegeList[MassegeCount] == "CY")
		{
			DrawSkip_ = true;
			MassegeCount++;
			CY_.push_back(std::stoi(massegeList[MassegeCount]));
			MassegeCount++;
		}

		/*--------------------------------*/

		/*-----キャラクターの描画-----*/

		else if (massegeList[MassegeCount] == "CDraw")
		{
			DrawSkip_ = true;
			MassegeCount++;
			CDrawID_.push_back(std::stoi(massegeList[MassegeCount]));
			MassegeCount++;
		}

		/*----------------------------*/

		/*-----キャラクターの立ち絵消し-----*/

		else if (massegeList[MassegeCount] == "CDrawEnd")
		{
			DrawSkip_ = true;
			MassegeCount++;
			int eraseID = std::stoi(massegeList[MassegeCount]);
			for (int i = 0; i < CDrawID_.size(); i++)
			{
				if (CDrawID_[i] == eraseID)
				{
					CDrawID_.erase(CDrawID_.begin() + i);
					CX_.erase(CX_.begin() + i);
					CY_.erase(CY_.begin() + i);
				}
			}
			MassegeCount++;
		}

		/*----------------------------------*/

		/*-----改行処理-----*/

		else if (massegeList[MassegeCount] == "Break")
		{
			DrawSkip_ = true;
			MassegeCount++;
			BreakCount_++;
			NowBreak_ = true;
		}

		/*------------------*/

		/*-----改行処理終了-----*/

		else if (massegeList[MassegeCount] == "BreakEnd")
		{
			DrawSkip_ = true;
			MassegeCount++;
			BreakCount_ = 0;
			NowBreak_ = false;
		}

		/*----------------------*/
	}
}

void ADVSimpleScript::ImageDraw()
{
	/*-----メッセージ処理の画像描画-----*/

	if (ResourceNums_.size() > 0)
	{
		DrawGraph(BGX_, BGY_, ResourceNums_[BGID_], TRUE);
		for (int i = 0; i < CDrawID_.size(); i++)
		{
			DrawGraph(CX_[i], CY_[i], ResourceNums_[CDrawID_[i]], TRUE);
		}
	}

	/*----------------------------------*/
}

void ADVSimpleScript::MassegeDraw(int MassegeColor, int FontSize, int DefaultFontSize)
{
	LineWidth_ = FontSize;

	/*-----メッセージ処理の文字列描画-----*/

	SetFontSize(FontSize);

	if (DrawSkip_)
	{
		DrawSkip_ = false;
		return;
	}
	else
	{
		DrawString(StringX_, StringY_, CName_.c_str(), MassegeColor);

		DrawString(MassegeX_, MassegeY_ + LineWidth_ * BreakCount_, massegeList[MassegeCount].c_str(), MassegeColor);
		if (NowBreak_)
		{
			for (int i = 0; i < BreakCount_; i++)
			{
				DrawString(MassegeX_, MassegeY_ + LineWidth_ * i, massegeList[MassegeCount - ((BreakCount_ - 1 - i) * 2 + 2)].c_str(), MassegeColor);
			}
		}
	}

	SetFontSize(DefaultFontSize);

	/*------------------------------------*/
}

#endif
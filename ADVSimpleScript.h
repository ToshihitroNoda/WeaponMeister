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

	static int MassegeCount_;
	static std::vector<std::string> massegeList_;

private:

	static int LineWidth_;
	static std::string filePath_;

	static std::vector<int> ResourceNums_;
	static std::vector<std::string> ResourcePath_;
	static std::vector<int> CX_;
	static std::vector<int> CY_;
	static std::vector<int> CDrawID_;
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

int ADVSimpleScript::MassegeCount_ = 0;

std::vector<std::string> ADVSimpleScript::massegeList_;
std::vector<std::string> ADVSimpleScript::ResourcePath_;

std::vector<int> ADVSimpleScript::ResourceNums_;
std::vector<int> ADVSimpleScript::CX_;
std::vector<int> ADVSimpleScript::CY_;
std::vector<int> ADVSimpleScript::CDrawID_;

int ADVSimpleScript::LineWidth_	   = 0;
int ADVSimpleScript::ResourceNum_  = -1;
int ADVSimpleScript::MassegeX_	   = 0;
int ADVSimpleScript::MassegeY_	   = 0;
int ADVSimpleScript::StringX_	   = 0;
int ADVSimpleScript::StringY_	   = 0;
int ADVSimpleScript::BGX_		   = 0;
int ADVSimpleScript::BGY_		   = 0;
int ADVSimpleScript::BGID_		   = 0;
int ADVSimpleScript::CDrawCount_   = 0;
int ADVSimpleScript::BreakCount_   = 0;
int ADVSimpleScript::PrevPlayMusic = 0;

std::string ADVSimpleScript::filePath_ = "";
std::string ADVSimpleScript::CName_	   = "";

bool ADVSimpleScript::NowBreak_ = false;
bool ADVSimpleScript::DrawSkip_ = false;

void ADVSimpleScript::Load(std::string filePath)
{
	std::ifstream ifs_csv_file(filePath);
	std::string line;

	while (std::getline(ifs_csv_file, line))
	{
		std::istringstream linestream(line); // �e�s�̕�����X�g���[��
		std::string splitted; // �J���}����������
		while (std::getline(linestream, splitted, { ',' }))
		{
			std::istringstream ss; //������X�g���[���̏�����
			ss = std::istringstream(splitted); //������X�g���[��
			std::string text; // string�^�ۑ��p
			ss >> text; // istringstream��string�ɕϊ��������̂�ۑ�
			massegeList_.push_back(text); //�z��ɒǉ�
		}
	}
}

void ADVSimpleScript::Update()
{
	if (MassegeCount_ < massegeList_.size())
	{
		/*------���\�[�X�t�@�C���̓ǂݍ���-----*/

		if (massegeList_[MassegeCount_] == "ResourceLoad")
		{
			DrawSkip_ = true;
			ResourceNum_++;
			ResourceNums_.push_back(ResourceNum_);
			MassegeCount_++;
			if (massegeList_[MassegeCount_] == "Image")
			{
				MassegeCount_++;
				ResourcePath_.push_back(massegeList_[MassegeCount_]);
				ResourceNums_[ResourceNum_] = LoadGraph(ResourcePath_.back().c_str());
			}
			else if (massegeList_[MassegeCount_] == "Music")
			{
				MassegeCount_++;
				ResourcePath_.push_back(massegeList_[MassegeCount_]);
				ResourceNums_[ResourceNum_] = LoadSoundMem(ResourcePath_.back().c_str());
				PrevPlayMusic = ResourceNums_[ResourceNum_];
			}
			MassegeCount_++;
		}

		/*-------------------------------------*/

		/*-----BGM�̍Đ�-----*/

		else if (massegeList_[MassegeCount_] == "PlayBGM")
		{
			DrawSkip_ = true;
			MassegeCount_++;
			int playMusic = std::stoi(massegeList_[MassegeCount_].c_str());
			StopSoundMem(PrevPlayMusic);
			PlaySoundMem(playMusic, DX_PLAYTYPE_LOOP);
			PrevPlayMusic = playMusic;
			MassegeCount_++;
		}

		/*-------------------*/

		/*-----�w�i�̍��W�擾-----*/

		else if (massegeList_[MassegeCount_] == "BGX")
		{
			DrawSkip_ = true;
			MassegeCount_++;
			BGX_ = std::stoi(massegeList_[MassegeCount_]);
			MassegeCount_++;
		}
		else if (massegeList_[MassegeCount_] == "BGY")
		{
			DrawSkip_ = true;
			MassegeCount_++;
			BGY_ = std::stoi(massegeList_[MassegeCount_]);
			MassegeCount_++;
		}

		/*------------------------*/

		/*-----�w�i�̕`��-----*/

		else if (massegeList_[MassegeCount_] == "BGDraw")
		{
			DrawSkip_ = true;
			MassegeCount_++;
			BGID_ = std::stoi(massegeList_[MassegeCount_]);
			MassegeCount_++;
		}

		/*--------------------*/

		/*-----���b�Z�[�W�̕�������W�擾-----*/

		else if (massegeList_[MassegeCount_] == "MassegeX")
		{
			DrawSkip_ = true;
			MassegeCount_++;
			MassegeX_ = std::stoi(massegeList_[MassegeCount_]);
			MassegeCount_++;
		}
		else if (massegeList_[MassegeCount_] == "MassegeY")
		{
			DrawSkip_ = true;
			MassegeCount_++;
			MassegeY_ = std::stoi(massegeList_[MassegeCount_]);
			MassegeCount_++;
		}

		/*------------------------------------*/

		/*-----���b�Z�[�W�ȊO�̕�������W�擾-----*/

		else if (massegeList_[MassegeCount_] == "StringX")
		{
			DrawSkip_ = true;
			MassegeCount_++;
			StringX_ = std::stoi(massegeList_[MassegeCount_]);
			MassegeCount_++;
		}
		else if (massegeList_[MassegeCount_] == "StringY")
		{
			DrawSkip_ = true;
			MassegeCount_++;
			StringY_ = std::stoi(massegeList_[MassegeCount_]);
			MassegeCount_++;
		}

		/*----------------------------------------*/

		/*-----���b�Z�[�W�ȊO�̕�����̕`��-----*/

		else if (massegeList_[MassegeCount_] == "CName")
		{
			DrawSkip_ = true;
			MassegeCount_++;
			CName_ = massegeList_[MassegeCount_];
			MassegeCount_++;
		}

		/*--------------------------------------*/

		/*-----�L�����N�^�[�̍��W�擾-----*/

		else if (massegeList_[MassegeCount_] == "CX")
		{
			DrawSkip_ = true;
			MassegeCount_++;
			CX_.push_back(std::stoi(massegeList_[MassegeCount_]));
			MassegeCount_++;
		}
		else if (massegeList_[MassegeCount_] == "CY")
		{
			DrawSkip_ = true;
			MassegeCount_++;
			CY_.push_back(std::stoi(massegeList_[MassegeCount_]));
			MassegeCount_++;
		}

		/*--------------------------------*/

		/*-----�L�����N�^�[�̕`��-----*/

		else if (massegeList_[MassegeCount_] == "CDraw")
		{
			DrawSkip_ = true;
			MassegeCount_++;
			CDrawID_.push_back(std::stoi(massegeList_[MassegeCount_]));
			MassegeCount_++;
		}

		/*----------------------------*/

		/*-----�L�����N�^�[�̗����G����-----*/

		else if (massegeList_[MassegeCount_] == "CDrawEnd")
		{
			DrawSkip_ = true;
			MassegeCount_++;
			int eraseID = std::stoi(massegeList_[MassegeCount_]);
			for (int i = 0; i < CDrawID_.size(); i++)
			{
				if (CDrawID_[i] == eraseID)
				{
					CDrawID_.erase(CDrawID_.begin() + i);
					CX_.erase(CX_.begin() + i);
					CY_.erase(CY_.begin() + i);
				}
			}
			MassegeCount_++;
		}

		/*----------------------------------*/

		/*-----���s����-----*/

		else if (massegeList_[MassegeCount_] == "Break")
		{
			DrawSkip_ = true;
			MassegeCount_++;
			BreakCount_++;
			NowBreak_ = true;
		}

		/*------------------*/

		/*-----���s�����I��-----*/

		else if (massegeList_[MassegeCount_] == "BreakEnd")
		{
			DrawSkip_ = true;
			MassegeCount_++;
			BreakCount_ = 0;
			NowBreak_ = false;
		}

		/*----------------------*/
	}
}

void ADVSimpleScript::ImageDraw()
{
	/*-----���b�Z�[�W�����̉摜�`��-----*/

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

	/*-----���b�Z�[�W�����̕�����`��-----*/

	SetFontSize(FontSize);

	DrawString(StringX_, StringY_, CName_.c_str(), MassegeColor);

	if (DrawSkip_)
	{
		DrawSkip_ = false;
		return;
	}
	else
	{
		DrawString(MassegeX_, MassegeY_ + LineWidth_ * BreakCount_, massegeList_[MassegeCount_].c_str(), MassegeColor);
		if (NowBreak_)
		{
			for (int i = 0; i < BreakCount_; i++)
			{
				DrawString(MassegeX_, MassegeY_ + LineWidth_ * i, massegeList_[MassegeCount_ - ((BreakCount_ - 1 - i) * 2 + 2)].c_str(), MassegeColor);
			}
		}
	}

	SetFontSize(DefaultFontSize);

	/*------------------------------------*/
}

#endif
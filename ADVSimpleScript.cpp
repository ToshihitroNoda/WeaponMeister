#include "ADVSimpleScript.h"

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

int ADVSimpleScript::lineWidth_ = 0;
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
bool ADVSimpleScript::is_message_text_ = false;

void ADVSimpleScript::Init()
{
	MassegeCount  = 0;
	lineWidth_	  = 0;
	ResourceNum_  = -1;
	MassegeX_	  = 0;
	MassegeY_	  = 0;
	StringX_	  = 0;
	StringY_	  = 0;
	BGX_		  = 0;
	BGY_		  = 0;
	BGID_		  = 0;
	CDrawCount_	  = 0;
	BreakCount_	  = 0;
	PrevPlayMusic = 0;

	filePath_ = "";
	CName_ = "";

	NowBreak_ = false;
	DrawSkip_ = false;
	LoadEnd_ = false;
}

void ADVSimpleScript::Final()
{
	InitGraph();
	massegeList.clear();
	massegeList.shrink_to_fit();
	ResourcePath_.clear();
	ResourcePath_.shrink_to_fit();
	ResourceNums_.clear();
	ResourceNums_.shrink_to_fit();
	CX_.clear();
	CX_.shrink_to_fit();
	CY_.clear();
	CY_.shrink_to_fit();
	CDrawID_.clear();
	CDrawID_.shrink_to_fit();
}

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
			massegeList.push_back(text); //�z��ɒǉ�
		}
	}

	for (int i = 0; i < massegeList.size(); i++)
	{
		for (int j = 0; j < Commands_.size(); j++)
		{
			if (massegeList[MassegeCount] == Commands_[j])
				Update(); // csv�̓��̃R�}���h���`�悳��Ȃ��悤�ɐ��Update�񂵂Ă���
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
		is_message_text_ = false;
		while (!is_message_text_)
		{
			/*------���\�[�X�t�@�C���̓ǂݍ���-----*/

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

			/*-----BGM�̍Đ�-----*/

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

			/*-----�w�i�̍��W�擾-----*/

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

			/*-----�w�i�̕`��-----*/

			else if (massegeList[MassegeCount] == "BGDraw")
			{
				DrawSkip_ = true;
				MassegeCount++;
				BGID_ = std::stoi(massegeList[MassegeCount]);
				MassegeCount++;
			}

			/*--------------------*/

			/*-----���b�Z�[�W�̕�������W�擾-----*/

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

			/*-----���b�Z�[�W�ȊO�̕�������W�擾-----*/

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

			/*-----���b�Z�[�W�ȊO�̕�����̕`��-----*/

			else if (massegeList[MassegeCount] == "CName")
			{
				DrawSkip_ = true;
				MassegeCount++;
				CName_ = massegeList[MassegeCount];
				MassegeCount++;
			}

			/*--------------------------------------*/

			/*-----�L�����N�^�[�̍��W�擾-----*/

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

			/*-----�L�����N�^�[�̕`��-----*/

			else if (massegeList[MassegeCount] == "CDraw")
			{
				DrawSkip_ = true;
				MassegeCount++;
				CDrawID_.push_back(std::stoi(massegeList[MassegeCount]));
				MassegeCount++;
			}

			/*----------------------------*/

			/*-----�L�����N�^�[�̗����G����-----*/

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

			/*-----���s����-----*/

			else if (massegeList[MassegeCount] == "Break")
			{
				DrawSkip_ = true;
				MassegeCount++;
				BreakCount_++;
				NowBreak_ = true;
			}

			/*------------------*/

			/*-----���s�����I��-----*/

			else if (massegeList[MassegeCount] == "BreakEnd")
			{
				DrawSkip_ = true;
				MassegeCount++;
				BreakCount_ = 0;
				NowBreak_ = false;
			}

			/*----------------------*/
			else
				is_message_text_ = true;
		}
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
	lineWidth_ = FontSize;

	/*-----���b�Z�[�W�����̕�����`��-----*/

	SetFontSize(FontSize);

	if (DrawSkip_)
	{
		DrawSkip_ = false;
		return;
	}
	else
	{
		DrawString(StringX_, StringY_, CName_.c_str(), MassegeColor);

		DrawString(MassegeX_, MassegeY_ + lineWidth_ * BreakCount_, massegeList[MassegeCount].c_str(), MassegeColor);
		if (NowBreak_)
		{
			for (int i = 0; i < BreakCount_; i++)
			{
				DrawString(MassegeX_, MassegeY_ + lineWidth_ * i, massegeList[MassegeCount - ((BreakCount_ - 1 - i) * 2 + 2)].c_str(), MassegeColor);
			}
		}
	}

	SetFontSize(DefaultFontSize);

	/*------------------------------------*/
}
#include "ADVSimpleScript.h"

int ADVSimpleScript::MessageCount = 0;

std::vector<std::string> ADVSimpleScript::messageList;
std::vector<std::string> ADVSimpleScript::ResourcePath_;
std::vector<std::string> ADVSimpleScript::ResourceType_;
std::vector<std::string> ADVSimpleScript::Commands_
{ "ResourceLoad", "Image"   , "Music"  , "PlayMusic", "BGX"  , "BGY", "BGDraw",
  "MessageX"    , "MessageY", "StringX", "StringY"  , "CName", "CX" , "CY"    ,
  "CDraw"       , "CDrawEnd", "Break"  , "BreakEnd" };

std::vector<int> ADVSimpleScript::ResourceNums_;
std::vector<int> ADVSimpleScript::CX_;
std::vector<int> ADVSimpleScript::CY_;
std::vector<int> ADVSimpleScript::CDrawID_;

int ADVSimpleScript::lineWidth_    = 0;
int ADVSimpleScript::ResourceNum_  = -1;
int ADVSimpleScript::MessageX_     = 0;
int ADVSimpleScript::MessageY_     = 0;
int ADVSimpleScript::StringX_      = 0;
int ADVSimpleScript::StringY_      = 0;
int ADVSimpleScript::BGX_          = 0;
int ADVSimpleScript::BGY_          = 0;
int ADVSimpleScript::BGID_         = 0;
int ADVSimpleScript::CDrawCount_   = 0;
int ADVSimpleScript::BreakCount_   = 0;
int ADVSimpleScript::PrevPlayMusic = 0;

std::string ADVSimpleScript::filePath_ = "";
std::string ADVSimpleScript::CName_    = "";

bool ADVSimpleScript::NowBreak_        = false;
bool ADVSimpleScript::DrawSkip_        = false;
bool ADVSimpleScript::LoadEnd_         = false;
bool ADVSimpleScript::is_message_text_ = false;

void ADVSimpleScript::Init()
{
	MessageCount  = 0;
	lineWidth_    = 0;
	ResourceNum_  = -1;
	MessageX_     = 0;
	MessageY_     = 0;
	StringX_      = 0;
	StringY_      = 0;
	BGX_          = 0;
	BGY_          = 0;
	BGID_         = 0;
	CDrawCount_   = 0;
	BreakCount_   = 0;
	PrevPlayMusic = 0;

	filePath_ = "";
	CName_    = "";

	NowBreak_ = false;
	DrawSkip_ = false;
	LoadEnd_  = false;
}

void ADVSimpleScript::Final()
{
	for (int i = 0; i < ResourceType_.size(); i++)
	{
		if (ResourceType_[i] == "Image")
		{
			DeleteGraph(ResourceNums_[i]);
		}
		else if (ResourceType_[i] == "Music")
		{
			DeleteGraph(ResourceNums_[i]);
		}
	}
	ResourceType_.clear();
	messageList.clear();
	ResourcePath_.clear();
	ResourceNums_.clear();
	CX_.clear();
	CY_.clear();
	CDrawID_.clear();
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
			messageList.push_back(text); //�z��ɒǉ�
		}
	}

	for (int i = 0; i < messageList.size(); i++)
	{
		for (int j = 0; j < Commands_.size(); j++)
		{
			if (messageList[MessageCount] == Commands_[j])
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
	if (MessageCount < messageList.size())
	{
		is_message_text_ = false;
		while (!is_message_text_)
		{
			/*------���\�[�X�t�@�C���̓ǂݍ���-----*/

			if (messageList[MessageCount] == "ResourceLoad")
			{
				DrawSkip_ = true;
				ResourceNum_++;
				ResourceNums_.push_back(ResourceNum_);
				MessageCount++;
				if (messageList[MessageCount] == "Image")
				{
					MessageCount++;
					ResourceType_.push_back("Image");
					ResourcePath_.push_back(messageList[MessageCount]);
					ResourceNums_[ResourceNum_] = LoadGraph(ResourcePath_.back().c_str());
				}
				else if (messageList[MessageCount] == "Music")
				{
					MessageCount++;
					ResourceType_.push_back("Music");
					ResourcePath_.push_back(messageList[MessageCount]);
					ResourceNums_[ResourceNum_] = LoadSoundMem(ResourcePath_.back().c_str());
					PrevPlayMusic = ResourceNums_[ResourceNum_];
				}
				MessageCount++;
			}

			/*-------------------------------------*/

			/*-----BGM�̍Đ�-----*/

			else if (messageList[MessageCount] == "PlayBGM")
			{
				DrawSkip_ = true;
				MessageCount++;
				int playMusic = ResourceNums_[std::stoi(messageList[MessageCount])];
				StopSoundMem(PrevPlayMusic);
				PlaySoundMem(playMusic, DX_PLAYTYPE_LOOP);
				PrevPlayMusic = playMusic;
				MessageCount++;
				ChangeVolumeSoundMem(std::stoi(messageList[MessageCount]), playMusic);
				MessageCount++;
			}

			/*-------------------*/

			/*-----�w�i�̍��W�擾-----*/

			else if (messageList[MessageCount] == "BGX")
			{
				DrawSkip_ = true;
				MessageCount++;
				BGX_ = std::stoi(messageList[MessageCount]);
				MessageCount++;
			}
			else if (messageList[MessageCount] == "BGY")
			{
				DrawSkip_ = true;
				MessageCount++;
				BGY_ = std::stoi(messageList[MessageCount]);
				MessageCount++;
			}

			/*------------------------*/

			/*-----�w�i�̕`��-----*/

			else if (messageList[MessageCount] == "BGDraw")
			{
				DrawSkip_ = true;
				MessageCount++;
				BGID_ = std::stoi(messageList[MessageCount]);
				MessageCount++;
			}

			/*--------------------*/

			/*-----���b�Z�[�W�̕�������W�擾-----*/

			else if (messageList[MessageCount] == "MessageX")
			{
				DrawSkip_ = true;
				MessageCount++;
				MessageX_ = std::stoi(messageList[MessageCount]);
				MessageCount++;
			}
			else if (messageList[MessageCount] == "MessageY")
			{
				DrawSkip_ = true;
				MessageCount++;
				MessageY_ = std::stoi(messageList[MessageCount]);
				MessageCount++;
			}

			/*------------------------------------*/

			/*-----���b�Z�[�W�ȊO�̕�������W�擾-----*/

			else if (messageList[MessageCount] == "StringX")
			{
				DrawSkip_ = true;
				MessageCount++;
				StringX_ = std::stoi(messageList[MessageCount]);
				MessageCount++;
			}
			else if (messageList[MessageCount] == "StringY")
			{
				DrawSkip_ = true;
				MessageCount++;
				StringY_ = std::stoi(messageList[MessageCount]);
				MessageCount++;
			}

			/*----------------------------------------*/

			/*-----���b�Z�[�W�ȊO�̕�����̕`��-----*/

			else if (messageList[MessageCount] == "CName")
			{
				DrawSkip_ = true;
				MessageCount++;
				CName_ = messageList[MessageCount];
				MessageCount++;
			}

			/*--------------------------------------*/

			/*-----�L�����N�^�[�̍��W�擾-----*/

			else if (messageList[MessageCount] == "CX")
			{
				DrawSkip_ = true;
				MessageCount++;
				CX_.push_back(std::stoi(messageList[MessageCount]));
				MessageCount++;
			}
			else if (messageList[MessageCount] == "CY")
			{
				DrawSkip_ = true;
				MessageCount++;
				CY_.push_back(std::stoi(messageList[MessageCount]));
				MessageCount++;
			}

			/*--------------------------------*/

			/*-----�L�����N�^�[�̕`��-----*/

			else if (messageList[MessageCount] == "CDraw")
			{
				DrawSkip_ = true;
				MessageCount++;
				CDrawID_.push_back(std::stoi(messageList[MessageCount]));
				MessageCount++;
			}

			/*----------------------------*/

			/*-----�L�����N�^�[�̗����G����-----*/

			else if (messageList[MessageCount] == "CDrawEnd")
			{
				DrawSkip_ = true;
				MessageCount++;
				int eraseID = std::stoi(messageList[MessageCount]);
				for (int i = 0; i < CDrawID_.size(); i++)
				{
					if (CDrawID_[i] == eraseID)
					{
						CDrawID_.erase(CDrawID_.begin() + i);
						CX_.erase(CX_.begin() + i);
						CY_.erase(CY_.begin() + i);
					}
				}
				MessageCount++;
			}

			/*----------------------------------*/

			/*-----���s����-----*/

			else if (messageList[MessageCount] == "Break")
			{
				DrawSkip_ = true;
				MessageCount++;
				BreakCount_++;
				NowBreak_ = true;
			}

			/*------------------*/

			/*-----���s�����I��-----*/

			else if (messageList[MessageCount] == "BreakEnd")
			{
				DrawSkip_ = true;
				MessageCount++;
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

void ADVSimpleScript::MessageDraw(int MassegeColor, int FontSize, int DefaultFontSize)
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

		DrawString(MessageX_, MessageY_ + lineWidth_ * BreakCount_, messageList[MessageCount].c_str(), MassegeColor);
		if (NowBreak_)
		{
			for (int i = 0; i < BreakCount_; i++)
			{
				DrawString(MessageX_, MessageY_ + lineWidth_ * i, messageList[MessageCount - ((BreakCount_ - 1 - i) * 2 + 2)].c_str(), MassegeColor);
			}
		}
	}

	SetFontSize(DefaultFontSize);

	/*------------------------------------*/
}
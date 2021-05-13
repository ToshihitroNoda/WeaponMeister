#include "Adv.h"
#include "Input.h"
#include "Image.h"

int Adv::day = 0;

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


void Adv::Final()
{

}

void Adv::Update()
{
	if (Input::GetButtonDown(PAD_INPUT_1))
	{
		MassegeCount_++;
	}

	if (MassegeCount_ >= massegeList_.size())
	{
		sm.LoadScene("StageSelection");
	}

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

void Adv::Draw()
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

	DrawGraph(WindowX_, WindowY_, Image::textWindow, TRUE);

	/*-----���b�Z�[�W�����̕�����`��-----*/

	DrawString(StringX_, StringY_, CName_.c_str(), gm.colorWhite);

	if (DrawSkip_)
	{
		DrawSkip_ = false;
		return;
	}
	else
	{
		DrawString(MassegeX_, MassegeY_ + LineWidth_ * BreakCount_, massegeList_[MassegeCount_].c_str(), gm.colorWhite);
		if (NowBreak_)
		{
			for (int i = 0; i < BreakCount_; i++)
			{
				DrawString(MassegeX_, MassegeY_ + LineWidth_ * i, massegeList_[MassegeCount_ - ((BreakCount_ - 1 - i) * 2 + 2)].c_str(), gm.colorWhite);
			}
		}
	}

	/*------------------------------------*/

	if (IconFlashCount_ % Divisor_ < DrawFlashTiming_)
	{
		DrawGraph(CursorX_, CursorY_, Image::textCursor, TRUE);
	}
	IconFlashCount_++;
}

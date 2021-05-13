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

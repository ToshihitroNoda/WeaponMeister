#ifndef TIMER_H_
#define TIMER_H_

// �}���`�v���b�g�t�H�[���Ή��̎�����舵���N���X(C++11�Ή��Ȃ�ڐA�e��)

#include <chrono> // ���x�̍��������𓾂�(C++�Ȃ�Windows,Mac�ȂǐF��Ȋ��Ŏg����)
#include <thread> // �����x�~sleep_for���邽�߂ɕK�v
#include <vector> // ���X�gvector�ɕK�v
#include <map>	// �����^�A�z�z��ɕK�v
#include <memory> // shared_ptr�񂵓ǂ݃|�C���^�ɕK�v
#include <string> // ������string�^�ɕK�v
#include <sstream> // ostringstream�ɕK�v �W���o��(ostringstream�ŕ�����ɕW���o�͂�)
#include <iomanip> // ���Ԃ̕�����o��put_time()�ɕK�v


#include "Singleton.h"

class MyTimer : public Singleton<MyTimer>
{
public:
	friend class Singleton<MyTimer>; // Singleton �ł̃C���X�^���X�쐬�͋���

	// �ŏ���system_clock��steady_clock�̗����Ō��ݎ��Ԃ��擾
	// ��system_clock�́yWindow�Ȃ�OS�̎���(���[�U�[���ύX�����犪���߂������肤��)�z
	// ��steady_clock�́y��OS�Ɉˑ����Ȃ�����(�s�t�Ȃ̂Ŏ��Ԍv���Ɍ����Ă���)�z
	std::chrono::system_clock::time_point systemInitTime = std::chrono::system_clock::now();
	std::chrono::steady_clock::time_point steadyInitTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point steadyNowTime = std::chrono::steady_clock::now();
	//
	std::chrono::system_clock::time_point systemTimeFromStart = UpdateSystemTimeFromStart();

	// ������ۊǂ��镶����y���ӁzUpdateSystemTimeFromStart()�Ă΂Ȃ������͍ŐV�ɍX�V����Ȃ�
	std::string timeStringSystemClock = GetTimeString("%Y�N%m��%d��%H��%M��%S�b");
	float timeScale = 1.0f;//[�����@�\]main.cpp�ŉ�ʂ�`�����x�ƘA�������ăX���[���[�V�����⑁�����
	bool isTimeScaleMode = false; //[�����@�\]�X���[���[�V�����A�����胂�[�h��ON OFF

	// �C�x���g�̃^�C�}�[(vector��list�̂ǂ���̔z�񂩖����������ւ�sort�O���vector��)
	//[list��vector��r] http://vivi.dyndns.org/tech/cpp/list.html#list
	//[�����d�A�z�z��] http://vivi.dyndns.org/tech/cpp/multimap.html
	std::map<unsigned long, std::string> eventIdToName; // ����:ID����C�x���g��
	std::map<unsigned long, std::string> eventIdToInfo; // ����:ID����C�x���g���
	std::multimap<std::string, unsigned long> eventNameToId; // ����:�C�x���g������ID
	std::map<unsigned long, std::chrono::system_clock::time_point> eventIdToTime; // ����:ID���玞��
	unsigned long newEventId = 0;
	struct Event
	{	// �����ɍ��킹���C�x���g��o�^�ł���
		Event(unsigned long id, std::string name, std::string info, std::chrono::system_clock::time_point time)
			: id{ id }, name{ name }, info{ info }, time{ time }, isDead{ false } { /*�R���X�g���N�^*/ };
		//~Event(); // �f�X�g���N�^
		unsigned long id; // �C�x���g�Ǘ�ID
		std::string name; // �C�x���g�̖��O
		std::string info; // �C�x���g�̏��
		std::chrono::system_clock::time_point time; //�@�C�x���g�̎���
		bool isDead; //�C�x���g�I�����Ƀt���O��true�ɂ���
	};

	// �����牽�~���b��ɋN����C�x���g��ǉ�����
	unsigned long AddEventAtMilliSecAfterNow(std::string eventName, unsigned long milliSecFromNow, std::string eventInfo = "")
	{
		newEventId++; // �V�KID�̍X�V�J�E���g
		systemTimeFromStart = UpdateSystemTimeFromStart(); //�����̎擾
		std::chrono::system_clock::time_point eventTime
			= systemTimeFromStart + std::chrono::milliseconds(milliSecFromNow); // �C�x���g�\�莞�����v�Z
		//std::shared_ptr<Event> newEvent = std::make_shared<Event>(newEventId, eventName, eventInfo, eventTime);
		//eventTimes.push_back(newEvent); // ���X�g�ɃC�x���g�̃^�C�~���O��o�^
		// ������ID�o�^
		eventNameToId.insert(std::pair<std::string, unsigned long>(eventName, newEventId));
		eventIdToName[newEventId] = eventName; // �����ɃC�x���g���o�^
		eventIdToInfo[newEventId] = eventInfo; // �����ɃC�x���g���o�^
		eventIdToTime[newEventId] = eventTime; // �����Ɏ����o�^
	}


	// �������܂łɋN�������C�x���g����Ԃ�(���o���č폜�͂��Ȃ�)
	struct Event Back_EventHappen(std::string eventName = "")
	{
		systemTimeFromStart = UpdateSystemTimeFromStart(); //�����̎擾
		int count = 0;
		if (eventName != "")
		{	// �C�x���g���Ɏw�肪����΃C�x���g�����i���Ď擾
			int num = (int)(eventNameToId.count(eventName));
			auto itr = eventNameToId.find(eventName); // �������ŏ��̃C�e���[�^���
			for (int i = 0; i < num; i++)
			{	// �������C�x���g���C�e���[�^���itr�ł��ǂ�
				unsigned long eventId = itr->second;
				if (eventIdToTime[eventId] > systemTimeFromStart)
				{	//�������C�x���g��ԋp����
					Event findevent(eventId, eventName, eventIdToInfo[eventId], eventIdToTime[eventId]);
					return findevent;
				}
				itr++; //���̃C�e���[�^�������ǂ�(++����Ǝ��̖���)
			}
		}
		else
		{	// �C�x���g���Ɏw�肪������ΑS���̎�����
			for (auto itr = eventNameToId.begin(); itr != eventNameToId.end(); ++itr)
			{	// �������C�x���g���C�e���[�^���itr�ł��ǂ�
				unsigned long eventId = itr->second;
				if (eventIdToTime[eventId] > systemTimeFromStart)
				{	//�������C�x���g��ԋp����
					Event findevent(eventId, eventName, eventIdToInfo[eventId], eventIdToTime[eventId]);
					return findevent;
				}
				itr++; //���̃C�e���[�^�������ǂ�(++����Ǝ��̖���)
			}
		}

		//�C�x���g��������Ȃ�������ˋ�ID=0��isDead=true�C�x���g��ԋp
		Event no_event(0, "", "", systemTimeFromStart);
		no_event.isDead = true; // ���łɏI���C�x���g�Ƃ��ĉˋ�C�x���g��Ԃ�
		return no_event; // if(isDead)�Ŕ��肵�Ė����C�x���g�����ʂ��Ă�
	}

	// �������܂łɋN�������C�x���g�����o���y�Ɠ����Ɂz�폜����
	struct Event PopBack_EventHappen(std::string eventName = "")
	{
		systemTimeFromStart = UpdateSystemTimeFromStart(); //�����̎擾
		int count = 0;
		if (eventName != "")
		{	// �C�x���g���Ɏw�肪����΃C�x���g�����i���Ď擾
			int num = (int)(eventNameToId.count(eventName));
			auto itr = eventNameToId.find(eventName); // �������ŏ��̃C�e���[�^���
			for (int i = 0; i < num; i++)
			{	// �������C�x���g���C�e���[�^���itr�ł��ǂ�
				unsigned long eventId = itr->second;
				if (eventIdToTime[eventId] > systemTimeFromStart)
				{	//�������C�x���g��ԋp����
					Event findevent(eventId, eventName, eventIdToInfo[eventId], eventIdToTime[eventId]);
					// �폜������������
					eventNameToId.erase(itr);
					eventIdToName.erase(eventId); // �����̃C�x���g���폜
					eventIdToInfo.erase(eventId); // �����̃C�x���g���폜
					eventIdToTime.erase(eventId); // �����̎����폜
					return findevent;//�������C�x���g��ԋp����
				}
				itr++; //���̃C�e���[�^�������ǂ�(++����Ǝ��̖���)
			}
		}
		else
		{	// �C�x���g���Ɏw�肪������ΑS���̎�����
			for (auto itr = eventNameToId.begin(); itr != eventNameToId.end(); ++itr)
			{	// �������C�x���g���C�e���[�^���itr�ł��ǂ�
				unsigned long eventId = itr->second;
				if (eventIdToTime[eventId] > systemTimeFromStart)
				{	//�������C�x���g��ԋp����
					Event findevent(eventId, eventName, eventIdToInfo[eventId], eventIdToTime[eventId]);
					// �폜������������
					eventNameToId.erase(itr);
					eventIdToName.erase(eventId); // �����̃C�x���g���폜
					eventIdToInfo.erase(eventId); // �����̃C�x���g���폜
					eventIdToTime.erase(eventId); // �����̎����폜
					return findevent;
				}
				itr++; //���̃C�e���[�^�������ǂ�(++����Ǝ��̖���)
			}
		}

		//�C�x���g��������Ȃ�������ˋ�ID=0��isDead=true�C�x���g��ԋp
		Event no_event(0, "", "", systemTimeFromStart);
		no_event.isDead = true; // ���łɏI���C�x���g�Ƃ��ĉˋ�C�x���g��Ԃ�
		return no_event; // if(isDead)�Ŕ��肵�Ė����C�x���g�����ʂ��Ă�
	}

	// �C�x���g�̃N���A
	void ClearIsDeadEvent(std::string eventName = "")
	{	// isDead��true����Ȃ��C�x���g�������Ȃ�܂Ō�납��폜
		while (Back_EventHappen(eventName).isDead != true)
		{	// �C�x���g�̍폜(vector��pop_back�Ɠ���)
			PopBack_EventHappen(eventName); //�폜
		}
	}

	// �N�����Ԃ̋L�^�̏�����/���Z�b�g(Init�������΍Ď擾���ł���)
	void Init()
	{
		// �ŏ���system_clock��steady_clock�̗����Ō��ݎ��Ԃ��擾(�Ď擾��)
		systemInitTime = std::chrono::system_clock::now();
		steadyInitTime = std::chrono::steady_clock::now();
		// �o�^�C�x���g�^�C�~���O�̃��X�g�����Z�b�g
		//eventTimes.clear();
		eventIdToName.clear();
		eventIdToInfo.clear();
		eventNameToId.clear();
		eventIdToTime.clear();
		newEventId = 0;
	}


	// ��������OS�ɍ��E���ꂸ���߂�(�v�Z���ʂ�systemTimeFromStart�ɕۊ�)
	std::chrono::system_clock::time_point UpdateSystemTimeFromStart()
	{
		steadyNowTime = std::chrono::steady_clock::now(); //�������𓾂�(OS�̎�������Ȃ���)
		// �J�n����steady_clock::now�Ƃ̍����Ƃ��āA�J�n����system_clock::now�ɑ���
		// [�Q�l] https://techblog.kayac.com/steady_clock
		systemTimeFromStart =
			systemInitTime + std::chrono::duration_cast<std::chrono::seconds>(steadyNowTime - steadyInitTime);
		return systemTimeFromStart;
	}

	// �����������̕�����t�H�[�}�b�g�œ���(�������̂�steadyNowTime��timeStringSystemClock�ɕۊ�)
	// �o�͂�"%c"�Ȃ�t�H�[�}�b�g��[Mon Nov 27 10:58:32 2017]
	// "%Y�N%m��%d��%H��%M��%S�b"�Ȃ�[2020�N12��11��14��30��15�b](�f�t�H���g)
	// [�t�H�[�}�b�g��] https://cpprefjp.github.io/reference/chrono/local_time.html
	std::string GetTimeString(const char* timeStringFormat = "%Y�N%m��%d��%H��%M��%S�b")
	{
		systemTimeFromStart = UpdateSystemTimeFromStart();//��������OS�����ɍ��E���ꂸ����

		// �����^�C�v�^��system_clock��time_point�^����time_t�^�ɕϊ�����B
		std::time_t timeFromStart = std::chrono::system_clock::to_time_t(systemTimeFromStart);
		// ���[�J���^�C���𓾂�(���[�J���^�C���ɂ��Ă͈ȉ������N�Q��)
		// https://programming.pc-note.net/c/time.html
		struct tm localTimeFromStart;
		localtime_s(&localTimeFromStart, &timeFromStart);
		//�yostringstream�z�͕�����X�g���[����<<���Z�q�Ȃǂ̕��@�Ńf�[�^�𗬂�����ł���
		// https://programming-place.net/ppp/contents/cpp/library/029.html#write_to_string_stream
		std::ostringstream oss;
		//�����̈�s�ŕ�����X�g���[���ɗ�������
		oss << std::put_time(&localTimeFromStart, timeStringFormat) << std::endl;

		timeStringSystemClock = oss.std::ostringstream::str(); //str()�ŕ�����string�����ĕۊ�
		return timeStringSystemClock; //�������𕶎���Ƃ��ĕԂ�
	}


	// Init���Ă��猻�݂܂ł̌o�ߎ��Ԃ𓾂�(�P��Tick = 100�i�m�b = 1/10000000�b)
	long GetElapsedTicks()
	{	// �������X�V
		UpdateSystemTimeFromStart();
		// Init���Ă��猻�݂܂ł̌o�ߎ���(�i�m�b)
		auto durationFromInit = std::chrono::duration_cast<std::chrono::nanoseconds>(steadyNowTime - steadyInitTime);
		// Tick���B1Tick = 100�i�m�b = 1/10000000�b
		return (long)(durationFromInit.count() / 100);
	}

	// �w��i�m�b �v���O�������x�~
	void SleepForNanoSec(int waittime)
	{	// �w��i�m�b �v���O�������x�~
		std::this_thread::sleep_for(std::chrono::nanoseconds(waittime));
	}

	// �w��}�C�N���b �v���O�������x�~
	void SleepForMicroSec(int waittime)
	{	// �w��~���b �v���O�������x�~
		std::this_thread::sleep_for(std::chrono::microseconds(waittime));
	}

	// �w��~���b �v���O�������x�~
	void SleepForMilliSec(int waittime)
	{	// �w��~���b �v���O�������x�~
		std::this_thread::sleep_for(std::chrono::milliseconds(waittime));
	}

	// �w�� �b �v���O�������x�~
	void SleepForSec(int waittime)
	{	// �w�� �b �v���O�������x�~
		std::this_thread::sleep_for(std::chrono::seconds(waittime));
	}

	// �w�� �� �v���O�������x�~
	void SleepForMinutes(int waittime)
	{	// �w�� �� �v���O�������x�~
		std::this_thread::sleep_for(std::chrono::minutes(waittime));
	}

protected:
	// �O������̃C���X�^���X�쐬�͋֎~
	MyTimer() {};
	//�O������̃C���X�^���X�j�����֎~
	virtual ~MyTimer() {};
};

#endif

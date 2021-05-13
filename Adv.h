#ifndef ADV_H_
#define ADV_H_

#include "Scene.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "Screen.h"

class Adv : public Scene
{
public:	
	GameManager& gm  = GameManager::GetInstance();
	SceneManager& sm = SceneManager::GetInstance(); // シーンマネージャへの参照

	Adv() : Scene()
	{
		this->tag = "Adv";
	}

	void Init() override;
	void Final() override;
	void Update() override;
	void Draw() override;

	static int day;

private:
	const int WindowHeight		= 280;
	const int WindowX_			= 5;
	const int WindowY_			= Screen::Height - WindowHeight;
	const int CursorX_			= 1150;
	const int CursorY_			= 630; 
	const int DrawFlashTiming_	= 20;
	const int Divisor_			= 30;

	int IconFlashCount_ = 0;

	/*-----メッセージ処理用メンバ変数-----*/
	
	int MassegeCount_ = 0;

	const int LineWidth_ = 20;
	std::string filePath_ = "";
	std::vector<std::string> massegeList_;

	std::vector<int> ResourceNums_;
	std::vector<std::string> ResourcePath_;
	std::vector<int> CX_;
	std::vector<int> CY_;
	std::vector<int> CDrawID_;
	int ResourceNum_   = -1;
	int MassegeX_	   = 0;
	int MassegeY_	   = 0;
	int StringX_	   = 0;
	int StringY_	   = 0;
	int BGX_		   = 0;
	int BGY_		   = 0;
	int BGID_		   = 0;
	int CDrawCount_    = 0;
	int BreakCount_	   = 0;
	int PrevPlayMusic  = 0;
	std::string CName_ = "";
	bool NowBreak_	   = false;
	bool DrawSkip_	   = false;

	/*----------------------------------*/
};

#endif


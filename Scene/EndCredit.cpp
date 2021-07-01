#include "EndCredit.h"
#include "../Music.h"
#include <DxLib.h>

void EndCredit::Init()
{   
	gm.image.Load(tag);
	// ミリ秒でエンディングの再生時間を取得してるので*1000して秒に直してから*フレーム数
	totalSoundTime_ = GetSoundTotalTime(Music::ed) / 1000 * 60;
	PlaySoundMem(Music::ed, DX_PLAYTYPE_BACK);
}

void EndCredit::Final()
{

}

void EndCredit::Update()
{
	if (scrollCounter_ < totalSoundTime_)
	{
		scrollCounter_++;
		creditGraphY_ -= 0.53;
	}
	else
		creditScrollEnd_ = true;
	if (creditScrollEnd_)
	{
		isDead = true;
	}
}

void EndCredit::Change()
{
	remove("savedata.dat");
	sm.LoadScene("Title");
}

void EndCredit::Draw()
{
	DrawGraphF(0.0, creditGraphY_, gm.image.endCredit, TRUE);
}
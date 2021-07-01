#include "EndCredit.h"
#include "../Music.h"
#include <DxLib.h>

void EndCredit::Init()
{   
	gm.image.Load(tag);
	// �~���b�ŃG���f�B���O�̍Đ����Ԃ��擾���Ă�̂�*1000���ĕb�ɒ����Ă���*�t���[����
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
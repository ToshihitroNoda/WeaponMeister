#include <DxLib.h>
#include <assert.h>

#include "Screen.h"
#include "Game.h"

#include "MyTimer.h"

int TargetFPS = 60; // �ڕW��FPS(Frame Per Second, 1�b������̃t���[����)
static bool EnableFrameSkip = true; // �����׎��Ƀt���[���X�L�b�v���邩�ifalse�̏ꍇ�͏��������i�X���[�j�j
double MaxAllowSkipTime = 0.2; // �t���[���X�L�b�v����ő�Ԋu�i�b�j�B����ȏ�̊Ԋu���󂢂��ꍇ�̓X�L�b�v�����ɏ��������ɂ���B
long IntervalTicks = (long)(1.0 / TargetFPS * 10000000); // �t���[���Ԃ�Tick���B1Tick = 100�i�m�b = 1/10000000�b
int MaxAllowSkipCount = (int)(TargetFPS * MaxAllowSkipTime);

static long nextFrameTicks = IntervalTicks; // ���̃t���[���̖ڕW����
static int skipCount = 0; // ����A���Ńt���[���X�L�b�v������
static long fpsTicks = 0; // FPS�v���̂��߂�Ticks�B
static int fpsFrameCount = 0; // FPS�v���̂��߂̃t���[���J�E���g�B60�񐔂��邲�ƂɁA�v�������Ԃ���FPS���Z�o����B

/// <summary>
/// ���݂�FPS�iFrame per Second�j
/// </summary>
static float CurrentFPS;


// static�֐��͂ǂ��ł��Ăׂ�֐�
static void GameDraw(Game& game)
{
	ClearDrawScreen();// ��U�L�����o�X�����ꂢ�ɂ܂������
	game.Draw(); // �p���p������̕`�揈��
	ScreenFlip(); // ���ŕ`���Ă������p���p�������\�ʂɓ���ւ��t���b�v
	skipCount = 0; // �t���[���X�L�b�v�̃J�E���g�����Z�b�g
}

// �ݒ��ʂ́y�����J�[�z���y�V�X�e���z�́y�T�u�V�X�e���z��Windows(SYSTEM:WINDOWS)�ɐݒ肷���WinMain����v���O�������J�n����
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_  LPSTR lpCmdLine, _In_  int nCmdShow)
{
	// [Windows�̋@�\]���̃v���O�������s�̏����D��x���グ��
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

	// �����������Ƃ̓��j�^�[�ւ̕`�悪��������܂ŏ����S�̂��~���A
		// �`�揈���ƍX�V�����̊Ԋu��o�����ƂȂ�悤�ɏ����̊Ԋu�𒲐����邱��
		// https://qiita.com/Seiten_Minagawa/items/615312ebe5e688ffee7f
		// ��ʃ��t���b�V�����[�g�ƖڕW�t���[�����[�g���������ꍇ�͐���������L���ɁA�������Ȃ��ꍇ�͐��������𖳌��ɂ���
	SetWaitVSyncFlag(GetRefreshRate() == TargetFPS ? TRUE : FALSE);

	// ��ʃ��[�h�̐ݒ�
	SetWindowSize(Screen::width, Screen::height);// �E�B���h�E�T�C�Y1280�~720(������SetGraphMode�̃T�C�Y���قȂ�Ɖ摜���䂪��)
	SetGraphMode(Screen::width, Screen::height, 32); // ��ʃT�C�Y1280�~720�̃J���[�r�b�g��32�r�b�g�ŋN��
	SetMainWindowText("WeaponMeister");//���̍s�ŃG���[�ɂȂ�����y�ݒ�z�}���`�o�C�g�����Z�b�g���Ԉ���Ă邩��
	ChangeWindowMode(TRUE);//�t���X�N���[���\�����E�B���h�E�\����
	SetAlwaysRunFlag(TRUE); // �E�B���h�E����A�N�e�B�u�ł����삳����

	//DX���C�u�����̏�����
	if (DxLib_Init() < 0)
	{
		// �G���[���o���璼���ɏI��
		return -1;
	}

	SetMouseDispFlag(TRUE);// ������FALSE�ɂ���ƃ}�E�X�J�[�\����\��
	//�\�����Ă���X�N���[���̌��ŉB��Ď��ɕ`���摜���ɕ`�����[�h
	// ����ƃy�A��ScreenFlip();�ł��̃y�[�W�Ɠ���ւ��ł������h��
	SetDrawScreen(DX_SCREEN_BACK);
	SetUseTransColor(FALSE); // �摜�̎w��F�𓧉߂���@�\�𖳌���

	SetCameraNearFar(1.0f, 2500.0f); // �`�拗���̐ݒ�
	//SetValidMousePointerWindowOutClientAreaMoveFlag(FALSE);

	// ����܂�Init�ł���Ă��Ă�����������
	Game game;
	game.Init(); // game��Init����

	// �Ǝ������N���X�̎Q�Ƃ𓾂�(�V���O���g���^)
	MyTimer& timer = MyTimer::GetInstance();
	ScreenFlip();

	timer.Init(); // �����v���J�n

	// �A�j���[�V����(�p���p������)�ɂ���ɂ�While��
	while (ProcessMessage() == 0)
	{// ProcessMessage() == 0�ɂȂ�̂́~�{�^�����������Ƃ��Ȃ�
		// FPS�̌v��(FPS = 1�b������̃p���p�����文��)
		fpsFrameCount++;
		if (fpsFrameCount >= 60)
		{   // �o�ߎ��� 1Tick = 100�i�m�b = 1/10000000�b (elasped=�o��)
			long elapsedTicks = timer.GetElapsedTicks() - fpsTicks;
			float elapsedSec = (float)elapsedTicks / 10000000;
			CurrentFPS = fpsFrameCount / elapsedSec;// ���݂�FPS

			fpsFrameCount = 0; // 60����������0���Z�b�g
			// 60���������猻�݂�FPS(�p���p�����x)���L�^
			fpsTicks = timer.GetElapsedTicks();
		}

		game.Update(); //�Q�[���̍X�V����

	   //[�����@�\]�X���[���[�V�����A������(time.timeScale��0.5��2�{��2.0��1/2�X���[)
		if (timer.isTimeScaleMode && timer.timeScale > 0)
		{   // �t���[�����[�g���Čv�Z���������X���[���[�V����
			TargetFPS = (int)(60 / timer.timeScale); // �ڕW��FPS(Frame Per Second, 1�b������̃t���[����)
			MaxAllowSkipTime = 0.2; // �t���[���X�L�b�v����ő�Ԋu�i�b�j�B����ȏ�̊Ԋu���󂢂��ꍇ�̓X�L�b�v�����ɏ��������ɂ���B
			IntervalTicks = (long)(1.0 / TargetFPS * 10000000); // �t���[���Ԃ�Tick���B1Tick = 100�i�m�b = 1/10000000�b
			MaxAllowSkipCount = (int)(TargetFPS * MaxAllowSkipTime);
		}

		// ������������DX�ݒ�Ō����Ă���Ȃ�DX���C�u������Wait������C������(�t���[���X�L�b�v���������ł��)
		if (GetWaitVSyncFlag() == TRUE && timer.isTimeScaleMode == false)
		{   // ���t���[���X�L�b�v�Ƃ͕`�揈�����d�����Ƀp���p�������1����΂���?
			if (EnableFrameSkip)
			{   // ���]�������� = ���̃p���p���\�莞�� - ���݂̎���
				long waitTicks = nextFrameTicks - timer.GetElapsedTicks();
				if (waitTicks < 0) // �ڕW�������I�[�o�[���Ă���
				{   //�����܂薟��̃p���p���y�[�W�����΂��ƃL���������[�v���Č�����̂Ō��x�����Ă�
					if (skipCount < MaxAllowSkipCount) // �A���t���[���X�L�b�v�����ő�X�L�b�v���𒴂��Ă��Ȃ����
					{
						skipCount++; // �t���[���X�L�b�v�i�`�揈�����΂��j
					}
					else
					{   // �ő�X�L�b�v���𒴂��Ă�̂ŁA�t���[���X�L�b�v���Ȃ��ŕ`��
						nextFrameTicks = timer.GetElapsedTicks();
						GameDraw(game); // �����x�z���ŃX���[�`�揈���ɐؑւ�
					}
				}
				else
				{   // �ڕW����OK�Ȃ̂Ńt���[���X�L�b�v���Ȃ��ŕ`��
					// ��DX���C�u�����������ŉt����60Hz�ƃ^�C�~���O���킹�ĕ`��
					GameDraw(game); // �`�揈��
				}
				// ���̃p���p���\�莞����IntervalTicks(�P��:100�i�m�b)����
				nextFrameTicks += IntervalTicks;
			}
			else
			{   // ������else�͉��������Ă��t���[���X�L�b�v���Ȃ��ݒ�̎��ɗ���
				GameDraw(game); // ���X���[�`�揈��
			}
		}
		else
		{   // ������������DX�ݒ�Ły�����ĂȂ��z�Ȃ�Wait���������͂ł��(�t���[���X�L�b�v�������ł��)
			// ��������̓t���[���X�L�b�v����(waitTicks = ���̃p���p���\�莞�� - ���݂̎���)
			long waitTicks = nextFrameTicks - timer.GetElapsedTicks(); // �]�������ԁi�ҋ@���K�v�Ȏ��ԁj
			if (EnableFrameSkip && waitTicks < 0)
			{   // ���܂薟��̃p���p���y�[�W�����΂��ƃL���������[�v���Č�����̂Ō��x�����Ă�
				if (skipCount < MaxAllowSkipCount)
				{
					skipCount++; // �t���[���X�L�b�v�i�`�揈�����΂��j
				}
				else
				{   // ���̃p���p���\�莞�����������ɐݒ肷��̂Ŏ�����Βx���waitTicks < 0�ɂȂ�
					nextFrameTicks = timer.GetElapsedTicks();
					GameDraw(game); //�x����X���[���[�V�����ŕ`���Ă䂭�ݒ�̎��͂���
				}
			}
			else
			{   // �����͂�Wait����
				if (waitTicks > 20000) // ����2�~���b�ȏ�҂K�v������
				{   // ������Time�N���X��Sleep�ň�莞�ԃv���O�����x�~
					// https://marycore.jp/prog/objective-c/sleep-process/#sleep_for
					// Sleep�͎w�肵�����ԂŃs�b�^���߂��Ă���킯�ł͂Ȃ��̂ŁA
					// �]�T�������āA�u�҂��Ȃ���΂Ȃ�Ȃ�����-2�~���b�vSleep����
					int waitMillsec = (int)(waitTicks / 10000) - 2;
					timer.SleepForMilliSec(waitMillsec);
				}

				// ���Ԃ�����܂ŉ������Ȃ����[�v���񂵂đҋ@����
				while (timer.GetElapsedTicks() < nextFrameTicks)
				{   // ����̎��ԂɂȂ�܂ŋ󃋁[�v
				}

				GameDraw(game); // ����̎��ԂɂȂ�����`�揈��
			}
			// ���̃p���p���\�莞����IntervalTicks(�P��:100�i�m�b)����
			nextFrameTicks += IntervalTicks;
		}
	}

	// ���̈ʒu�ɃE�B���h�E�̒��ɉ摜��`�������Ȃǂ�����
	// DX���C�u���������̂��낢��ȃT���v���������Ă݂悤�I
	// https://dxlib.xsrv.jp/dfunc.html

	// �L�[���͑҂�������
	WaitKey();

	// DX���C�u�����̌�n��
	DxLib::DxLib_End();

	// �\�t�g�̏I��
	return 0;
}
#ifndef MYRANDOM_H_
#define MYRANDOM_H_

#include <random>

class MyRandom
{
public:
    // �Q�[�����ŗB��̃C���X�^���X
    static std::random_device rnd;// �񌈒�I�ȗ���������
    static std::mt19937 random; // �����Z���k�E�c�C�X�^��32�r�b�g��

    // �������i�V�[�h�w�薳���j
    static void Init()
    {   // https://cpprefjp.github.io/reference/random/random_device.html
        random.seed(rnd()); // �������V�[�h�ɂ��邱�ƂŖ��񃉃��_���ɂ���
    }

    // �������i�V�[�h���w��j
    static void Init(int seed)
    {
        random.seed(seed);
    }

    // �w�肵���͈͂̐����̗������擾����imax�͏o�Ȃ��̂Œ��Ӂj
    static int RangeInt(int min, int max)
    {
        std::uniform_int_distribution<> randRange(min, max);        // [min, max] �͈͂̈�l����
        return randRange(random);
    }

    // �w�肵���͈͂̏����̗������擾����imax�͏o�Ȃ��̂Œ��Ӂj
    static float Range(float min, float max)
    {
        std::uniform_real_distribution<> randRange(min, max);        // [min, max] �͈͂̈�l����
        return (float)randRange(random);
    }

    // �w�肵���m���i���j��true�ɂȂ�
    /*static bool Percent(float probability)
    {
        return random.NextDouble() * 100 < probability;
    }*/

    // �w�肵���͈͂ŗ�����ԋp����B
    // �Ⴆ��1.5f���w�肷��ƁA-1.5�`+1.5�͈̔͂̒l��ԋp����B
    static float PlusMinus(float value)
    {
        return Range(-value, value);
    }
};

#endif
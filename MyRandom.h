#ifndef MYRANDOM_H_
#define MYRANDOM_H_

#include <random>

class MyRandom
{
public:
    // ゲーム中で唯一のインスタンス
    static std::random_device rnd;// 非決定的な乱数生成器
    static std::mt19937 random; // メルセンヌ・ツイスタの32ビット版

    // 初期化（シード指定無し）
    static void Init()
    {   // https://cpprefjp.github.io/reference/random/random_device.html
        random.seed(rnd()); // 乱数をシードにすることで毎回ランダムにする
    }

    // 初期化（シードを指定）
    static void Init(int seed)
    {
        random.seed(seed);
    }

    // 指定した範囲の整数の乱数を取得する（maxは出ないので注意）
    static int RangeInt(int min, int max)
    {
        std::uniform_int_distribution<> randRange(min, max);        // [min, max] 範囲の一様乱数
        return randRange(random);
    }

    // 指定した範囲の小数の乱数を取得する（maxは出ないので注意）
    static float Range(float min, float max)
    {
        std::uniform_real_distribution<> randRange(min, max);        // [min, max] 範囲の一様乱数
        return (float)randRange(random);
    }

    // 指定した確率（％）でtrueになる
    /*static bool Percent(float probability)
    {
        return random.NextDouble() * 100 < probability;
    }*/

    // 指定した範囲で乱数を返却する。
    // 例えば1.5fを指定すると、-1.5～+1.5の範囲の値を返却する。
    static float PlusMinus(float value)
    {
        return Range(-value, value);
    }
};

#endif
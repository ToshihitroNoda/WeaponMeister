#ifndef SINGLETON_H_
#define SINGLETON_H_

// テンプレートT型シングルトンSingleton<～> ～になんでも指定して唯一物にできる
// ★Singleton<T>型は【必ず唯一で複製不可】(使い方:どこからでもアクセスし変数を共有するクラス向き)
// ★ゲーム内の【どこからアクセスしても統一性が保たれる】(唯一だから)「クラス名と実体が一致」
template<class T>
class Singleton
{
public:
    // GetInstanceを通して【しか】T型クラスをつくれないうえに、
    // ★作ったものは【かならず唯一で複製不可】
    // それが【シングルトン型】！
    // ゲーム中で唯一で複製不可にしたい【ゲームを一律管理するクラス】などに最適！
    // https://teratail.com/questions/17416
    // http://rudora7.blog81.fc2.com/blog-entry-393.html
    // ②↓同じ関数の定義はプログラム全体で１つだけしか許されません。(static関数名は被らない)
    static inline T& GetInstance()
    {   //①↓関数の中で定義されたstatic変数は、関数の定義毎に１つ領域が確保されます。
        static T instance; //メモリ上にstatic変数確保(静かに常に待機するinstance)
        return instance; //①=(常駐)②=(唯一) ①と②両方満たすinstanceは【メモリ上に唯一】
    }

protected:
    Singleton() {} // 外部でのインスタンス作成は禁止(protected:内部公開、外部禁止)
    virtual ~Singleton() {} // 仮想デストラクタ(シングルトンを【継承するためには忘れちゃダメ】)

private:
    void operator=(const Singleton& obj) {} // 代入演算子禁止
    Singleton(const Singleton& obj) {} // コピーコンストラクタ禁止(コピーできない【唯一】)
    static T* instance; // private:だから外部アクセスできない【GetInstance()経由しか無理】
};

// いつもcppで書いたstatic変数初期化も★【Tテンプレートクラスだからすべて.hヘッダにまとめて書いた】
template< class T >
T* Singleton< T >::instance = 0; //cppでの定義を.h内に書いた(static変数はclass内で初期化できないから)

#endif // !SINGLETON_H_

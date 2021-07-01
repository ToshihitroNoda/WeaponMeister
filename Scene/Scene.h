#ifndef SCENE_H_
#define SCENE_H_

#include <string>

// シーンの基底クラス
class Scene
{
public:
	std::string tag = ""; // シーンの種類の判別に使う

	// コンストラクタ
	Scene() = default;
	// デストラクタ
	virtual ~Scene() = default;

	// 初期化処理
	virtual void Init()   = 0;

	// 終了処理
	virtual void Final()  = 0;

	// 更新処理
	virtual void Update() = 0;

	// シーン切り替え処理
	virtual void Change() = 0;

	// 描画処理
	virtual void Draw()   = 0;

	bool isDead = false;
};

#endif
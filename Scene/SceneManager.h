#ifndef SCNENEMANAGER_H_
#define SCNENEMANAGER_H_

#include <vector>
#include <memory>
#include <string>

#include "../MyLib/Singleton.h"

class Scene; //クラス宣言だけで

class SceneManager : public Singleton<SceneManager>//←<～>として継承すると唯一のシングルトン型タイプとなる
{
public:
    friend class Singleton<SceneManager>; // Singleton でのインスタンス作成は許可

    std::string selectStage = "stage1"; // 選択中のステージ(タイトルでのデフォルト選択などもマネージャに保持できる)

    // マネージャは【どこからでもアクセスしやすい「変数の掲示板」として気軽に使ってもよい】
    int scoreMax = -1; // シーンをまたぐスコアなどはマネージャに定義すればシーンチェンジ後も消えない

    std::shared_ptr<Scene> prevScene{ nullptr }; // 一つ前のシーン
    std::shared_ptr<Scene> currentScene{ nullptr }; // 現在のシーン
    // シーンをチェンジし遷移する(前のシーンのリセット処理もする) optionsはステージcsvなどの指定に使える
    void LoadScene(std::string sceneName, std::vector<std::string> options = { "" });

protected:
    SceneManager() = default; // 外部からのインスタンス作成は禁止
    virtual ~SceneManager() = default; //外部からのインスタンス破棄も禁止
};

#endif
#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameManager.h"
#include "GameObject.h"
#include "Screen.h"

enum class State
{
    collect,
    run,
    wait
};

class Player : public GameObject
{
public:
    GameManager& gm = GameManager::GetInstance(); 

    Player() = default;
    Player(float x, float y, float z = 0)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        tag = "Player";

        // 画像ピクセル数
        imageWidth          = 64;  
        imageHeight         = 64;  
        imageLength         = 64;  
        // 当たり判定の左端のオフセット
        hitboxOffsetLeft    = 5;   
        hitboxOffsetRight   = 5;   
        hitboxOffsetTop     = 0;   
        hitboxOffsetBottom  = 0;   
        hitboxOffsetForward = 5;   
        hitboxOffsetBack    = 5;   

        if (isRotaGraph == true)
        {   // 画像の中心を起点に描く場合のずれ
            rotaGraphShiftX = (float)imageWidth / 2;
            rotaGraphShiftY = (float)imageHeight / 2;
            rotaGraphShiftZ = (float)imageLength / 2;
        }

        // ミドルの値を初期化のときに計算して固定値を得る
        collisionDetectionMiddleX_ = (GetRight() - GetLeft())   / 2; 
        collisionDetectionMiddleZ_ = (GetForward() - GetBack()) / 2;

        SetMousePoint(Screen::Width / 2, Screen::Height / 2); // マウスカーソル初期化

        camDistanceFromPlayer_ = 250; // プレイヤからカメラまでのY平面上の距離
        camHeightFromTerrain_  = -200; // 地面からカメラまでのY方向上の高さ

    };
    ~Player(){};

    void HandleInput();

    void MoveX();
    void MoveY();
    void MoveZ();

    void Init();
    void Update();
    void Draw();
    void OnCollision(std::shared_ptr<GameObject> other);

    void AnimationAttach(int AtnimIndex);
    void PlayAnimation(float ConstPlayTime, bool isLoop);

    const float backImageWidth = 8192;
    float backX = 0;
    
private:

    float MoveSpeedMax_          = 15; 
    float MoveSpeed_             = 0; 
    float MoveSpeedLateral_      = 0; 
    float camDistanceFromPlayer_ = 0;
    float camHeightFromTerrain_  = 0;
    float nowCamAngle_           = 0; 
    float PercentAngleByCursorDis_    = 0.0f; // マウスの移動距離に応じて角度変える
    float PercentAngleByCursorDis_BG_ = 0.0f;
    float collisionDetectionMiddleX_  = 0.0f;
    float collisionDetectionMiddleZ_  = 0.0f;

    int MouseX_     = 0;
    int MouseY_     = 0;
    int prevMouseX_ = 0;

    bool doLateralMove_ = false; 
    bool canAngleInit_  = false;
    bool collectAttach_ = false;
    bool runAttach_     = false;
    bool waitAttach_    = false;
    std::vector<bool> AttachCheck_{ collectAttach_, runAttach_, waitAttach_ };

    const float IncreaseSpeed_ = 0.3f;
    const float DecreaseSpeed_ = 0.9f;
    const int   MaxAngle_      = 360;
    const int   DrawStrPosX_   = 500;
    const int   DrawStrPosY_   = 500;

    int AttachIndex_     = 0;
    int prevAttachIndex_ = 0;
    int prevAnimIndex_   = 0;
    float TotalTime_     = 0.0f;
    float PlayTime_      = 0.0f;
    float modelAngle_    = 0.0f;
};

#endif
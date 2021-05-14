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

        // �摜�s�N�Z����
        imageWidth          = 64;  
        imageHeight         = 64;  
        imageLength         = 64;  
        // �����蔻��̍��[�̃I�t�Z�b�g
        hitboxOffsetLeft    = 5;   
        hitboxOffsetRight   = 5;   
        hitboxOffsetTop     = 0;   
        hitboxOffsetBottom  = 0;   
        hitboxOffsetForward = 5;   
        hitboxOffsetBack    = 5;   

        if (isRotaGraph == true)
        {   // �摜�̒��S���N�_�ɕ`���ꍇ�̂���
            rotaGraphShiftX = (float)imageWidth / 2;
            rotaGraphShiftY = (float)imageHeight / 2;
            rotaGraphShiftZ = (float)imageLength / 2;
        }

        // �~�h���̒l���������̂Ƃ��Ɍv�Z���ČŒ�l�𓾂�
        collisionDetectionMiddleX_ = (GetRight() - GetLeft())   / 2; 
        collisionDetectionMiddleZ_ = (GetForward() - GetBack()) / 2;

        SetMousePoint(Screen::Width / 2, Screen::Height / 2); // �}�E�X�J�[�\��������

        camDistanceFromPlayer_ = 250; // �v���C������J�����܂ł�Y���ʏ�̋���
        camHeightFromTerrain_  = -200; // �n�ʂ���J�����܂ł�Y������̍���

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
    float PercentAngleByCursorDis_    = 0.0f; // �}�E�X�̈ړ������ɉ����Ċp�x�ς���
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
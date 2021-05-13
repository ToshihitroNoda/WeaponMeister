#ifndef CAMERA_H_
#define CAMERA_H_

#include <DxLib.h>
#include "MyMath.h"
#include "Screen.h"

class Camera
{
public:
    // カメラの位置。
    // 画面左上のワールド座標を表す。
    static float x;
    static float y;
    static float z;

    static float anglePlaneChara;       // 板ポリゴンのキャラは常にカメラ方向に面を見せるようにするための角度
    static float anglePlaneCharaRotate; //この角度を0～2πに変えるとクルっとオセロのように回転させる

    static VECTOR cameraPos;

    static float cameraLookAtHeight;

    // コンストラクタ
    Camera(float x, float y, float z)
    {
        this->x   = x;
        this->y   = y;
        this->z   = z;
        cameraPos = VGet(x, y, z); // カメラの位置の保存(読み出し専用)
    }

    ~Camera()
    {

    }


    // カメラの位置をセットし画面左上のワールド2D座標系として保存
    static void SetPosition(float worldX, float worldY, float worldZ)
    {   // 画面左上のワールド座標系として保存
        x = worldX;
        y = worldY;
        z = worldZ;
        cameraPos = VGet(x, y, z); // カメラの位置の保存(cameraPosは読み出し専用)
    }

    // 指定されたワールド座標が画面の中心に来るように、カメラの位置を変更する
    static void LookAt(float targetX, float targetY, float targetZ)
    {
        // カメラの位置と向きを設定
        {
            // 注視点はターゲットの座標から CAMERA_LOOK_AT_HEIGHT 分だけ高い位置
            VECTOR TargetPosition       = VGet(targetX, targetY + cameraLookAtHeight, targetZ);
            // カメラの位置の設定
            VECTOR CameraPosition       = VGet(x, y, z);    
            // カメラがターゲットのほうを向くようにする
            VECTOR CameraLookAtPosition = TargetPosition;

            // カメラの設定に反映する
            SetCameraPositionAndTarget_UpVecY(CameraPosition, CameraLookAtPosition);
            // カメラ回転後の角度を保存して板ポリゴンキャラクタが常にカメラに面を見せるようにする
            anglePlaneChara = GetCameraAngleHRotate();
            // カメラ位置の保存(cameraPosは読み出し専用)
            cameraPos       = CameraPosition; 
        }
    }

    static int SetCameraPositionAndTarget_UpVecY(VECTOR Position, VECTOR Target)
    {
        // 右手・左手系とY軸矢印の方向に従い座標を変換
        VECTOR Position_COVERT_XYZ = VGet(Position.x, Position.y, Position.z);
        VECTOR Target_COVERT_XYZ = VGet(Target.x, Target.y, Target.z);
        return DxLib::SetCameraPositionAndTarget_UpVecY(Position_COVERT_XYZ, Target_COVERT_XYZ);
    }

    /// <summary>
    /// 四角形（枠線のみ）を描画する
    /// </summary>
    /// <param name="left">左端</param>
    /// <param name="top">上端</param>
    /// <param name="right">右端</param>
    /// <param name="bottom">下端</param>
    /// <param name="color">色</param>
    static void DrawLineBox(float left, float top, float right, float bottom, unsigned int color, float leftTopZ = 0, float rightBottomZ = 0)
    {
        if (leftTopZ == 0 && rightBottomZ == 0)
        {   // 2D版
            DrawBox(
                (int)(left   - x + 0.5f),
                (int)(top    - y + 0.5f),
                (int)(right  - x + 0.5f),
                (int)(bottom - y + 0.5f),
                color,
                FALSE);
        }
        else
        {   // 3D版
            DrawCube3D
               (VGet(left , top   , leftTopZ    ),
                VGet(right, bottom, rightBottomZ),
                color, color, FALSE);
        }
    }
};

#endif
#include "Camera.h"
#include "MyLib/MyMath.h"

// カメラを動かす
void Camera::Move()
{
	GetMousePoint(&mouseX_, &mouseY_);              // マウスカーソル座標取得

	// マウスがウィンドウ内にあったらカメラ移動
	if (mouseX_ > 0 && mouseX_ < Screen::width &&
		mouseY_ > 0 && mouseY_ < Screen::height)
	{
		if (mouseX_ > Screen::width / 2)                  //　マウスが右に動いていたら
		{

			// マウスの移動距離を度数変換、360 : x = Screen::Width * 1.2f : MouseX - Screen::width / 2
			//                             x(Screen::Width * 1.2f) = 360(MouseX - Screen::width / 2)
			//                             x = (360(MouseX - Screen::width / 2)) / (Screen::Width * 1.2f)

			percentAngleByCursorDis_ = (float)((MaxAngle_ * (mouseX_ - Screen::width / 2)) / (Screen::width * 1.2f));
			percentAngleByCursorDis_BG_ = (float)((MaxAngle_ * (mouseX_ - Screen::width / 2)) / (BackImageWidth / 60));

			// PercentAngleByCursor初期化
			if (!canAngleInit_)
			{
				percentAngleByCursorDis_ = 0;
				percentAngleByCursorDis_BG_ = 0;
				canAngleInit_ = true;
			}

			nowCamAngle_ += percentAngleByCursorDis_;   // 度数分足す

			backX += percentAngleByCursorDis_BG_;
			if (backX <= -BackImageWidth + Screen::width)
				backX = 0;
		}
		else                                        // マウスが左に動いていたら
		{
			percentAngleByCursorDis_ = (float)((MaxAngle_ * (Screen::width / 2 - mouseX_)) / (Screen::width * 1.2f));
			percentAngleByCursorDis_BG_ = (float)((MaxAngle_ * (mouseX_ - Screen::width / 2)) / (BackImageWidth / 60));

			// PercentAngleByCursor初期化
			if (!canAngleInit_)
			{
				percentAngleByCursorDis_ = 0;
				percentAngleByCursorDis_BG_ = 0;
				canAngleInit_ = true;
			}

			nowCamAngle_ -= percentAngleByCursorDis_;

			backX += percentAngleByCursorDis_BG_;
			if (backX > BackImageWidth)
				backX = 0;
		}
	}

	// カメラが360度で1周するように
	if (nowCamAngle_ <= 0.0f)             nowCamAngle_ = (float)MaxAngle_ - 1.0f;
	if (nowCamAngle_ >= (float)MaxAngle_) nowCamAngle_ = 1.0f;
}

// カメラの位置をセットし画面左上のワールド2D座標系として保存
void Camera::SetPosition(Vector3 v3)
{   // 画面左上のワールド座標系として保存
	position = v3;
	cameraPos = position.Vec3ToVec(position); // カメラの位置の保存(cameraPosは読み出し専用)
}

// 指定されたワールド座標が画面の中心に来るように、カメラの位置を変更する
void Camera::LookAt(Vector3 v3)
{
	// カメラの位置と向きを設定
	{
		// 注視点はターゲットの座標から CAMERA_LOOK_AT_HEIGHT 分だけ高い位置
		VECTOR TargetPosition = VGet(v3.x, v3.y + cameraLookAtHeight, v3.z);
		// カメラの位置の設定
		VECTOR CameraPosition = position.Vec3ToVec(position);
		// カメラがターゲットのほうを向くようにする
		VECTOR CameraLookAtPosition = TargetPosition;

		// カメラの設定に反映する
		SetCameraPositionAndTarget_UpVecY(CameraPosition, CameraLookAtPosition);
		// カメラ位置の保存(cameraPosは読み出し専用)
		cameraPos = CameraPosition;
	}
}

int Camera::SetCameraPositionAndTarget_UpVecY(VECTOR Position, VECTOR Target)
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
void Camera::DrawLineBox(float left, float top, float right, float bottom, unsigned int color, float leftTopZ, float rightBottomZ)
{
	if (leftTopZ == 0 && rightBottomZ == 0)
	{   // 2D版
		DrawBox(
			(int)(left - position.x + 0.5f),
			(int)(top - position.y + 0.5f),
			(int)(right - position.x + 0.5f),
			(int)(bottom - position.y + 0.5f),
			color,
			FALSE);
	}
	else
	{   // 3D版
		DrawCube3D
		(VGet(left, top, leftTopZ),
			VGet(right, bottom, rightBottomZ),
			color, color, FALSE);
	}
}
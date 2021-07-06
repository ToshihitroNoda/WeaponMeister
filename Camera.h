#ifndef CAMERA_H_
#define CAMERA_H_

#include <DxLib.h>
#include "Screen.h"
#include "Vector3.h"

class Camera
{
public:
	// カメラの位置。
	// 画面左上のワールド座標を表す。
	Vector3 position{ 0.0f, 0.0f, 0.0f };

	float cameraLookAtHeight = 0.0f;

	VECTOR cameraPos = DxLib::VGet(Screen::width / 2, Screen::height / 2, -100.0f);

	Camera() = default;

	~Camera() = default;

	// カメラを動かす
	void Move();

	// カメラの位置をセットし画面左上のワールド2D座標系として保存
	void SetPosition(Vector3 v3);

	// 指定されたワールド座標が画面の中心に来るように、カメラの位置を変更する
	void LookAt(Vector3 v3);

	int SetCameraPositionAndTarget_UpVecY(VECTOR Position, VECTOR Target);

	/// <summary>
	/// 四角形（枠線のみ）を描画する
	/// </summary>
	/// <param name="left">左端</param>
	/// <param name="top">上端</param>
	/// <param name="right">右端</param>
	/// <param name="bottom">下端</param>
	/// <param name="color">色</param>
	void DrawLineBox(float left, float top, float right, float bottom, unsigned int color, float leftTopZ = 0, float rightBottomZ = 0);

	int backX = 0;
	float nowCamAngle_ = 0.0f;

private:
	int mouseX_ = 0;
	int mouseY_ = 0;

	float percentAngleByCursorDis_    = 0.0f; // マウスの移動距離に応じて角度変える
	float percentAngleByCursorDis_BG_ = 0.0f;

	bool canAngleInit_ = false;

	const int MaxAngle_      = 360;
	const int BackImageWidth = 8192;
};

#endif
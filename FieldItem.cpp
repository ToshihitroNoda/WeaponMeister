#include "FieldItem.h"
#include "Camera.h"
#include "Input.h"
#include "Image.h"

void FieldItem::Init()
{

}

void FieldItem::Update()
{
	isOnCollisionPlayer_ = false;
}

void FieldItem::Draw()
{
	MV1SetPosition(Image::fieldItem, VGet(x, y, z));
	MV1SetScale(Image::fieldItem, VGet(0.2f, 0.2f, 0.2f));
	MV1DrawModel(Image::fieldItem);
	DrawHitBox();
}


void FieldItem::OnCollision(std::shared_ptr<GameObject> other)
{
	if (other->tag == "Player")
	{
		isOnCollisionPlayer_ = true;
	}
}
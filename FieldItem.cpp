#include "FieldItem.h"
#include "Camera.h"
#include "Input.h"

void FieldItem::Init()
{

}

void FieldItem::Update()
{
	isOnCollisionPlayer = false;
}

void FieldItem::Draw()
{
	MV1SetPosition(gm.image.fieldItem, VGet(x, y, z));
	MV1SetScale(gm.image.fieldItem, VGet(0.2f, 0.2f, 0.2f));
	MV1DrawModel(gm.image.fieldItem);
	//DrawHitBox();
}


void FieldItem::OnCollision(std::shared_ptr<GameObject> other)
{
	if (other->tag == "Player")
	{
		isOnCollisionPlayer = true;
	}
}
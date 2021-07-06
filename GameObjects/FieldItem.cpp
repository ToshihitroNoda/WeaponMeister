#include "FieldItem.h"
#include "../Camera.h"
#include "../MyLib/Input.h"

void FieldItem::Init()
{

}

void FieldItem::Update()
{
	isOnCollisionPlayer = false;
}

void FieldItem::Draw()
{
	MV1SetPosition(gm.image.fieldItem, position.Vec3ToVec(position));
	MV1SetScale(gm.image.fieldItem, VGet(0.2f, 0.2f, 0.2f));
	MV1DrawModel(gm.image.fieldItem);
	//DrawHitBox();
}


void FieldItem::OnCollision(std::shared_ptr<GameObject> other)
{
	if (other->tag == "Player")
	{
		isOnCollisionPlayer = true; 
		if (Input::GetButtonDown(PAD_INPUT_1) && gm.pouch.size() < gm.MaxPouchSize)
		{
			isDead = true;
		}
	}
}
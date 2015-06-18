#include "GizmoSoldier.h"

#define DEBUG_SOLDIER_TEXTURE "CloseNormal.png"

GizmoSoldier* GizmoSoldier::create()
{
	GizmoSoldier *sprite = new (std::nothrow) GizmoSoldier();
	if (sprite && sprite->initWithFile(DEBUG_SOLDIER_TEXTURE))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

GizmoSoldier::GizmoSoldier():Soldier(Soldier::Human)
{

}

GizmoSoldier::~GizmoSoldier()
{

}

void GizmoSoldier::Update()
{
	Soldier::Update();
	//
	auto const_pos = GetPosition();
	setPosition(const_pos.x,const_pos.y);
}

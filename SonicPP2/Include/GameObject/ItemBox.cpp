#include "ItemBox.h"
#include "Spring.h"
#include "../GameManager.h"
#include "../Scene/Camera.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"

CItemBox::CItemBox()
{
	SetTypeID<CItemBox>();
}

CItemBox::CItemBox(const CItemBox& Obj) :
	CGameObject(Obj)
{
}

CItemBox::~CItemBox()
{
}


bool CItemBox::Init()
{
	m_Pivot = { 0.5f, 1.f };

	CreateAnimation();

	AddAnimation("SpringYellowIdle", false);
	AddAnimation("SpringYellowBounce", false, 0.5f);

	//SetEndFunction<CItemBox>("SpringYellowBounce", this, &CItemBox::SetIdle);

	SetSize(32.f, 16.f);

	CColliderBox* Box = AddCollider<CColliderBox>("MapObject");

	Box->SetExtent(32.f, 16.f);
	Box->SetOffset(0.f, -8.f);
	Box->SetCollisionProfile("MapObject");

	Box->SetCollisionBeginFunction<CItemBox>(this, &CItemBox::CollisionBegin);
	Box->SetCollisionEndFunction<CItemBox>(this, &CItemBox::CollisionEnd);

	ChangeAnimation("SpringYellowIdle");

	return true;
}

void CItemBox::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CItemBox::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CItemBox::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CItemBox::InflictSpeed(float Speed, Vector2 Dir)
{
	CGameObject::InflictSpeed(Speed, Dir);
}

void CItemBox::CollisionBegin(CCollider* Src, CCollider* Dest)
{

}

void CItemBox::CollisionEnd(CCollider* Src, CCollider* Dest)
{

}
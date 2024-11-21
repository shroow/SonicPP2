#include "Ring.h"
#include "Spring.h"
#include "../GameManager.h"
#include "../Scene/Camera.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"

CRing::CRing()
{
	SetTypeID<CRing>();
}

CRing::CRing(const CRing& Obj) :
	CGameObject(Obj)
{
}

CRing::~CRing()
{
}


bool CRing::Init()
{

	CreateAnimation();

	AddAnimation("RingIdle", true, 0.5f);
	AddAnimation("RingEffect", false, 0.5f);

	SetEndFunction<CRing>("RingEffect", this, &CRing::AnimationEnd);

	SetSize(32.f, 32.f);
	SetPivot(0.5f, 0.5f);

	CColliderBox* Box = AddCollider<CColliderBox>("Ring");

	Box->SetExtent(32.f, 32.f);
	
	Box->SetCollisionProfile("MapObject");

	Box->SetCollisionBeginFunction<CRing>(this, &CRing::CollisionBegin);
	Box->SetCollisionEndFunction<CRing>(this, &CRing::CollisionEnd);

	return true;
}

void CRing::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CRing::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

}

void CRing::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CRing::InflictSpeed(float Speed, Vector2 Dir)
{
	CGameObject::InflictSpeed(Speed, Dir);
}

void CRing::AnimationEnd()
{
	SetActive(false);
}


void CRing::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	std::string Name = Dest->GetName();

	if (Name == "Player")
		ChangeAnimation("RingEffect");
}

void CRing::CollisionEnd(CCollider* Src, CCollider* Dest)
{

}


#include "Spring.h"
#include "../GameManager.h"
#include "../Scene/Camera.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"

CSpring::CSpring()	:
	m_Bounce(false)
{
	SetTypeID<CSpring>();
}

CSpring::CSpring(const CSpring& Obj) :
	CGameObject(Obj)
{
}

CSpring::~CSpring()
{
}


bool CSpring::Init()
{
	m_Pivot = { 0.5f, 1.f };

	CreateAnimation();

	AddAnimation("SpringYellowIdle", false);
	AddAnimation("SpringYellowBounce", false, 0.5f);

	SetEndFunction<CSpring>("SpringYellowBounce", this, &CSpring::SetIdle);
	
	SetSize(32.f, 16.f);

	CColliderBox* Box = AddCollider<CColliderBox>("SpringUp");

	Box->SetExtent(32.f, 16.f);
	Box->SetOffset(0.f, -8.f);
	Box->SetCollisionProfile("MapObject");

	Box->SetCollisionBeginFunction<CSpring>(this, &CSpring::CollisionBegin);
	Box->SetCollisionEndFunction<CSpring>(this, &CSpring::CollisionEnd);

	ChangeAnimation("SpringYellowIdle");

	return true;
}

void CSpring::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CSpring::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	if(!m_Bounce)
		ChangeAnimation("SpringYellowIdle");
}

void CSpring::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CSpring::InflictSpeed(float Speed, Vector2 Dir)
{
	CGameObject::InflictSpeed(Speed, Dir);
}

void CSpring::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	//FIX
	//반사벡터를 이용해서 대각선으로 장애물에 부딪혔을 경우의 정확한 위치를 구하기
	m_Bounce = true;
	ChangeAnimation("SpringYellowBounce");
}

void CSpring::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	m_Bounce = false;
}

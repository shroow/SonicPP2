
#include "Thorn.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"
#include "Effect.h"

CThorn::CThorn() :
	m_Angle(0.f)
{
	SetTypeID<CThorn>();
}

CThorn::CThorn(const CThorn& Obj) :
	CGameObject(Obj),
	m_Angle(Obj.m_Angle),
	m_Distance(Obj.m_Distance)
{
}

CThorn::~CThorn()
{
}

bool CThorn::Init()
{
	m_MoveSpeed = 700.f;
	m_Distance = 600.f;

	SetSize(16.f, 16.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("TulipponThorn");
	SetColorKey(13, 72, 7);

	CColliderBox* Box = AddCollider<CColliderBox>("Thorn");

	Box->SetExtent(16.f, 16.f);

	Box->SetCollisionBeginFunction<CThorn>(this, &CThorn::CollisionBegin);
	Box->SetCollisionEndFunction<CThorn>(this, &CThorn::CollisionEnd);

	//CColliderCircle* Circle = AddCollider<CColliderCircle>("Body");

	//Circle->SetRadius(25.f);
	////Circle->SetCollisionProfile("Monster");

	//Circle->SetCollisionBeginFunction<CThorn>(this, &CThorn::CollisionBegin);
	//Circle->SetCollisionEndFunction<CThorn>(this, &CThorn::CollisionEnd);

	SetPhysicsSimulate(true);

	return true;
}

void CThorn::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	Move(m_Angle);

	m_Distance -= m_MoveSpeed * DeltaTime;

	if (m_Distance <= 0.f)
		SetActive(false);
}

void CThorn::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CThorn::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);

	Vector2	RenderLT;

	RenderLT = m_Pos - m_Pivot * m_Size - m_Scene->GetCamera()->GetPos();

	Ellipse(hDC, (int)RenderLT.x, (int)RenderLT.y,
		(int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));
}

void CThorn::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	SetActive(false);
	
	Dest->GetOwner()->InflictDamage(true);

	// Damage Ã³¸®
	//Dest->GetOwner()->InflictDamage(m_Damage);
}

void CThorn::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}

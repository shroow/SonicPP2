#include "Rock.h"
#include "../Collision/ColliderBox.h"

CRock::CRock()	:
	m_RockType(EObject_Type::Small),
	m_Breakable(false)
{
}

CRock::CRock(const CRock& Obj) :
	CMapObject(Obj),
	m_RockType(EObject_Type::Small),
	m_Breakable(false)
{
}

CRock::~CRock()
{
}

void CRock::SetRockType(EObject_Type Type, bool Breakable)
{
	m_RockType = Type;
	m_Breakable = Breakable;

	switch (m_RockType)
	{
	case EObject_Type::Small:
		SetTexture("Rock_Small");
		m_ColliBox->SetExtent(48.f, 32.f);
		break;
	case EObject_Type::Medium:
		SetTexture("Rock_Medium");
		m_ColliBox->SetExtent(48.f, 48.f);
		break;
	case EObject_Type::Big:
		SetTexture("Rock_Big");
		m_ColliBox->SetExtent(48.f, 80.f);
		break;
	}

	if (m_Breakable)
	{

	}
}

bool CRock::Init()
{

	m_ColliBox = AddCollider<CColliderBox>("Rock");

	m_ColliBox->SetExtent(48.f, 32.f);
	m_ColliBox->SetCollisionProfile("MapObject");

	m_ColliBox->SetCollisionBeginFunction<CRock>(this, &CRock::CollisionBegin);
	m_ColliBox->SetCollisionEndFunction<CRock>(this, &CRock::CollisionEnd);

	return true;
}

void CRock::Update(float DeltaTime)
{
	CMapObject::Update(DeltaTime);
}

void CRock::PostUpdate(float DeltaTime)
{
	CMapObject::PostUpdate(DeltaTime);
}

void CRock::Render(HDC hDC, float DeltaTime)
{
	CMapObject::Render(hDC, DeltaTime);
}

bool CRock::InflictDamage(bool Damage)
{
	if (Damage)
	{
		SetActive(false);
	}

	return true;
}

Vector2 CRock::InflictSpeed(Vector2 Speed)
{
	return Vector2();
}

void CRock::CollisionBegin(CCollider* Src, CCollider* Dest)
{

	if (Dest->GetProfile()->Channel == ECollision_Channel::PlayerAttack)
	{
		if (!m_Breakable)
			InflictDamage(true);
	}
}

void CRock::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}

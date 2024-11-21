#include "Nill.h"
#include "../Collision/ColliderBox.h"

CNill::CNill() :
	m_NillDir(EObject_Dir::Up)
{
}

CNill::CNill(const CNill& Obj) :
	CMapObject(Obj),
	m_NillDir(Obj.m_NillDir)
{
}

CNill::~CNill()
{
}

void CNill::SetNillDir(EObject_Dir Type)
{
	m_NillDir = Type;

	switch (m_NillDir)
	{
	case EObject_Dir::Left:
		SetTexture("Rock_Small");
		m_ColliBox->SetExtent(48.f, 32.f);
		break;
	case EObject_Dir::Right:
		m_ColliBox->SetExtent(48.f, 48.f);
		break;
	case EObject_Dir::Up:
		SetTexture("Rock_Big");
		m_ColliBox->SetExtent(48.f, 80.f);	
	case EObject_Dir::Down:
		SetTexture("Rock_Big");
		m_ColliBox->SetExtent(48.f, 80.f);
		break;
	}
}

bool CNill::Init()
{
	m_ColliBox = AddCollider<CColliderBox>("Rock");

	m_ColliBox->SetExtent(48.f, 32.f);
	m_ColliBox->SetCollisionProfile("MapObject");

	m_ColliBox->SetCollisionBeginFunction<CNill>(this, &CNill::CollisionBegin);
	m_ColliBox->SetCollisionEndFunction<CNill>(this, &CNill::CollisionEnd);

	return true;
}

void CNill::Update(float DeltaTime)
{
	CMapObject::Update(DeltaTime);
}

void CNill::PostUpdate(float DeltaTime)
{
	CMapObject::PostUpdate(DeltaTime);
}

void CNill::Render(HDC hDC, float DeltaTime)
{
	CMapObject::Render(hDC, DeltaTime);
}

bool CNill::InflictDamage(bool Damage)
{
	if (Damage)
	{
		SetActive(false);
	}

	return true;
}

Vector2 CNill::InflictSpeed(Vector2 Speed)
{
	return Vector2();
}

void CNill::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	switch (Dest->GetColliderType())
	{
	case ECollider_Type::Box:
		if (Dest->GetProfile()->Channel == ECollision_Channel::Player || Dest->GetProfile()->Channel == ECollision_Channel::Player)
		{
			InflictDamage(true);
		}
		break;
	case ECollider_Type::Line:
		break;
	}

}

void CNill::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}

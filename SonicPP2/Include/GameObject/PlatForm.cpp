#include "PlatForm.h"
#include "../Collision/ColliderBox.h"
#include "../GameManager.h"

CPlatForm::CPlatForm() :
	m_CheckMove(false)
{
}

CPlatForm::CPlatForm(const CPlatForm& Obj) :
	CMapObject(Obj),
	m_CheckMove(Obj.m_CheckMove)
{
}

CPlatForm::~CPlatForm()
{
}

bool CPlatForm::Init()
{
	m_MoveSpeed = 100.f;
	m_MoveCount = 3.f;
	m_MoveDir = -1.f;

	SetTexture("PlatForm", TEXT("Stage1/MapObject/Platform/PlatForm.bmp"));

	SetColorKey(255, 0, 255);

	SetSize(64.f, 40.f);
	SetPivot(0.5f, 0.5f);

	CColliderBox* Box = AddCollider<CColliderBox>("PlatForm");

	Box->SetExtent(64.f, 40.f);
	Box->SetCollisionProfile("TileMap");

	Box->SetCollisionBeginFunction<CPlatForm>(this, &CPlatForm::CollisionBegin);
	Box->SetCollisionEndFunction<CPlatForm>(this, &CPlatForm::CollisionEnd);

	return true;
}

void CPlatForm::Update(float DeltaTime)
{
	CMapObject::Update(DeltaTime);

	if (!m_CheckMove)
		return;

	if (m_MoveCount <= 0.f)
	{
		m_MoveCount += DELTA_TIME;
		MoveDir(Vector2(0.f, m_MoveDir));
	}
	else if (m_MoveCount == 3.f)
	{
		if (m_MoveCount > 3.f)
			m_MoveCount = 3.f;
		if (m_MoveDir == -1.f)
			m_MoveDir = 1.f;
		else if (m_MoveDir == 1.f)
			m_MoveDir = -1.f;
	}
	else if (m_MoveCount >= 3.f)
	{
		m_MoveCount -= DELTA_TIME;
	}

}

void CPlatForm::PostUpdate(float DeltaTime)
{
	CMapObject::PostUpdate(DeltaTime);
}

void CPlatForm::Render(HDC hDC, float DeltaTime)
{
	CMapObject::Render(hDC, DeltaTime);
}

bool CPlatForm::InflictDamage(bool Damage)
{
	return true;
}

Vector2 CPlatForm::InflictSpeed(Vector2 Speed)
{
	return Vector2();
}

void CPlatForm::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	switch (Dest->GetColliderType())
	{
	case ECollider_Type::Box:
		if (Dest->GetProfile()->Channel == ECollision_Channel::Player || Dest->GetProfile()->Channel == ECollision_Channel::Player)
		{
			return;
		}
		break;
	case ECollider_Type::Line:
		break;
	}

}

void CPlatForm::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}

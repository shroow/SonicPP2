#include "Tulippon.h"
#include "../GameManager.h"
#include "../Scene/Camera.h"
#include "../Scene/Scene.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderLine.h"
#include "../Collision/ColliderCircle.h"
#include "BombS.h"

CTulippon::CTulippon()	:
	m_FireCount(4.f),
	m_HP(1)
{
	SetTypeID<CTulippon>();
}

CTulippon::CTulippon(const CTulippon& Obj) :
	CMonster(Obj)
{
}

CTulippon::~CTulippon()
{
}

bool CTulippon::Init()
{
	m_Pivot = { 0.5f, 1.f };

	CreateAnimation();

	AddAnimation("TulipponIdle", false);
	AddAnimation("TulipponFireThorn", true, 0.6f);

	CColliderBox* Box = AddCollider<CColliderBox>("Monster");

	Box->SetExtent(48.f, 50.f);
	Box->SetOffset(0.f, -25.f);
	Box->SetCollisionProfile("Monster");

	Box->SetCollisionBeginFunction<CTulippon>(this, &CTulippon::CollisionBegin);
	Box->SetCollisionEndFunction<CTulippon>(this, &CTulippon::CollisionEnd);

	SetPhysicsSimulate(true);


	return true;
}

void CTulippon::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_FireCount -= DELTA_TIME;

}

void CTulippon::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
	
	if (m_FireCount <= 0.f)
	{
		m_FireCount = 5.f;
	}
	else if (m_FireCount <= 1.2f)  
	{
		ChangeAnimation("TulipponFireThorn");
	}
	else if (m_FireCount <= 5.f)
	{
		ChangeAnimation("TulipponIdle");
	}
}

void CTulippon::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

bool CTulippon::InflictDamage(bool Damage)
{
	Damage = CMonster::InflictDamage(Damage);

	if (Damage)
	{
		--m_HP;

		if (m_HP <= 0)
		{
			CBombS* Bomb = m_Scene->CreateObject<CBombS>("BombS");
			Bomb->SetPos(m_Pos.x - m_Pivot.x * m_Size.x, m_Pos.y - m_Size.y * 0.6f);
			SetActive(false);
		}
	}

	return Damage;
}

void CTulippon::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	if (Dest->GetProfile()->Channel == ECollision_Channel::Player)
	{
		InflictDamage(true);
	}
}

void CTulippon::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}

void CTulippon::CollisionOn(CCollider* Src, CCollider* Dest)
{
	//FIX
	//반사벡터를 이용해서 대각선으로 장애물에 부딪혔을 경우의 정확한 위치를 구하기
	switch (Dest->GetColliderType())
	{
	case ECollider_Type::Box:
		return;
	case ECollider_Type::Line:
		if (CCollisionManager::GetInst()->CollisionBoxToLine(Src->GetHitPoint(),
			(CColliderBox*)Src, (CColliderLine*)Dest))
		{

			if (!m_Ground)
			{
				m_FallTime = 0.f;
				m_Ground = true;
				m_Jump = false;
			}

			return;
		}
		return;
	case ECollider_Type::Circle:
		if (CCollisionManager::GetInst()->CollisionBoxToCircle(Src->GetHitPoint(),
			(CColliderBox*)Src, (CColliderCircle*)Dest))
		{
			return;
		}
		return;
	}
}
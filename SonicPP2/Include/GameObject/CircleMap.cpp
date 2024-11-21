#include "CircleMap.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderLine.h"
#include "../Collision/ColliderCircle.h"
#include "../Scene/Scene.h"
#include "Sonic.h"

CCircleMap::CCircleMap() :
	m_CenterCollide(false),
	m_RightCollide(false),
	m_LeftCollide(false)
{
}

CCircleMap::CCircleMap(const CCircleMap& Obj)
{
}

CCircleMap::~CCircleMap()
{
}

void CCircleMap::SetLine()
{
	m_LineLeft->SetCollisionChannel(ECollision_Channel::MapObject);
	m_LineLeft->SetLineInfo((m_Pos.x - 88.f), (m_Pos.y + 60.f),
		(m_Pos.x - 72.f), (m_Pos.y + 75.f));
	m_LineLeft->SetEnable(false);

	m_LineRight->SetCollisionChannel(ECollision_Channel::MapObject);
	m_LineRight->SetLineInfo((m_Pos.x + 72.f), (m_Pos.y + 75.f),
		(m_Pos.x + 88.f), (m_Pos.y + 60.f));
	m_LineRight->SetEnable(false);
}

bool CCircleMap::Init()
{
	SetSize(128.f, 112.f);
	SetPivot(0.f, 0.f);

	SetTexture("CircleRightDown",
		TEXT("Stage1/MapObject/CircleMap/RightDown.bmp"));
	SetColorKey(255, 0, 255);

	m_RightIncom = AddCollider<CColliderBox>("CircleMap");
	m_LeftIncom = AddCollider<CColliderBox>("CircleMap");
	m_CenterIncom = AddCollider<CColliderBox>("CircleMap");

	m_RightIncom->SetCollisionProfile("MapObject");
	m_LeftIncom->SetCollisionProfile("MapObject");
	m_CenterIncom->SetCollisionProfile("MapObject");

	m_RightIncom->SetCollisionBeginFunction<CCircleMap>(this, &CCircleMap::RightIncomCollisionBegin);
	m_RightIncom->SetCollisionEndFunction<CCircleMap>(this, &CCircleMap::RightIncomCollisionEnd);

	m_LeftIncom->SetCollisionBeginFunction<CCircleMap>(this, &CCircleMap::LeftIncomCollisionBegin);
	m_LeftIncom->SetCollisionEndFunction<CCircleMap>(this, &CCircleMap::LeftIncomCollisionEnd);

	m_CenterIncom->SetCollisionBeginFunction<CCircleMap>(this, &CCircleMap::CenterIncomCollisionBegin);
	m_CenterIncom->SetCollisionEndFunction<CCircleMap>(this, &CCircleMap::CenterIncomCollisionEnd);

	m_RightIncom->SetExtent(32.f, 256.f);
	m_RightIncom->SetOffset(112.f, 0.f);

	m_LeftIncom->SetExtent(32.f, 256.f);
	m_LeftIncom->SetOffset(-112.f, 0.f);

	m_CenterIncom->SetExtent(32.f, 32.f);
	m_CenterIncom->SetOffset(0.f, 80.f);

	//92, 36  82, 56
	m_LineRight = AddCollider<CColliderLine>("CircleMap");
	m_LineLeft = AddCollider<CColliderLine>("CircleMap");

	m_LineRight->SetCollisionProfile("Default");
	m_LineLeft->SetCollisionProfile("Default");

	m_LineRight->SetCollisionBeginFunction<CCircleMap>(this, &CCircleMap::LineCollisionBegin);
	m_LineRight->SetCollisionEndFunction<CCircleMap>(this, &CCircleMap::LineCollisionBegin);

	m_LineLeft->SetCollisionBeginFunction<CCircleMap>(this, &CCircleMap::LineCollisionBegin);
	m_LineLeft->SetCollisionEndFunction<CCircleMap>(this, &CCircleMap::LineCollisionBegin);


	//circle size 96 88
	//RightDown size 128 112


	return true;
}

void CCircleMap::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CCircleMap::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CCircleMap::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CCircleMap::RightIncomCollisionBegin(CCollider* Src, CCollider* Dest)

{
	if (Dest->GetProfile()->Channel == ECollision_Channel::Player)
	{
		m_RightCollide = true;
		m_LeftCollide = false;


		if (m_CenterCollide)
		{
			m_CenterCollide = false;
			m_LineLeft->SetEnable(false);
		}
	}
}

void CCircleMap::RightIncomCollisionEnd(CCollider* Src, CCollider* Dest)
{
}

void CCircleMap::LeftIncomCollisionBegin(CCollider* Src, CCollider* Dest)
{
	if (Dest->GetProfile()->Channel == ECollision_Channel::Player)
	{
		m_RightCollide = false;
		m_LeftCollide = true;

		if (m_CenterCollide)
		{
			m_CenterCollide = false;
			m_LineRight->SetEnable(false);
		}
	}
}

void CCircleMap::LeftIncomCollisionEnd(CCollider* Src, CCollider* Dest)
{
}

void CCircleMap::CenterIncomCollisionBegin(CCollider* Src, CCollider* Dest)
{
	if (m_CenterCollide)
		return;

	if (Dest->GetProfile()->Channel == ECollision_Channel::Player)
	{
		if (m_LeftCollide && !m_RightCollide)
		{
			CGameObject* Player = m_Scene->GetPlayer();
			Player->SetMoveRound(true, m_Pos);
			Player->SetMoveRoundAngle(m_Pos.Angle(Player->GetPos()), 1.f);
			Player->SetMoveSpeed(10.f);
			m_CenterCollide = true;

			m_LineLeft->SetEnable(true);
		}
		else if (m_RightCollide && !m_LeftCollide)
		{
			CGameObject* Player = m_Scene->GetPlayer();
			Player->SetMoveRound(true, m_Pos);
			Player->SetMoveRoundAngle(m_Pos.Angle(Player->GetPos()), -1.f);
			Player->SetMoveSpeed(10.f);
			m_CenterCollide = true;

			m_LineRight->SetEnable(true);
		}
		else
			return;
	}
}

void CCircleMap::CenterIncomCollisionEnd(CCollider* Src, CCollider* Dest)
{
}

void CCircleMap::LineCollisionBegin(CCollider* Src, CCollider* Dest)
{
	//if (Dest->GetProfile()->Channel == ECollision_Channel::Default)
	//	return;

	if (Dest->GetProfile()->Channel == ECollision_Channel::Player)
	{
		CGameObject* Player = m_Scene->GetPlayer();
		Player->SetMoveRound(false, m_Pos);
		Player->SetPhysicsSimulate(true);
		Player->SetMoveSpeed(300.f);
	}
}

void CCircleMap::LineCollisionEnd(CCollider* Src, CCollider* Dest)
{

}

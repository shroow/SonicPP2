#include "RihnoBot.h"
#include "../GameManager.h"
#include "../Scene/Camera.h"
#include "../Scene/Scene.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderLine.h"
#include "../Collision/ColliderCircle.h"
#include "BombS.h"

CRihnoBot::CRihnoBot() :
	m_HP(1)
{
	SetTypeID<CRihnoBot>();
}

CRihnoBot::CRihnoBot(const CRihnoBot& Obj) :
	CMonster(Obj)
{
}

CRihnoBot::~CRihnoBot()
{
}

bool CRihnoBot::Init()
{
	m_Pivot = { 0.5f, 1.f };
	m_MoveSpeed = 100.f;
	m_CharDir = { -1.f, 0.f };
	m_TurnCheck = false;
	m_MoveCheck = true;
	m_IdleCheck = false;
	m_TurnCount = 0.f;

	SetSize(48.f, 32.f);

	CreateAnimation();

	AddAnimation("RihnoRightIdle");
	AddAnimation("RihnoLeftIdle");
	AddAnimation("RihnoRightMove", false);
	AddAnimation("RihnoLeftMove", false);
	AddAnimation("RihnoRightTurn", false);
	AddAnimation("RihnoLeftTurn", false);

	SetEndFunction<CRihnoBot>("RihnoRightMove", this, &CRihnoBot::StopMove);
	SetEndFunction<CRihnoBot>("RihnoLeftMove", this, &CRihnoBot::StopMove);
	SetEndFunction<CRihnoBot>("RihnoRightTurn", this, &CRihnoBot::StopTurn);
	SetEndFunction<CRihnoBot>("RihnoLeftTurn", this, &CRihnoBot::StopTurn);

	m_vecSequenceKey[0].push_back("RihnoRightIdle");
	m_vecSequenceKey[0].push_back("RihnoRightMove");
	m_vecSequenceKey[0].push_back("RihnoRightTurn");

	m_vecSequenceKey[1].push_back("RihnoLeftIdle");
	m_vecSequenceKey[1].push_back("RihnoLeftMove");
	m_vecSequenceKey[1].push_back("RihnoLeftTurn");


	CColliderBox* Box = AddCollider<CColliderBox>("Monster");

	Box->SetExtent(48.f, 32.f);
	Box->SetOffset(0.f, -16.f);
	Box->SetCollisionProfile("Monster");

	Box->SetCollisionBeginFunction<CRihnoBot>(this, &CRihnoBot::CollisionBegin);
	Box->SetCollisionEndFunction<CRihnoBot>(this, &CRihnoBot::CollisionEnd);

	SetPhysicsSimulate(true);
	SetSideWallCheck(true);

	return true;
}

void CRihnoBot::Update(float DeltaTime)
{
	//화면에 안나오면 비활성
	//m_Scene->GetCamera()->GetWorldResolution();

	CGameObject::Update(DeltaTime);
	
	if (m_IdleCheck)
		m_TurnCount -= DELTA_TIME;

	if (m_TurnCount <= 0.f)
	{
		m_IdleCheck = false;
		m_TurnCheck = true;
	}

	if (m_MoveCheck)
		m_Pos += m_CharDir * m_MoveSpeed * DELTA_TIME * m_TimeScale;
}

void CRihnoBot::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	int	AnimDirIndex = 0;

	if (m_CharDir.x == -1.f)
		AnimDirIndex = 1;

	if (m_MoveCheck) //Move
	{
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][1]);
	}
	else if (m_TurnCheck)  //Turn
	{
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][2]);
	}
	else if (m_IdleCheck) //Idle
	{
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][0]);
	}
}

void CRihnoBot::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

bool CRihnoBot::InflictDamage(bool Damage)
{
	Damage = CMonster::InflictDamage(Damage);

	if (Damage)
	{
		--m_HP;

		if (m_HP <= 0)
		{
			CBombS* Bomb = m_Scene->CreateObject<CBombS>("BombS");
			Bomb->SetPos(m_Pos.x - m_Pivot.x * m_Size.x, m_Pos.y - m_Size.y);
			SetActive(false);
		}
			
	}

	return Damage;
}

void CRihnoBot::InflictSpeed(float Speed, Vector2 Dir)
{
	CMonster::InflictSpeed(Speed, Dir);
}

void CRihnoBot::StopMove()
{
	m_MoveCheck = false;
	m_IdleCheck = true;
	m_TurnCount = 1.f;
}

void CRihnoBot::StopTurn()
{
	if (m_CharDir.x == 1.f)
		m_CharDir.x = -1.f;

	else if(m_CharDir.x == -1.f)
		m_CharDir.x = 1.f;

	m_TurnCheck = false;
	m_MoveCheck = true;
}

void CRihnoBot::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	if (Dest->GetProfile()->Channel == ECollision_Channel::Player)
	{
		InflictDamage(true);
	}
}

void CRihnoBot::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}

void CRihnoBot::CollisionOn(CCollider* Src, CCollider* Dest)
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
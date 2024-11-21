#include "EggBossFire.h"

#include "../GameManager.h"
#include "../Scene/Camera.h"
#include "../Scene/Scene.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderLine.h"
#include "../Collision/ColliderCircle.h"
#include "BombS.h"
#include "SpinBoard.h"
#include "Fire.h"
#include "EggHead.h"

CEggBossFire::CEggBossFire() :
	m_HP(10)
{
	SetTypeID<CEggBossFire>();
}

CEggBossFire::CEggBossFire(const CEggBossFire& Obj) :
	CMonster(Obj)
{
}

CEggBossFire::~CEggBossFire()
{
}

bool CEggBossFire::Init()
{
	m_Pivot = { 0.5f, 0.5f };
	m_MoveSpeed = 200.f;
	m_CharDir = { -1.f, 0.f };
	m_HP = 10;
	m_StateCount = 2.f;
	m_PrevState = EBoss_State::None;
	m_TimeCount = 0.f;
	m_EffectCount = 0.f;

	SetSize(112.f, 64.f);

	m_BossHead = m_Scene->CreateObject<CEggHead>("Head");

	CreateAnimation();

	AddAnimation("EFBodyRightIdle");
	AddAnimation("EFBodyLeftIdle");
	AddAnimation("RightAttackBasic", false, 2.f);
	AddAnimation("LeftAttackBasic", false, 2.f);
	AddAnimation("RightAttackDown", false, 0.8f);
	AddAnimation("LeftAttackDown", false, 0.8f);



	//AddNotify<CEggBossFire>("EFBodyRightIdle", 0, this, &CEggBossFire::StartMove);
	//AddNotify<CEggBossFire>("EFBodyLeftIdle", 0, this, &CEggBossFire::StartMove);

	////SetEndFunction<CEggBossFire>("EFBodyRightIdle", this, &CEggBossFire::StopMove);
	////SetEndFunction<CEggBossFire>("EFBodyLeftIdle", this, &CEggBossFire::StopMove);

	AddNotify<CEggBossFire>("RightAttackBasic", 2, this, &CEggBossFire::FireBasic);
	AddNotify<CEggBossFire>("RightAttackBasic", 4, this, &CEggBossFire::FireBasic2);
	AddNotify<CEggBossFire>("LeftAttackBasic", 2, this, &CEggBossFire::FireBasic);
	AddNotify<CEggBossFire>("LeftAttackBasic", 4, this, &CEggBossFire::FireBasic2);

	AddNotify<CEggBossFire>("RightAttackDown", 3, this, &CEggBossFire::FireDown);
	AddNotify<CEggBossFire>("LeftAttackDown", 3, this, &CEggBossFire::FireDown);

	//SetEndFunction<CEggBossFire>("RightAttackBasic", this, &CEggBossFire::StartMove);
	//SetEndFunction<CEggBossFire>("LeftAttackBasic", this, &CEggBossFire::StartMove);
	//SetEndFunction<CEggBossFire>("RightAttackDown", this, &CEggBossFire::StartMove);
	//SetEndFunction<CEggBossFire>("LeftAttackDown", this, &CEggBossFire::StartMove);

	m_vecSequenceKey[0].push_back("EFBodyRightIdle");
	m_vecSequenceKey[0].push_back("RightAttackBasic");
	m_vecSequenceKey[0].push_back("RightAttackDown");

	m_vecSequenceKey[1].push_back("EFBodyLeftIdle");
	m_vecSequenceKey[1].push_back("LeftAttackBasic");
	m_vecSequenceKey[1].push_back("LeftAttackDown");

	CColliderBox* Body = AddCollider<CColliderBox>("EggBossFire");

	Body->SetExtent(112.f, 64.f);
	Body->SetCollisionProfile("Monster");

	Body->SetCollisionBeginFunction<CEggBossFire>(this, &CEggBossFire::CollisionBegin);
	Body->SetCollisionEndFunction<CEggBossFire>(this, &CEggBossFire::CollisionEnd);

	SetSideWallCheck(true);

	m_State = EBoss_State::Idle;

	return true;
}

void CEggBossFire::Update(float DeltaTime)
{
	
	Vector2 CameraPos = m_Scene->GetCamera()->GetPos();
	//if(m_Pos.x + 10.f > CameraPos.x && m_Pos.y + 10.f > CameraPos.y )
	{ }

	CGameObject::Update(DeltaTime);

	m_BossHead->SetPos(m_Pos.x, m_Pos.y - 40.f);
	m_BossHead->SetCharDir(m_CharDir.x);


	if (m_ImCount)
	{
		m_ImCount -= DELTA_TIME;
		if (m_ImCount < 0.f)
			m_ImCount = 0.f;
	}

	if (m_StateCount)
	{
		m_StateCount -= DELTA_TIME;
		if (m_StateCount < 0.f)
			m_StateCount = 0.f;
	}

	Vector2 CenterPos = { 7861.f, 695.f };
	Vector2 LeftPos = { 7561.f, 725.f };
	Vector2 RightPos = { 8161.f, 725.f };
	//상태따른 행동만
	switch (m_State)
	{
	case EBoss_State::None:
		break;
	case EBoss_State::Idle:
		break;
	case EBoss_State::Move1:	//지정위치 이동 CharDir 따라 위치 변경
		if (m_CharDir.x == 1.f)
			m_Pos += (RightPos - m_Pos) * DELTA_TIME * 0.8f;
		else if (m_CharDir.x == -1.f)
			m_Pos += (LeftPos - m_Pos) * DELTA_TIME * 0.8f;
		break;
	case EBoss_State::Move2:	//7895 635 중앙으로 이동
		m_Pos += (CenterPos - m_Pos)  * DELTA_TIME * 0.8f;
		break;
	case EBoss_State::Attack1:
		m_TimeCount = 0.5f;
		m_BossHead->SetCharDir(m_CharDir.x * -1.f);
		break;
	case EBoss_State::Attack2:
		m_TimeCount = 0.5f;
		break;
	case EBoss_State::Hurt:

		break;
	case EBoss_State::Die:
		m_Pos.y += 120.f * DELTA_TIME;
		m_BossHead->SetState(EBoss_State::Die);
		break;
	}
}

void CEggBossFire::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	int	AnimDirIndex = 0;

	if (m_CharDir.x == -1.f)
		AnimDirIndex = 1;

	//상태를 바꿔주기
	switch (m_State)
	{
	case EBoss_State::None:
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][0]);
		break;
	case EBoss_State::Idle:
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][0]);
		if (m_StateCount <= 0.f)
		{
			m_State = EBoss_State::Attack1;
			m_StateCount = 2.5f;
		}
		break;
	case EBoss_State::Move1:	//지정거리 이동
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][0]);
		if (m_StateCount <= 0.f)
		{
			m_State = EBoss_State::Idle;
			m_StateCount = 0.7f;
		}
		break;
	case EBoss_State::Move2:	//7895 635 중앙으로 이동
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][0]);
		if (m_StateCount <= 0.f)
		{
			m_State = EBoss_State::Attack2;
			m_StateCount = 2.f;
		}
		break;
	case EBoss_State::Attack1:
		if (AnimDirIndex == 1)
		{
			ChangeAnimation(m_vecSequenceKey[0][1]); 
			m_BossHead->SetCharDir(1.f);
		}
		else if (AnimDirIndex == 0)
		{
			ChangeAnimation(m_vecSequenceKey[1][1]);
			m_BossHead->SetCharDir(-1.f);
		}
		if (m_StateCount <= 0.f)
		{
			m_State = EBoss_State::Move2;
			m_StateCount = 2.f;
			m_CharDir.x *= -1.f;
		}
		break;
	case EBoss_State::Attack2:
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][2]);
		if (m_StateCount <= 0.f)
		{
			m_State = EBoss_State::Move1;
			m_StateCount = 2.f;
		}
		break;
	case EBoss_State::Hurt:
		break;
	case EBoss_State::Die:
		///죽는 모션 추가
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][2]);

		m_TimeCount -= DELTA_TIME;
		if (m_TimeCount <= 0.f)
		{
			m_TimeCount = 0.5f;
			
			Die();
			
			if (m_EffectCount <= 0)
			{
				CSpinBoard* SpinBoard = m_Scene->CreateObject<CSpinBoard>("SpinBoard");
				SpinBoard->SetPos(7861.f, 600.f);
				SetActive(false);
			}
		}

		break;
	}
}

void CEggBossFire::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

bool CEggBossFire::InflictDamage(bool Damage)
{
	Damage = CMonster::InflictDamage(Damage);

	if (Damage)
	{
		--m_HP;

		if (m_HP == 0)
		{
			m_State = EBoss_State::Die;
			m_TimeCount = 0.3f;
			m_EffectCount = 7;
		}
	}

	return Damage;
}

void CEggBossFire::InflictSpeed(float Speed, Vector2 Dir)
{
	CMonster::InflictSpeed(Speed, Dir);
}

void CEggBossFire::StartMove()
{
	MoveDir(m_MoveSpeed, m_CharDir);
}

void CEggBossFire::StopMove()
{
	m_CharDir.x *= -1.f;
	m_StateCount = 1.f;
}

void CEggBossFire::StopTurn()
{
	if (m_CharDir.x == 1.f)
		m_CharDir.x = -1.f;

	else if (m_CharDir.x == -1.f)
		m_CharDir.x = 1.f;

	m_StateCount = 1.f;
}

void CEggBossFire::FireBasic()
{
	m_TimeCount -= DELTA_TIME;
	if (m_TimeCount <= 0.f)
		return;
	CFire* Fire = m_Scene->CreateObject<CFire>("Fire");
	Fire->SetState(0, m_CharDir.x, m_Pos);
}

void CEggBossFire::FireBasic2()
{
	m_TimeCount -= DELTA_TIME;
	if (m_TimeCount <= 0.f)
		return;

	Vector2 Pos;
	Pos.x = m_Pos.x - m_CharDir.x * 50.f;
	Pos.y = m_Pos.y;

	CFire* Fire = m_Scene->CreateObject<CFire>("Fire");
	Fire->SetState(0, m_CharDir.x, Pos);
}

void CEggBossFire::FireDown()
{
	m_TimeCount -= DELTA_TIME;
	if (m_TimeCount <= 0.f)
		return;

	Vector2 Pos;
	Pos.x = m_Pos.x - m_CharDir.x * 10.f;
	Pos.y = m_Pos.y + 4.f;

	CFire* Fire = m_Scene->CreateObject<CFire>("Fire");
	Fire->SetState(2, m_CharDir.x, Pos);

	Pos.x = m_Pos.x * m_CharDir.x * 20.f;
	Pos.y = m_Pos.y + 8.f;

	CFire* Fire2 = m_Scene->CreateObject<CFire>("Fire");
	Fire2->SetState(2, m_CharDir.x, Pos);
}

void CEggBossFire::Die()
{
	CBombS* Bomb = m_Scene->CreateObject<CBombS>("BombS");
	Bomb->SetPos(m_Pos.x - m_Size.x * 0.2f, m_Pos.y - m_Size.y * 0.3f);
	Bomb->SetDuration(2.f);

	CBombS* Bomb1 = m_Scene->CreateObject<CBombS>("BombS");
	Bomb1->SetPos(m_Pos.x - m_Size.x * 0.3f, m_Pos.y + m_Size.y * 0.6f);
	Bomb1->SetDuration(3.f);

	CBombS* Bomb2 = m_Scene->CreateObject<CBombS>("BombS");
	Bomb2->SetPos(m_Pos.x + m_Size.x * 0.7f, m_Pos.y - m_Size.y * 0.2f);
	Bomb2->SetDuration(3.f);

	CBombS* Bomb3 = m_Scene->CreateObject<CBombS>("BombS");
	Bomb3->SetPos(m_Pos.x + m_Size.x * 0.4f, m_Pos.y + m_Size.y * 0.4f);
	Bomb3->SetDuration(2.f);

	--m_EffectCount;
}

void CEggBossFire::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	if (Dest->GetProfile()->Channel == ECollision_Channel::Player)
	{
		if (!m_ImCount)
		{
			InflictDamage(true);
			m_ImCount = 0.8f;
			m_BossHead->SetState(EBoss_State::Hurt);
		}
	}
}

void CEggBossFire::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}
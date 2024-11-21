#include "Fire.h"
#include "../GameManager.h"
#include "../Collision/ColliderBox.h"

CFire::CFire()
{
}

CFire::CFire(const CFire& Obj) :
	CEffect(Obj)
{
}

CFire::~CFire()
{
}

void CFire::SetState(int State, float Dir, Vector2 Pos)
{
	m_State = State;
	m_Dir = Dir;
	m_Pos = Pos;
}

bool CFire::Init()
{
	SetPivot(0.5f, 0.5f);
	m_TimeCount = 2.f;

	m_Box = AddCollider<CColliderBox>("Fire");

	m_Box->SetCollisionProfile("Monster");

	m_Box->SetCollisionBeginFunction<CFire>(this, &CFire::CollisionBegin);
	m_Box->SetCollisionEndFunction<CFire>(this, &CFire::CollisionEnd);

	// 애니메이션 1개를 무조건 가지고 있게 해준다.
	CreateAnimation();

	AddAnimation("FireAngleRight", true, 1.f);
	AddAnimation("FireAngleLeft", true, 1.f);
	AddAnimation("FireGroundRight", true, 1.f);
	AddAnimation("FireGroundLeft", true, 1.f);
	AddAnimation("FireDown", true, 1.f);


	m_vecSequenceKey[0].push_back("FireAngleLeft");
	m_vecSequenceKey[0].push_back("FireGroundLeft");
	m_vecSequenceKey[0].push_back("FireDown");
	
	m_vecSequenceKey[1].push_back("FireAngleRight");
	m_vecSequenceKey[1].push_back("FireGroundRight");
	m_vecSequenceKey[1].push_back("FireDown");

	return true;
}

void CFire::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);

	switch (m_State)
	{
	case 0:	//FireAngle
		if(m_Dir == 1.f)
			MoveAngle(135.f, 120.f);
		else if (m_Dir == -1.f)
			MoveAngle(45.f, 120.f);

		m_TimeCount -= DELTA_TIME;
		if (m_TimeCount <= 0.f)
		{
			m_State = 1;
			m_TimeCount = 2.f;
		}
		break;
	case 1: //FireGround
		if (m_Dir == 1.f)
			MoveAngle(180.f, 150.f);
		else if (m_Dir == -1.f)
			MoveAngle(0.f, 150.f);

		m_TimeCount -= DELTA_TIME;
		if (m_TimeCount <= 0.f)
		{
			SetActive(false);
		}
		break;
	case 2: //FireDown
		MoveAngle(90.f, 150.f);

		m_TimeCount -= DELTA_TIME;
		if (m_TimeCount <= 0.f)
		{
			SetActive(false);
		}
		break;
	}
}

void CFire::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);

	int AnimDirIndex = 0;

	if (m_Dir == -1.f)
		AnimDirIndex = 1;

	switch (m_State)
	{
	case 0:	//FireAngle
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][0]);
		m_Box->SetExtent(40.f, 40.f);
		break;
	case 1: //FireGround
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][1]);
		m_Box->SetExtent(48.f, 24.f);
		break;
	case 2: //FireDown
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][2]);
		m_Box->SetExtent(24.f, 48.f);
		break;
	}
}

void CFire::Render(HDC hDC, float DeltaTime)
{
	CEffect::Render(hDC, DeltaTime);
}

void CFire::AnimationEnd()
{
	if (m_EffectType == EEffect_Type::Once)
		SetActive(false);
}


void CFire::CollisionBegin(CCollider* Src, CCollider* Dest)
{
}

void CFire::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}
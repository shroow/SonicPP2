#include "EggHead.h"

CEggHead::CEggHead()
{
}

CEggHead::CEggHead(const CEggHead& Obj)	:
	CGameObject(Obj)
{
}

CEggHead::~CEggHead()
{
}

bool CEggHead::Init()
{
	m_TimeCount = 1.f;
	m_State = EBoss_State::Idle;

	SetPivot(0.5f, 0.5f);

	CreateAnimation();

	AddAnimation("EFHeadRightIdle");
	AddAnimation("EFHeadLeftIdle");
	AddAnimation("EFHurtRight");
	AddAnimation("EFHurtLeft");
	AddAnimation("EFDieRight");
	AddAnimation("EFDieLeft");

	m_vecSequenceKey[0].push_back("EFHeadRightIdle");
	m_vecSequenceKey[0].push_back("EFHurtRight");
	m_vecSequenceKey[0].push_back("EFDieRight");

	m_vecSequenceKey[1].push_back("EFHeadLeftIdle");
	m_vecSequenceKey[1].push_back("EFHurtLeft");
	m_vecSequenceKey[1].push_back("EFDieLeft");

	return true;
}

void CEggHead::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CEggHead::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	int AnimDirIndex = 0;
	if (m_CharDir.x == -1.f)
		AnimDirIndex = 1;

	switch (m_State)
	{
	case EBoss_State::None:
		break;
	case EBoss_State::Idle:
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][0]);
		break;
	case EBoss_State::Hurt:
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][1]);
		m_TimeCount -= DeltaTime;
		if (m_TimeCount <= 0.f)
		{
			m_TimeCount = 1.f;
			m_State = EBoss_State::Idle;
		}
		break;
	case EBoss_State::Die:
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][2]);
		break;
	}
}

void CEggHead::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

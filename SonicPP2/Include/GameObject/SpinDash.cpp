#include "SpinDash.h"

CSpinDash::CSpinDash()
{
}

CSpinDash::CSpinDash(const CSpinDash& Obj) :
	CEffect(Obj)
{
}

CSpinDash::~CSpinDash()
{
}

bool CSpinDash::Init()
{
	// �ִϸ��̼� 1���� ������ ������ �ְ� ���ش�.
	CreateAnimation();

	AddAnimation("RightSpinDashEffet", true, 0.4f);
	AddAnimation("LeftSpinDashEffet", true, 0.4f);

	return true;
}

void CSpinDash::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);
}

void CSpinDash::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);
}

void CSpinDash::Render(HDC hDC, float DeltaTime)
{
	int AnimationDir = 0;

	if (m_Dir == -1.f)
		AnimationDir = 1;

	switch (AnimationDir)
	{
	case 0:
		SetPivot(0.7f, 0.5f);
		ChangeAnimation("RightSpinDashEffet");
		break;
	case 1:
		SetPivot(0.3f, 0.5f);
		ChangeAnimation("LeftSpinDashEffet");
		break;
	default:
		ChangeAnimation("RightSpinDashEffet");
		break;
	}

	CEffect::Render(hDC, DeltaTime);
}

void CSpinDash::AnimationEnd()
{
	if (m_EffectType == EEffect_Type::Once)
		SetActive(false);
}

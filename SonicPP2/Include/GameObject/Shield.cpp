#include "Shield.h"

CShield::CShield()
{
}

CShield::CShield(const CShield& Obj) :
	CEffect(Obj)
{
}

CShield::~CShield()
{
}

bool CShield::Init()
{
	// �ִϸ��̼� 1���� ������ ������ �ְ� ���ش�.
	CreateAnimation();

	SetCurrentAnimationEndFunction<CShield>(this, &CShield::AnimationEnd);

	return true;
}

void CShield::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);
}

void CShield::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);
}

void CShield::Render(HDC hDC, float DeltaTime)
{
	CEffect::Render(hDC, DeltaTime);
}

void CShield::AnimationEnd()
{
	if (m_EffectType == EEffect_Type::Once)
		SetActive(false);
}
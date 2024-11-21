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
	// 애니메이션 1개를 무조건 가지고 있게 해준다.
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
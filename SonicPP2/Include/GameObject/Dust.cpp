#include "Dust.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CDust::CDust()
{
}

CDust::CDust(const CDust& Obj) :
	CEffect(Obj)
{
}

CDust::~CDust()
{
}

bool CDust::Init()
{
	m_EffectType = EEffect_Type::Once;

	// �ִϸ��̼� 1���� ������ ������ �ְ� ���ش�.
	CreateAnimation();

	AddAnimation("DustEffect", false, 0.5f);

	SetCurrentAnimationEndFunction<CDust>(this, &CDust::AnimationEnd);

	return true;
}

void CDust::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);
}

void CDust::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);
}

void CDust::Render(HDC hDC, float DeltaTime)
{
	CEffect::Render(hDC, DeltaTime);
}

void CDust::AnimationEnd()
{
	if (m_EffectType == EEffect_Type::Once)
		SetActive(false);
}
#include "BombS.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CBombS::CBombS()
{
}

CBombS::CBombS(const CBombS& Obj) :
	CEffect(Obj)
{
}

CBombS::~CBombS()
{
}

bool CBombS::Init()
{
	m_EffectType = EEffect_Type::Once;

	// �ִϸ��̼� 1���� ������ ������ �ְ� ���ش�.
	CreateAnimation();

	AddAnimation("SmallBombEffet", false, 0.5f);

	m_Scene->GetSceneResource()->SoundPlay("SmallBomb");

	SetCurrentAnimationEndFunction<CBombS>(this, &CBombS::AnimationEnd);

	return true;
}

void CBombS::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);
}

void CBombS::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);
}

void CBombS::Render(HDC hDC, float DeltaTime)
{
	CEffect::Render(hDC, DeltaTime);
}

void CBombS::AnimationEnd()
{
	if (m_EffectType == EEffect_Type::Once)
		SetActive(false);
}

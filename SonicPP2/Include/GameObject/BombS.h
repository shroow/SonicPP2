#pragma once
#include "Effect.h"
class CBombS :
    public CEffect
{
    	friend class CScene;

protected:
	CBombS();
	CBombS(const CBombS& Obj);
	virtual ~CBombS();

public:
	EEffect_Type GetEffectType()	const
	{
		return m_EffectType;
	}

	void SetDuration(float Duration)
	{
		m_Duration = Duration;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void AnimationEnd();
};


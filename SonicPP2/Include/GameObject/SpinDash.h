#pragma once
#include "Effect.h"
class CSpinDash :
    public CEffect
{
	friend class CScene;

protected:
	CSpinDash();
	CSpinDash(const CSpinDash& Obj);
	virtual ~CSpinDash();

private:
	float	m_Dir;

public:
	void SetDir(float Dir)
	{
		m_Dir = Dir;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void AnimationEnd();
};


#pragma once

#include "GameObject.h"

class CStartBack :
    public CGameObject
{
	friend class CScene;

protected:
	CStartBack();
	CStartBack(const CStartBack& Obj);
	virtual ~CStartBack();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
};


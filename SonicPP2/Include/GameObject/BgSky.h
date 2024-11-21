#pragma once

#include "GameObject.h"

class CBgSky :
	public CGameObject
{
	friend class CScene;

protected:
	CBgSky();
	CBgSky(const CBgSky& Obj);
	virtual ~CBgSky();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
};


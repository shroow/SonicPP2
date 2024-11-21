#pragma once
#include "GameObject.h"
class CBgForest :
    public CGameObject
{
	friend class CScene;

protected:
	CBgForest();
	CBgForest(const CBgForest& Obj);
	virtual ~CBgForest();

protected:
	std::vector<class CGameObject*>	m_vecTexture;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
};


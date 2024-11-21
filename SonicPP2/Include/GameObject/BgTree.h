#pragma once
#include "GameObject.h"
class CBgTree :
    public CGameObject
{
	friend class CScene;

protected:
	CBgTree();
	CBgTree(const CBgTree& Obj);
	virtual ~CBgTree();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
};


#pragma once
#include "GameObject.h"
class CItemBox :
    public CGameObject
{
	friend class CScene;

protected:
	CItemBox();
	CItemBox(const CItemBox& Obj);
	virtual ~CItemBox();

private:
	

public:



public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual void InflictSpeed(float Speed, Vector2 Dir);

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};


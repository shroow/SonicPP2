#pragma once
#include "GameObject.h"

class CSpring :
    public CGameObject
{
	friend class CScene;

protected:
	CSpring();
	CSpring(const CSpring& Obj);
	virtual ~CSpring();

private:
	bool		m_Bounce;
	EObject_Dir	m_ObjectDir;

public:
	void SetIdle()
	{
		m_Bounce = false;
	}


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual void InflictSpeed(float Speed, Vector2 Dir);

public:
	void SetObjectDir(EObject_Dir Dir)
	{
		m_ObjectDir = Dir;
	}

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};


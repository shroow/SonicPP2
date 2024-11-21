#pragma once

#include "GameObject.h"

class CSpinBoard :
	public CGameObject
{
	friend class CScene;

protected:
	CSpinBoard();
	CSpinBoard(const CSpinBoard& Obj);
	virtual ~CSpinBoard();

private:
	bool	m_CheckCreate;
	float	m_TimeCount;

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


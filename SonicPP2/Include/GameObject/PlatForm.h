#pragma once
#include "MapObject.h"
class CPlatForm :
    public CMapObject
{
	friend class CScene;

protected:
	CPlatForm();
	CPlatForm(const CPlatForm& Obj);
	virtual ~CPlatForm();

private:
	bool	m_CheckMove;
	float   m_MoveCount;
	float	m_MoveDir;

public:
	void SetMove()
	{
		m_CheckMove = true;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual bool InflictDamage(bool Damage);
	virtual Vector2 InflictSpeed(Vector2 Speed);

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};


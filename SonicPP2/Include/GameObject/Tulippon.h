#pragma once
#include "Monster.h"
class CTulippon :
    public CMonster
{
	friend class CScene;

protected:
	CTulippon();
	CTulippon(const CTulippon& Obj);
	virtual ~CTulippon();

private:
	float	m_FireCount;
	int		m_HP;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual bool InflictDamage(bool Damage);

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
	void CollisionOn(CCollider* Src, CCollider* Dest);
};


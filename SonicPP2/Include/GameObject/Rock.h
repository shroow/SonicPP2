#pragma once
#include "MapObject.h"
class CRock :
	public CMapObject
{
	friend class CScene;

protected:
	CRock();
	CRock(const CRock& Obj);
	virtual ~CRock();

private:
	EObject_Type	m_RockType;
	bool			m_Breakable;

	CSharedPtr<class CColliderBox>	m_ColliBox;

public:
	void SetRockType(EObject_Type Type, bool Breakable);

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


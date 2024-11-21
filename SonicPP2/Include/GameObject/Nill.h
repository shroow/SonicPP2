#pragma once
#include "MapObject.h"
class CNill :
	public CMapObject
{
	friend class CScene;

protected:
	CNill();
	CNill(const CNill& Obj);
	virtual ~CNill();

private:
	EObject_Dir	m_NillDir;

	CSharedPtr<class CColliderBox>	m_ColliBox;

public:
	void SetNillDir(EObject_Dir Dir);

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


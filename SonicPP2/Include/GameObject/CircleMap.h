#pragma once
#include "GameObject.h"
class CCircleMap :
	public CGameObject
{
	friend class CScene;

protected:
	CCircleMap();
	CCircleMap(const CCircleMap& Obj);
	virtual ~CCircleMap();

private:
	bool	m_CenterCollide;
	bool	m_RightCollide;
	bool	m_LeftCollide;

	CSharedPtr<class CColliderBox>	m_RightIncom;
	CSharedPtr<class CColliderBox>	m_LeftIncom;
	CSharedPtr<class CColliderBox>	m_CenterIncom;
	CSharedPtr<class CColliderLine>	m_LineRight;
	CSharedPtr<class CColliderLine>	m_LineLeft;

public:
	void SetLine();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void RightIncomCollisionBegin(CCollider* Src, CCollider* Dest);
	void RightIncomCollisionEnd(CCollider* Src, CCollider* Dest);
	void LeftIncomCollisionBegin(CCollider* Src, CCollider* Dest);
	void LeftIncomCollisionEnd(CCollider* Src, CCollider* Dest);
	void CenterIncomCollisionBegin(CCollider* Src, CCollider* Dest);
	void CenterIncomCollisionEnd(CCollider* Src, CCollider* Dest);

	void LineCollisionBegin(CCollider* Src, CCollider* Dest);
	void LineCollisionEnd(CCollider* Src, CCollider* Dest);
};


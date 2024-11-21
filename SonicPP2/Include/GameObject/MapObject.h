#pragma once
#include "GameObject.h"
class CMapObject :
    public CGameObject
{
	friend class CScene;

protected:
	CMapObject();
	CMapObject(const CMapObject& Obj);
	virtual ~CMapObject();

protected:
	bool	m_Breakable;

public:
	bool GetBreakable()	const
	{
		return m_Breakable;
	}

	void SetDuration(bool Breakable)
	{
		m_Breakable = Breakable;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
};


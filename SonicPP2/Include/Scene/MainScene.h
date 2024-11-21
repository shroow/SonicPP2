#pragma once
#include "Scene.h"
class CMainScene :
    public CScene
{
	friend class CSceneManager;

protected:
	CMainScene();
	virtual ~CMainScene();

public:
	virtual bool GetDEBUG() const
	{
		return m_DEBUG;
	}
public:
	bool Init();

private:
	void CreateAnimationSequence();

private:
	void Cam1Key();
	void Cam2Key();
};


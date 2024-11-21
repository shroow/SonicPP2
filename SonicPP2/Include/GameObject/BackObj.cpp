
#include "BackObj.h"
#include "../Scene/Camera.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../Resource/Texture/Texture.h"

CBackObj::CBackObj()
{
	SetTypeID<CBackObj>();
	m_RenderLayer = ERender_Layer::Back;
}

CBackObj::CBackObj(const CBackObj& Obj)	:
	CGameObject(Obj)
{
}

CBackObj::~CBackObj()
{
}

bool CBackObj::Init()
{
	SetPos(0.f, 595.f);
	SetSize(3840.f, 344.f);
	SetPivot(0.5f, 0.6f);


	SetTexture("S1A1Back", TEXT("Stage1/Background/BgForest1.bmp"));

	return true;
}

void CBackObj::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBackObj::Render(HDC hDC, float DeltaTime)
{
	//CGameObject::Render(hDC, DeltaTime);

	Vector2	Pos;
	Vector2	CameraPos;
	Vector2	Resolution;
	Vector2 WorldResolution;

	if (m_Scene)
	{
		CameraPos = m_Scene->GetCamera()->GetPos();
		Resolution = m_Scene->GetCamera()->GetResolution();
		Pos = m_Pos - m_Scene->GetCamera()->GetPos();
		WorldResolution = m_Scene->GetCamera()->GetWorldResolution() - Resolution;
	}

	else
	{
		CScene* Scene = CSceneManager::GetInst()->GetScene();
		Pos = m_Pos - Scene->GetCamera()->GetPos();
		CameraPos = Scene->GetCamera()->GetPos();
		Resolution = Scene->GetCamera()->GetResolution();
		WorldResolution = Scene->GetCamera()->GetWorldResolution() - Resolution;
	}

	if (m_Texture)
	{
		Vector2	RenderLT;
		Vector2 WorldPivot;

		WorldPivot = CameraPos / WorldResolution;

		RenderLT = m_Pos - m_Size * WorldPivot;

		if (m_Texture)
		{
			BitBlt(hDC, 
				(int)(RenderLT.x * m_Pivot.x),
				(int)(RenderLT.y * m_Pivot.y),
				(int)m_Size.x, (int)m_Size.y, m_Texture->GetDC(),
				0, 0, SRCCOPY);
		}
	}

	//if (m_Texture)
	//{
	//	BitBlt(hDC, -40, -40,
	//		(int)m_Size.x, (int)m_Size.y, m_Texture->GetDC(),
	//		0, 0, SRCCOPY);
	//}
}
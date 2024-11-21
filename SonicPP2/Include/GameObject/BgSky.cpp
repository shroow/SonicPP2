
#include "BgSky.h"
#include "../Scene/Camera.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../Resource/Texture/Texture.h"

CBgSky::CBgSky()
{
	SetTypeID<CBgSky>();
	m_RenderLayer = ERender_Layer::Back;
}

CBgSky::CBgSky(const CBgSky& Obj) :
	CGameObject(Obj)
{
}

CBgSky::~CBgSky()
{
}

bool CBgSky::Init()
{
	SetPos(0.f, 100.f);
	SetSize(3840.f, 404.f);
	SetPivot(0.5f, 0.9f);

	SetTexture("S1A1Sky", TEXT("Stage1/Background/BgSkyC.bmp"));

	return true;
}

void CBgSky::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBgSky::Render(HDC hDC, float DeltaTime)
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
}
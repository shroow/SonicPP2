
#include "StartBack.h"
#include "../Scene/Camera.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../Resource/Texture/Texture.h"

CStartBack::CStartBack()
{
	SetTypeID<CStartBack>();
	m_RenderLayer = ERender_Layer::Back;
}

CStartBack::CStartBack(const CStartBack& Obj)	:
	CGameObject(Obj)
{
}

CStartBack::~CStartBack()
{
}

bool CStartBack::Init()
{
	SetPos(0.f, 0.f);
	SetSize(800.f, 480.f);
	SetPivot(0.f, 0.f);

	SetTexture("StartBack", TEXT("StageTitle/StartWindow/BgStart.bmp"));

	return true;
}

void CStartBack::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CStartBack::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

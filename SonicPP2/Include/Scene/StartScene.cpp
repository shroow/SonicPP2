
#include "StartScene.h"
#include "../GameObject/BackObj.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"
#include "../Widget/StartWindow.h"
#include "../GameObject/StartBack.h"

CStartScene::CStartScene()
{
}

CStartScene::~CStartScene()
{
}

bool CStartScene::Init()
{

	GetCamera()->SetResolution(800.f, 480.f);
	GetCamera()->SetWorldResolution(800.f, 480.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	CInput::GetInst()->SetMouseOn(true);

	CStartBack* BackObj = CreateObject<CStartBack>("StartBack");

	CreateWidgetWindow<CStartWindow>("StartWindow");

	return true;
}

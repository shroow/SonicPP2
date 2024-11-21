

#include "StartWindow.h"
#include "Button.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../GameManager.h"
#include "../Scene/MainScene.h"
#include "../Scene/SceneManager.h"
#include "../Input.h"
#include "ImageWidget.h"
#include "Text.h"
#include "Number.h"
#include "../GameManager.h"
#include "../Scene/EditScene.h"

CStartWindow::CStartWindow()
{
}

CStartWindow::~CStartWindow()
{
}

bool CStartWindow::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	//m_Scene->GetSceneResource()->LoadSound("UI", "ButtonHovered", false,
	//	"1Up.wav");
	//m_Scene->GetSceneResource()->LoadSound("UI", "ButtonClick", false,
	//	"Stun.wav");

	SetSize(800.f, 480.f);

	//CImageWidget* Back = CreateWidget<CImageWidget>("Back");

	//Back->SetTexture("StartBack", TEXT("StageTitle/StartWindow/BgStart.bmp"));

	//Back->SetSize(800.f, 480.f);	
	
	CImageWidget* MainImg = CreateWidget<CImageWidget>("Back");

	MainImg->SetTexture("MainImg", TEXT("StageTitle/StartWindow/Main2.bmp"));

	MainImg->SetColorKey(255, 0, 255);

	MainImg->SetSize(800.f, 480.f);

	CButton* StartButton = CreateWidget<CButton>("StartButton");

	StartButton->SetTexture("StartButton", TEXT("StageTitle/StartWindow/StartButton.bmp"));
	StartButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(192.f, 16.f));
	StartButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(192.f, 0.f), Vector2(384.f, 16.f));
	StartButton->SetButtonStateData(EButton_State::Click, Vector2(192.f, 0.f), Vector2(384.f, 16.f));
	StartButton->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(192.f, 16.f));
	m_Scene->GetSceneResource()->SetColorKey("StartButton", 255, 0, 255);

	StartButton->SetSound(EButton_Sound_State::MouseHovered, "ButtonHovered");
	StartButton->SetSound(EButton_Sound_State::Click, "ButtonClick");

	StartButton->SetPos(320.f, 410.f);
	StartButton->SetZOrder(1);

	StartButton->SetCallback<CStartWindow>(EButton_Sound_State::Click,
		this, &CStartWindow::StartButtonCallback);

	CButton* EditButton = CreateWidget<CButton>("EditButton");

	EditButton->SetTexture("EditButton", TEXT("StageTitle/StartWindow/EditButton.bmp"));
	EditButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(192.f, 16.f));
	EditButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(192.f, 0.f), Vector2(384.f, 16.f));
	EditButton->SetButtonStateData(EButton_State::Click, Vector2(192.f, 0.f), Vector2(384.f, 16.f));
	EditButton->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(192.f, 16.f));
	m_Scene->GetSceneResource()->SetColorKey("EditButton", 255, 0, 255);

	EditButton->SetSound(EButton_Sound_State::MouseHovered, "ButtonHovered");
	EditButton->SetSound(EButton_Sound_State::Click, "ButtonClick");

	EditButton->SetPos(320, 440.f);

	EditButton->SetZOrder(1);

	EditButton->SetCallback<CStartWindow>(EButton_Sound_State::Click,
		this, &CStartWindow::EditButtonCallback);

	//CButton* EndButton = CreateWidget<CButton>("EndButton");

	//EndButton->SetTexture("EndButton", TEXT("UI/EditButton.bmp"));
	//EndButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(200.f, 100.f));
	//EndButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(200.f, 0.f), Vector2(400.f, 100.f));
	//EndButton->SetButtonStateData(EButton_State::Click, Vector2(400.f, 0.f), Vector2(600.f, 100.f));
	//EndButton->SetButtonStateData(EButton_State::Disable, Vector2(600.f, 0.f), Vector2(800.f, 100.f));

	//EndButton->SetSound(EButton_Sound_State::MouseHovered, "ButtonHovered");
	//EndButton->SetSound(EButton_Sound_State::Click, "ButtonClick");

	//EndButton->SetPos(600.f, 340.f);
	//EndButton->SetZOrder(1);

	//EndButton->SetCallback<CStartWindow>(EButton_Sound_State::Click,
	//	this, &CStartWindow::EndButtonCallback);

	//m_Text = CreateWidget<CText>("Text");

	//m_Text->SetText(TEXT("ÅØ½ºÆ® Ãâ·Â!!"));
	//m_Text->SetPos(10.f, 50.f);
	//m_Text->SetTextColor(255, 0, 0);

	//m_Text->EnableShadow(true);
	//m_Text->SetShadowOffset(5.f, 5.f);

	//m_TextTime = 0.f;

	//memset(m_AddText, 0, sizeof(TCHAR) * 32);
	//lstrcpy(m_AddText, TEXT("Èæ¿°·æ"));
	//m_AddCount = 0;

	m_FPSText = CreateWidget<CText>("StartText");

	m_FPSText->SetText(TEXT("FPS"));
	m_FPSText->SetPos(600.f, 50.f);
	m_FPSText->SetTextColor(255, 0, 0);

	m_FPSText->EnableShadow(true);
	m_FPSText->SetShadowOffset(2.f, 2.f);


	return true;
}

void CStartWindow::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	//SYSTEMTIME	Time;

	//GetLocalTime(&Time);

	//m_Hour->SetNumber(Time.wHour);
	//m_Minute->SetNumber(Time.wMinute);
	//m_Second->SetNumber(Time.wSecond);


	if (m_AddCount < lstrlen(m_AddText))
	{
		m_TextTime += DeltaTime;

		if (m_TextTime >= 1.f)
		{
			m_TextTime -= 1.f;

			m_Text->AddText(m_AddText[m_AddCount]);

			++m_AddCount;
		}
	}

	float FPS = CGameManager::GetInst()->GetFPS();

	char	Text[256] = {};
	sprintf_s(Text, "FPS : %.5f", FPS);

	TCHAR	Unicode[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

	m_FPSText->SetText(Unicode);
}

void CStartWindow::StartButtonCallback()
{
	//CInput::GetInst()->ClearCallback();
	CSceneManager::GetInst()->CreateScene<CMainScene>();
}

void CStartWindow::EditButtonCallback()
{
	//CInput::GetInst()->ClearCallback();
	CSceneManager::GetInst()->CreateScene<CEditScene>();
}

void CStartWindow::EndButtonCallback()
{
	CGameManager::GetInst()->Exit();
}

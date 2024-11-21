#include "ClearBoard.h"
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

CClearBoard::CClearBoard()
{
}

CClearBoard::~CClearBoard()
{
}

bool CClearBoard::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	SetSize(200.f, 100.f);
	SetPos(0.f, 0.f);

	m_Score = CreateWidget<CImageWidget>("Score");
	m_Score->SetTexture("ClearBoard", TEXT("UI/ClearBoard.bmp"));
	m_Score->SetSize(639.f, 481.f);
	m_Score->SetPos(80.f, 0);
	m_Score->SetColorKey(255, 0, 255);

	//m_Time = CreateWidget<CImageWidget>("Time");
	//m_Time->SetTexture("TimeHUD", TEXT("HUD/Time.bmp"));
	//m_Time->SetSize(40.f, 16.f);
	//m_Time->SetPos(45.f, 55.f);
	//m_Time->SetColorKey(255, 0, 255);

	//m_Rings = CreateWidget<CImageWidget>("Rings");
	//m_Rings->SetTexture("RingsHUD", TEXT("HUD/Rings.bmp"));
	//m_Rings->SetSize(49.f, 16.f);
	//m_Rings->SetPos(45.f, 75.f);
	//m_Rings->SetColorKey(255, 0, 255);

	//m_MinuteCount = CreateWidget<CNumber>("Minute");
	//m_SecondCount = CreateWidget<CNumber>("Second");
	//m_RingCount = CreateWidget<CNumber>("RingCount");


	//std::vector<std::wstring>	vecFileName;

	//for (int i = 0; i <= 9; ++i)
	//{
	//	TCHAR	FileName[MAX_PATH] = {};
	//	// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
	//	wsprintf(FileName, TEXT("HUD/Number/%d.bmp"), i);
	//	vecFileName.push_back(FileName);
	//}


	//m_MinuteCount->SetTexture("Number", vecFileName);
	//m_SecondCount->SetTexture("Number", vecFileName);
	//m_RingCount->SetTexture("Number", vecFileName);

	//m_MinuteCount->SetColorKey(255, 0, 255);
	//m_SecondCount->SetColorKey(255, 0, 255);
	//m_RingCount->SetColorKey(255, 0, 255);


	//m_MinuteCount->SetSize(8.f, 16.f);
	//m_MinuteCount->SetPos(100.f, 55.f);

	//m_SecondCount->SetSize(8.f, 16.f);
	//m_SecondCount->SetPos(120.f, 55.f);

	//m_RingCount->SetSize(8.f, 16.f);
	//m_RingCount->SetPos(120.f, 75.f);

	return true;
}

void CClearBoard::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	
	//m_MinuteCount->SetNumber(1);
	//m_SecondCount->SetNumber(1);

	//m_RingCount->SetNumber(m_Ring);


}

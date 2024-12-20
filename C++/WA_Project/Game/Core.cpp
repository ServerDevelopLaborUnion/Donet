#include "pch.h"
#include "Core.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "NetworkManager.h"

bool Core::Init(HWND _hwnd, std::wstring& message)
{
	// 변수 초기화
	hwnd = _hwnd;
	hdc = ::GetDC(hwnd);
	hbackdc = 0;
	hbackbit = 0;

	// 더블 버퍼링
	// 1. 생성(세팅)
	hbackbit = ::CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	hbackdc = ::CreateCompatibleDC(hdc);

	// 2. 연결
	::SelectObject(hbackdc, hbackbit);

	// utility setting
	CreateGDI();

	// Set Server Connection
	NetworkManager* network = Single(NetworkManager);
	if (!network->Initialize()) {
		message = L"Network Initialize Failed...";
		return false;
	}
	if (!network->Connect()) {
		message = L"Connecting Failed...";
		return false;
	}

	// Wait Auth
	//while (!network->GetSession()->GetAuth());

	// === Manager Init === 
	Single(TimeManager)->Init();
	Single(InputManager)->Init();
	Single(ResourceManager)->Init();
	Single(SceneManager)->Init();

	return true;
}
void Core::CleanUp()
{
	// 생성한순서 반대로 삭제
	::DeleteDC(hbackdc);	//createdc한거
	::DeleteObject(hbackbit); // createbitmap 한거
	::ReleaseDC(hwnd, hdc);
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(colorPens[i]);
	}
	for (int i = 1; i < (UINT)BRUSH_TYPE::END; ++i)
	{
		// Hollow 제외하고
		DeleteObject(colorBrushs[i]);
	}

	Single(ResourceManager)->Release();
	Single(SceneManager)->Release();
	Single(NetworkManager)->Close();
}

bool Core::GameLoop()
{
	MainUpdate();
	MainRender();
	Single(EventManager)->Update();
	return Single(NetworkManager)->GetConnected();
}

void Core::MainUpdate()
{
	// === Manager Update === 
	Single(TimeManager)->Update();
	Single(InputManager)->Update();
	Single(SceneManager)->Update();
	Single(CollisionManager)->Update();
}

void Core::MainRender()
{
	// 1. clear
	::PatBlt(hbackdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACKNESS);
	// 2. Render
	Single(SceneManager)->Render(hbackdc);
	// 3. display
	::BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		hbackdc, 0, 0, SRCCOPY);

	//	::TransparentBlt();
	   //::StretchBlt();
	   //::PlgBlt();
	   //::AlphaBlend();
}

void Core::CreateGDI()
{
	// HOLLOW
	colorBrushs[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	colorBrushs[(UINT)BRUSH_TYPE::RED] = (HBRUSH)CreateSolidBrush(RGB(255, 167, 167));
	colorBrushs[(UINT)BRUSH_TYPE::GREEN] = (HBRUSH)CreateSolidBrush(RGB(134, 229, 134));
	colorBrushs[(UINT)BRUSH_TYPE::BLUE] = (HBRUSH)CreateSolidBrush(RGB(103, 153, 255));
	colorBrushs[(UINT)BRUSH_TYPE::YELLOW] = (HBRUSH)CreateSolidBrush(RGB(255, 187, 0));

	//RED GREEN BLUE PEN
	colorPens[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	colorPens[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	colorPens[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	colorPens[(UINT)PEN_TYPE::YELLOW] = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	colorPens[(UINT)PEN_TYPE::HOLLOW] = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
}

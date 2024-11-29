#pragma once

#include "Define.h"

class Core
{
	DECLARE_SINGLE(Core);
public:
	bool Init(HWND hwnd, std::wstring& message);
	bool GameLoop();
	void CleanUp();
private:
	void MainUpdate();
	void MainRender();
	void CreateGDI();
public:
	const HWND& GetHwnd() const { return hwnd; }
	// �̸� �ٲٱ�
	const HDC& GetMainDC() const { return hdc; }
	const HBRUSH& GetBrush(BRUSH_TYPE eType)
	{
		return colorBrushs[(UINT)eType];
	}
	const HPEN& GetPen(PEN_TYPE eType)
	{
		return colorPens[(UINT)eType];
	}

private:
	HBRUSH colorBrushs[(UINT)BRUSH_TYPE::END] = {};
	HPEN colorPens[(UINT)PEN_TYPE::END] = {};

	HWND hwnd;
	HDC  hdc; // Main DC
	HDC  hbackdc; // ����� DC
	HBITMAP hbackbit; // ������� bitmap
};

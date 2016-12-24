// ServerDisplayer.cpp: implementation of the CServerDisplayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ServerDisplayer.h"
#include "Log.h"

CServerDisplayer gServerDisplayer;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CServerDisplayer::CServerDisplayer() // OK
{
	for(int n=0;n < MAX_LOG_TEXT_LINE;n++)
	{
		memset(&this->m_log[n],0,sizeof(this->m_log[n]));
	}

	//this->m_font = CreateFont(50,0,0,0,FW_THIN,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Times");
	this->m_font = CreateFont(86, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE, 
		//ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_STROKE_PRECIS, CLEARTYPE_QUALITY,
		//DEFAULT_PITCH|FF_DONTCARE, "Times");
		FF_MODERN | FIXED_PITCH, "Tahoma");

	this->m_brush[0] = CreateSolidBrush(RGB(76,212,176));
	strcpy_s(this->m_DisplayerText[0],"-ConnectServers-");
}

CServerDisplayer::~CServerDisplayer() // OK
{
	DeleteObject(this->m_font);
	DeleteObject(this->m_brush[0]);
}

void CServerDisplayer::Init(HWND hWnd) // OK
{
	this->m_hwnd = hWnd;
}

void CServerDisplayer::Run() // OK
{
	this->PaintAllInfo();
}

void CServerDisplayer::PaintAllInfo() // OK
{
	RECT rect;

	GetClientRect(this->m_hwnd,&rect);

	rect.top = 0;
	rect.bottom = 80;

	HDC hdc = GetDC(this->m_hwnd);

	int OldBkMode = SetBkMode(hdc,TRANSPARENT);

	HFONT OldFont = (HFONT)SelectObject(hdc,this->m_font);

	SetTextColor(hdc,RGB(250,250,250));
	FillRect(hdc,&rect,this->m_brush[0]);
	TextOut(hdc,113,1,this->m_DisplayerText[0],strlen(this->m_DisplayerText[0]));

	SelectObject(hdc,OldFont);
	SetBkMode(hdc,OldBkMode);
	ReleaseDC(this->m_hwnd,hdc);
}

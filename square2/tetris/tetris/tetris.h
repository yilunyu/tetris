// tetris.h : main header file for the tetris application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CtetrisApp:
// See tetris.cpp for the implementation of this class
//

class CtetrisApp : public CWinApp
{
public:
	CtetrisApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CtetrisApp theApp;
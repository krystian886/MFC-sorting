
// SortingComparison.h : main header file for the SortingComparison application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSortingComparisonApp:
// See SortingComparison.cpp for the implementation of this class
//

class CSortingComparisonApp : public CWinApp
{
public:
	CSortingComparisonApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSortingComparisonApp theApp;

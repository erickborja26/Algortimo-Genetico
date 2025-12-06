// LisACa.h : main header file for the LISACA application
//

#if !defined(AFX_LISACA_H__F47B7B6C_B749_4DEA_B024_D1ABDC978AC6__INCLUDED_)
#define AFX_LISACA_H__F47B7B6C_B749_4DEA_B024_D1ABDC978AC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLisACaApp:
// See LisACa.cpp for the implementation of this class
//

class CLisACaApp : public CWinApp
{
public:
	CLisACaApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLisACaApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CLisACaApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISACA_H__F47B7B6C_B749_4DEA_B024_D1ABDC978AC6__INCLUDED_)

// YaMaXun.h : main header file for the YAMAXUN application
//

#if !defined(AFX_YAMAXUN_H__49D4543F_F64D_4048_9B4C_F09B5C3531C0__INCLUDED_)
#define AFX_YAMAXUN_H__49D4543F_F64D_4048_9B4C_F09B5C3531C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CYaMaXunApp:
// See YaMaXun.cpp for the implementation of this class
//

class CYaMaXunApp : public CWinApp
{
public:
	CYaMaXunApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYaMaXunApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CYaMaXunApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YAMAXUN_H__49D4543F_F64D_4048_9B4C_F09B5C3531C0__INCLUDED_)

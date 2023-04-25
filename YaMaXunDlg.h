// YaMaXunDlg.h : header file
//
#include <string>
#include <iostream>
using namespace std;
#if !defined(AFX_YAMAXUNDLG_H__B3AAFD53_67E8_472A_B064_AA439833187C__INCLUDED_)
#define AFX_YAMAXUNDLG_H__B3AAFD53_67E8_472A_B064_AA439833187C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CYaMaXunDlg dialog

struct Hebe
{
	int chess_x;
	int chess_y;
	int bar_x;
	int bar_y;
	int x;
	int y;
	int score;
    int timecount;
	int node;
};
struct Move
{
	int x;
	int y;
	int lx;
	int ly;
	int barx;
	int bary;
};
/*
struct NodeOfMove
{
	Move result;
	NodeOfMove *Next;
};
struct NodeOfData
{
	int Data[10][10];
	int Dcount;
	NodeOfMove *Move;
	NodeOfData *Next;
};
struct NodeOfBar
{
	int count;
	NodeOfData *Data;
	NodeOfBar *Next;
};
*/
struct NodeOfSave
{
	int count;
	int Dcount;
	int Mcount;
	int Data[10][10];
	Move result;	
	NodeOfSave *Next;
	//	int count;
	//int Dcount;
//	int Mcount;
//	int Data[10][10];
//	Move result;
//	SaveNode *Next;
};

class CYaMaXunDlg : public CDialog
{
// Construction
public:
	string transpos(string s);
	CYaMaXunDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CYaMaXunDlg)
	enum { IDD = IDD_YAMAXUN_DIALOG };
	CListBox	m_action;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYaMaXunDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	void Show(CPaintDC * dc);
	int Broad[10][10];//0-Nothing,1-have a bar,2-have a chessman of zheng,3-have achessman of fan
	void Play(CPoint p);
	int Judge(int x,int y);
	int Putbar(int x,int y);
	int Move(int x,int y);
	int Get(int x,int y);
	NodeOfSave * MyInit();
	int Is_Over();
	int lx,ly;
	int Is_Move;
	int times;
	int mode;
	static UINT MyThreadProc(LPVOID pParam);
	int Fan[4][2];
	int Zheng[4][2];

	Hebe Computer1();
    Hebe Computer();
//	Hebe GetTemp1(int x,int y);
//	Hebe GetTemp(int x,int y);
//	Hebe GetBar1(int x1,int y1,int x,int y);
//	Hebe GetBar(int x1,int y1,int x,int y);
//	int GetScore1(int x2,int y2,int x1,int y1,int x,int y);
//	int GetScore(int x2,int y2,int x1,int y1,int x,int y);
	int Is_OK(int x1,int y1,int x2,int y2,int tep[10][10] );

//    int*getnewscore(int x,int y,int temp[][10],int *score);

	// Generated message map functions
	//{{AFX_MSG(CYaMaXunDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRestart();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnButton1();
	afx_msg void OnButtonAcc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YAMAXUNDLG_H__B3AAFD53_67E8_472A_B064_AA439833187C__INCLUDED_)

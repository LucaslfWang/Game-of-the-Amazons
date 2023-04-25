// YaMaXunDlg.cpp : implementation file
//

#include "stdafx.h"
#include "YaMaXun.h"
#include "YaMaXunDlg.h"
#include "Searchengine.h"
#include <map>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
double B;
double WS;
double TIME=0;
int c;
int status;
extern int first;
//FILE *p=fopen("qc_test.txt","w");
NodeOfSave *Head;
mov ss[2];
map<string, mov> l;
extern int flag;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
														//}}AFX_VIRTUAL

														// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYaMaXunDlg dialog

CYaMaXunDlg::CYaMaXunDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CYaMaXunDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CYaMaXunDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CYaMaXunDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CYaMaXunDlg)
	DDX_Control(pDX, IDC_LIST, m_action);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CYaMaXunDlg, CDialog)
	//{{AFX_MSG_MAP(CYaMaXunDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_RESTART, OnRestart)
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON_ACC, OnButtonAcc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYaMaXunDlg message handlers

BOOL CYaMaXunDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	string stringpo;
	short tlx, tly, tx, ty, tbarx, tbary;
	int m = MessageBox("选择先手？是=人先手，否=电脑先手", "选择模式", 4);
	if (m == 6)
	{
		mode = 1;
		status = 0;
		mov tt;
		first = 1;
		//人机，人先手
		ifstream icin;
		icin.open("playerfirst.txt");
		while (!icin.eof())
		{
			icin >> stringpo >> tlx >> tly >> tx >> ty >> tbarx >> tbary;
			tt.lx = (BYTE)tlx;
			tt.ly = (BYTE)tly;
			tt.x = (BYTE)tx;
			tt.y = (BYTE)ty;
			tt.barx = (BYTE)tbarx;
			tt.bary = (BYTE)tbary;
			l.insert(pair<string, mov>(stringpo, tt));
			tt.lx = 11 - tt.lx;
			tt.x = 11 - tt.x;
			tt.barx = 11 - tt.barx;
			l.insert(pair<string, mov>(transpos(stringpo), tt));
		}
		icin.close();

	}
	else
	{
		mode = 2;
		status = 2;
		mov tt;
		first = 0;

		/*tt.lx=1;tt.ly=7;tt.x=4;tt.y=7;tt.barx=5;tt.bary=8;
		l.insert(pair<string,mov>("0000003000000000000000000020003000000003000000001001000000002000000002000300000000000000000002000000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000003000000000000000000020003000000003000000001001000000002000000002000300000000000000000002000000"),tt));

		tt.lx=4;tt.ly=7;tt.x=4;tt.y=5;tt.barx=8;tt.bary=1;
		l.insert(pair<string,mov>("0000003000000000000000000020003000003000000000001001000000000002000002000310000000000000000002001000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000003000000000000000000020003000003000000000001001000000000002000002000310000000000000000002001000"),tt));

		tt.lx=4;tt.ly=5;tt.x=3;tt.y=4;tt.barx=6;tt.bary=4;
		l.insert(pair<string,mov>("0000000100000000000000003020003000003000000210001001000000000000000002000310000000000000000002001000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000100000000000000003020003000003000000210001001000000000000000002000310000000000000000002001000"),tt));

		tt.lx=10;tt.ly=7;tt.x=7;tt.y=7;tt.barx=7;tt.bary=9;
		l.insert(pair<string,mov>("0000000100000000000000003020003020013000000010001001000000000000000002000010000000013000000002001000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000100000000000000003020003020013000000010001001000000000000000002000010000000013000000002001000"),tt));

		tt.lx=7;tt.ly=3;tt.x=8;tt.y=3;tt.barx=7;tt.bary=3;
		l.insert(pair<string,mov>("0000000100000000000000003020003020013100000010001001000000000010003002000010000000210000000000001000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000100000000000000003020003020013100000010001001000000000010003002000010000000210000000000001000"),tt));

		tt.lx=10;tt.ly=7;tt.x=8;tt.y=7;tt.barx=8;tt.bary=5;
		l.insert(pair<string,mov>("0000000100000000000000000012003023013100000010001001000000000010003002000110000000210000000000001000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000100000000000000000012003023013100000010001001000000000010003002000110000000210000000000001000"),tt));

		tt.lx=10;tt.ly=7;tt.x=8;tt.y=7;tt.barx=8;tt.bary=8;
		l.insert(pair<string,mov>("0000000100000000000000003012003020010100000011001001000000000010003002000010000003210000000000001000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000100000000000000003012003020010100000011001001000000000010003002000010000003210000000000001000"),tt));

		tt.lx=8;tt.ly=3;tt.x=9;tt.y=4;tt.barx=8;tt.bary=5;
		l.insert(pair<string,mov>("0000000100000000000000003012003020010100000011001001000030000010010200000010010003210000000000001000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000100000000000000003012003020010100000011001001000030000010010200000010010003210000000000001000"),tt));

		tt.lx=7;tt.ly=3;tt.x=8;tt.y=3;tt.barx=8;tt.bary=5;
		l.insert(pair<string,mov>("0000000100000000000000003020000020013000000010001001300000000000002000000010000000113010000002001000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000100000000000000003020000020013000000010001001300000000000002000000010000000113010000002001000"),tt));

		tt.lx=4;tt.ly=10;tt.x=6;tt.y=10;tt.barx=6;tt.bary=5;
		l.insert(pair<string,mov>("0000000100000000000000003002000020013000000010011001000000000000002000300010000000113010000012001000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000100000000000000003002000020013000000010011001000000000000002000300010000000113010000012001000"),tt));

		tt.lx=7;tt.ly=7;tt.x=7;tt.y=8;tt.barx=6;tt.bary=8;
		l.insert(pair<string,mov>("0000000100000000000000003020003020013100000010001001000000000010003002000010000000210000000000001000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000100000000000000003020003020013100000010001001000000000010003002000010000000210000000000001000"),tt));

		tt.lx=1;tt.ly=7;tt.x=4;tt.y=4;tt.barx=9;tt.bary=4;
		l.insert(pair<string,mov>("0000003000000000000000000020003000000003000000001000000000002000000002000300000100000000000002000000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000003000000000000000000020003000000003000000001000000000002000000002000300000100000000000002000000"),tt));

		tt.lx=4;tt.ly=10;tt.x=4;tt.y=9;tt.barx=1;tt.bary=6;
		l.insert(pair<string,mov>("0000003000000000030000000020003002000010000000001000000000000000000102000300000100000000000002000000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000003000000000030000000020003002000010000000001000000000000000000102000300000100000000000002000000"),tt));

		tt.lx=4;tt.ly=4;tt.x=3;tt.y=5;tt.barx=6;tt.bary=8;
		l.insert(pair<string,mov>("0000003000000000030000100020000032000010000000001010000000000000000102000300000100020000000000000000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000003000000000030000100020000032000010000000001010000000000000000102000300000100020000000000000000"),tt));

		tt.lx=7;tt.ly=3;tt.x=8;tt.y=3;tt.barx=4;tt.bary=7;
		l.insert(pair<string,mov>("0000000000000001030000103020000030000010002000001010000000000000000102000301000100020000000000000000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000000000001030000103020000030000010002000001010000000000000000102000301000100020000000000000000"),tt));

		tt.lx=10;tt.ly=7;tt.x=9;tt.y=8;tt.barx=7;tt.bary=10;
		l.insert(pair<string,mov>("0000000000000001030000100002000030000010002000001010000000000001000132000301000100020010000000000000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000000000001030000100002000030000010002000001010000000000001000132000301000100020010000000000000"),tt));

		tt.lx=3;tt.ly=5;tt.x=2;tt.y=4;tt.barx=2;tt.bary=8;
		l.insert(pair<string,mov>("0000000000000001030000100002000030000110002000001010000000000001000130000001002100320010000000001000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000000000001030000100002000030000110002000001010000000000001000130000001002100320010000000001000"),tt));

		tt.lx=8;tt.ly=3;tt.x=7;tt.y=4;tt.barx=5;tt.bary=6;
		l.insert(pair<string,mov>("0000000000000001030000100102000230000110000000001010000000300001000100010001002100320010000000001000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000000000001030000100102000230000110000000001010000000300001000100010001002100320010000000001000"),tt));

		tt.lx=7;tt.ly=4;tt.x=4;tt.y=4;tt.barx=8;tt.bary=8;
		l.insert(pair<string,mov>("0000000000000001000000100113000230002110000000001010001000300001000100010001002100320010000000001000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000000000001000000100113000230002110000000001010001000300001000100010001002100320010000000001000"),tt));

		tt.lx=9;tt.ly=8;tt.x=10;tt.y=7;tt.barx=9;tt.bary=6;
		l.insert(pair<string,mov>("0000000000000001000000100113000232000110000000001010001003000001000110010001012100320010000000001000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000000000001000000100113000232000110000000001010001003000001000110010001012100320010000000001000"),tt));

		tt.lx=7;tt.ly=7;tt.x=7;tt.y=8;tt.barx=6;tt.bary=8;
		l.insert(pair<string,mov>("0000000100000000000000003002000020013000000011011001000000000000002000300010000000111310000010021000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000100000000000000003002000020013000000011011001000000000000002000300010000000111310000010021000"),tt));

		tt.lx=6;tt.ly=10;tt.x=5;tt.y=10;tt.barx=6;tt.bary=10;
		l.insert(pair<string,mov>("0000000100000000000000003002000020010000000011011001000000000010003000300011200000111310000010021000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000100000000000000003002000020010000000011011001000000000010003000300011200000111310000010021000"),tt));

		tt.lx=7;tt.ly=8;tt.x=8;tt.y=7;tt.barx=7;tt.bary=8;
		l.insert(pair<string,mov>("0000000100000000000000003002000020010000010311011001000000000010003000000011200000111310000010211000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000100000000000000003002000020010000010311011001000000000010003000000011200000111310000010211000"),tt));

		tt.lx=10;tt.ly=7;tt.x=9;tt.y=6;tt.barx=6;tt.bary=6;
		l.insert(pair<string,mov>("0000000100000000000000000020003013003000000200001001000000000000000002000310000000000000000002001000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>("0000000100000000000000000020003013003000000200001001000000000000000002000310000000000000000002001000",tt));

		tt.lx=4;tt.ly=10;tt.x=3;tt.y=9;tt.barx=5;tt.bary=7;
		l.insert(pair<string,mov>("0000000100000000000000000020003013003000000200001001000100200000000000000010000000003000000002101000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000100000000000000000020003013003000000200001001000100200000000000000010000000003000000002101000"),tt));

		tt.lx=9;tt.ly=6;tt.x=8;tt.y=7;tt.barx=8;tt.bary=4;
		l.insert(pair<string,mov>("0000000100000000000000000020003013003000000200001001000100200000100000000010000000210003000000101000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000100000000000000000020003013003000000200001001000100200000100000000010000000210003000000101000"),tt));

		tt.lx=3;tt.ly=9;tt.x=2;tt.y=8;tt.barx=2;tt.bary=9;
		l.insert(pair<string,mov>("0000000100000000000000000020000013003100100200001001000100000000100200300010000000210003000000101000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000100000000000000000020000013003100100200001001000100000000100200300010000000210003000000101000"),tt));

		tt.lx=2;tt.ly=8;tt.x=3;tt.y=7;tt.barx=2;tt.bary=7;
		l.insert(pair<string,mov>("0000000100000000000000000020000013003100100200001001300100000000100200021010000001010003000000101000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000100000000000000000020000013003100100200001001300100000000100200021010000001010003000000101000"),tt));

		tt.lx=4;tt.ly=5;tt.x=4;tt.y=3;tt.barx=5;tt.bary=2;
		l.insert(pair<string,mov>("0000000100000300000000000020000010003100100200001001300101000120100200001010000001010003000000101000",tt));
		tt.lx=11-tt.lx;
		tt.x=11-tt.x;
		tt.barx=11-tt.barx;
		l.insert(pair<string,mov>(transpos("0000000100000300000000000020000010003100100200001001300101000120100200001010000001010003000000101000"),tt));
		*///人机，电脑先手
		ifstream icin;
		icin.open("computerfirst.txt");
		while (!icin.eof())
		{
			icin >> stringpo >> tlx >> tly >> tx >> ty >> tbarx >> tbary;
			tt.lx = (BYTE)tlx;
			tt.ly = (BYTE)tly;
			tt.x = (BYTE)tx;
			tt.y = (BYTE)ty;
			tt.barx = (BYTE)tbarx;
			tt.bary = (BYTE)tbary;
			l.insert(pair<string, mov>(stringpo, tt));
			tt.lx = 11 - tt.lx;
			tt.x = 11 - tt.x;
			tt.barx = 11 - tt.barx;
			l.insert(pair<string, mov>(transpos(stringpo), tt));
		}
		icin.close();
	}
	FILE *fp;
	fp = fopen("test.txt", "a+");
	fprintf(fp, "开始：");
	if (first == 1)
	{
		fprintf(fp, "我方执黑\n");
	}
	else
	{
		fprintf(fp, "我方执白\n");
	}
	fclose(fp);

	FILE *fp2;
	fp2 = fopen("FinalQiPu.txt", "a+");
	fprintf(fp2, "\n#[AM][先手参赛队][后手参赛队][胜负关系][2018.8.x 14:00 合肥][比赛名称];");
	if (first == 1) //后手
	{
		fprintf(fp2, "知于行执黑后手\n");
		fprintf(fp2,"1  ");

	}
	else
	{
		fprintf(fp2, "知于行执白先手");
	}
	fclose(fp2);

	// TODO: Add extra initialization here
	for (int i = 0; i<10; i++)//棋盘初始化
		for (int j = 0; j<10; j++)
			if ((i == 3 && j == 0) || (i == 6 && j == 0) || (i == 0 && j == 3) || (i == 9 && j == 3))
				Broad[i][j] = 3;//  3;//  3;//   2;
			else if ((i == 0 && j == 6) || (i == 9 && j == 6) || (i == 3 && j == 9) || (i == 6 && j == 9))
				Broad[i][j] = 2;//  2;// 2;
			else
				Broad[i][j] = 0;
	lx = -1;
	ly = -1;
	times = 0;//主循环控制，就是控制谁走的参数
	Is_Move = 0;
	Head = MyInit();

	AfxBeginThread(MyThreadProc, this);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CYaMaXunDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CYaMaXunDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	Show(&dc);
}

void CYaMaXunDlg::Show(CPaintDC * dc) {
	CDC mdc_broad, mdc_zheng, mdc_fan, mdc_black;
	CBitmap bmp_broad, bmp_zheng, bmp_fan, bmp_black;
	CBitmap * ob_broad, *ob_zheng, *ob_fan, *ob_black;

	mdc_broad.CreateCompatibleDC(dc);
	mdc_zheng.CreateCompatibleDC(dc);
	mdc_fan.CreateCompatibleDC(dc);
	mdc_black.CreateCompatibleDC(dc);

	bmp_broad.LoadBitmap(IDB_BROAD);
	bmp_zheng.LoadBitmap(IDB_ZHENG);
	bmp_fan.LoadBitmap(IDB_FAN);
	bmp_black.LoadBitmap(IDB_BLACK);


	ob_broad = mdc_broad.SelectObject(&bmp_broad);
	ob_zheng = mdc_zheng.SelectObject(&bmp_zheng);
	ob_fan = mdc_fan.SelectObject(&bmp_fan);
	ob_black = mdc_black.SelectObject(&bmp_black);


	///////////////////////////////////
	//绘制棋子
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			switch (Broad[i][j])
			{
			case 1:
				mdc_broad.BitBlt(i * 50, j * 50, 50, 50, &mdc_black, 0, 0, SRCCOPY);
				break;
			case 2:
				mdc_broad.BitBlt(i * 50, j * 50, 50, 50, &mdc_zheng, 0, 0, SRCCOPY);
				break;
			case 3:
				mdc_broad.BitBlt(i * 50, j * 50, 50, 50, &mdc_fan, 0, 0, SRCCOPY);
				break;
			default:
				break;
			}
		}
	}
	////////////////////////////////////
	//绘制落子标记
	if ((!(lx == -1 && ly == -1)) && Is_Move == 1)
	{
		for (int i = 0; i < 50; i++)
		{
			mdc_broad.SetPixel(lx * 50 + i, ly * 50 + 25, RGB(255, 0, 0));
			mdc_broad.SetPixel(lx * 50 + i, ly * 50 + 26, RGB(255, 0, 0));
		}
		for (int i = 0; i < 50; i++)
		{
			mdc_broad.SetPixel(lx * 50 + 25, ly * 50 + i, RGB(255, 0, 0));
			mdc_broad.SetPixel(lx * 50 + 26, ly * 50 + i, RGB(255, 0, 0));
		}
	}

	///////////////////////////////////
	//显示棋盘
	dc->BitBlt(5, 5, 510, 510, &mdc_broad, 0, 0, SRCCOPY);

	mdc_broad.SelectObject(ob_broad);
	mdc_zheng.SelectObject(ob_zheng);
	mdc_fan.SelectObject(ob_fan);
	mdc_black.SelectObject(ob_black);
}
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CYaMaXunDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

void CYaMaXunDlg::OnLButtonDown(UINT nFlags, CPoint point) //鼠标左键点击相应
{
	// TODO: Add your message handler code here and/or call default	
	if (status == 1 || status == 2) return;

	times++;
	Is_Move = 0;

	Play(point);
	CDialog::OnLButtonDown(nFlags, point);
}
void CYaMaXunDlg::Play(CPoint p)//判断鼠标点击是否在棋盘内，并将点击出的像素转化为相应的坐标值
{
	int x, y;
	x = (p.x - 5) / 50;
	y = (p.y - 5) / 50;
	if (p.x<5 || p.x>505 || p.y<5 || p.y>505)
		times--;
	else
		Judge(x, y);
}
//---------------------2018有所改动-----------------------------
int CYaMaXunDlg::Judge(int x, int y)//主循环控制部分
{
	CString info;
	char xx[3],  xxcout[3];
	char yy[3],  yycout[3];
	char lxx[3], lxxcout[3];
	char lyy[3], lyycout[3];

	itoa(x + 1, xx, 10);//这是将x+1转化成10进制的字符串，供棋谱显示的时候用，下面同理
	itoa(lx + 1, lxx, 10);
	itoa(y + 1, yy, 10);
	itoa(ly + 1, lyy, 10);
	
	//x轴规范
	{
		if (x == 0) sscanf("A", "%s", xxcout);
		else if (x == 1) sscanf("B", "%s", xxcout);
		else if (x == 2) sscanf("C", "%s", xxcout);
		else if (x == 3) sscanf("D", "%s", xxcout);
		else if (x == 4) sscanf("E", "%s", xxcout);
		else if (x == 5) sscanf("F", "%s", xxcout);
		else if (x == 6) sscanf("G", "%s", xxcout);
		else if (x == 7) sscanf("H", "%s", xxcout);
		else if (x == 8) sscanf("I", "%s", xxcout);
		else  sscanf("J", "%s", xxcout);

		if (lx == 0) sscanf("A", "%s", lxxcout);
		else if (lx == 1) sscanf("B", "%s", lxxcout);
		else if (lx == 2) sscanf("C", "%s", lxxcout);
		else if (lx == 3) sscanf("D", "%s", lxxcout);
		else if (lx == 4) sscanf("E", "%s", lxxcout);
		else if (lx == 5) sscanf("F", "%s", lxxcout);
		else if (lx == 6) sscanf("G", "%s", lxxcout);
		else if (lx == 7) sscanf("H", "%s", lxxcout);
		else if (lx == 8) sscanf("I", "%s", lxxcout);
		else  sscanf("J", "%s", lxxcout);
	}
	//y轴规范
	itoa(11 - (y + 1), yycout, 10);
	itoa(11 - (ly + 1), lyycout, 10);

	//创建规范棋谱并写入



//	------------------------------------------ 2018.7.12 sht-----------------------
	switch (Broad[x][y])
	{
	case 0://表示点击的地方是空地
		if (times % 3 == 0)//表示每第三次点击，也就是放置障碍物的那次点击，第一次是选择棋子，第二次是选择棋子要移动到的位子
		{
			info.Format("M:Put bar at (%s,%s)", xxcout, yycout);//棋谱显示
			
			FILE *fp;
			fp = fopen("test.txt", "a+");
			fprintf(fp, "%s %s\n", xx, yy);
			fclose(fp);
			
			//新增规范棋谱写入
			FILE *fp2;
			fp2 = fopen("FinalQiPu.txt", "a+");
			fprintf(fp2,"(%s%s)  ", xxcout, yycout);
			fclose(fp2);


			if (!Putbar(x, y))
			{
				times--;
				MessageBox("不符合设置障碍规则", "提示");
				return 0;
			}
			else
			{
				ss[0].barx = x; ss[0].bary = y;
				m_action.InsertString(m_action.GetCount(), info);
			}
		}
		else if (times % 3 == 2)
		{
			info.Format("M:Move (%s,%s) to (%s,%s)", lxxcout, lyycout, xxcout, yycout);

			FILE *fp;
			fp = fopen("test.txt", "a+");
			if (first == 1)
			{
				fprintf(fp, "W ");
			}
			else
			{
				fprintf(fp, "B ");
			}
			fprintf(fp, "%s %s %s %s ", lyy, lxx, yy, xx);
			fclose(fp);

			//2018new
			FILE *fp2;
			fp2 = fopen("FinalQiPu.txt", "a+");
			fprintf(fp2, "%s%s%s%s", lxxcout,lyycout,xxcout,yycout);
			fclose(fp2);
			


			if (!Move(x, y))
			{
				times--;
				MessageBox("不符合下子规则", "提示");
				return 0;
			}
			else
			{
				ss[0].x = x; ss[0].y = y;
				m_action.InsertString(m_action.GetCount(), info);
			}
		}
		else
		{
			times--;
			MessageBox("此处无棋子", "提示");
			return 0;
		}
		break;
	case 1://表示点击的地方是障碍物
		if (times % 3 == 0 || times % 3 == 2)
		{
			if (times % 3 == 0)
				MessageBox("不符合设置障碍规则", "提示");
			else
				MessageBox("不符合下子规则", "提示");
			times--;
			return 0;
		}
		else
		{
			times--;
			MessageBox("此处不是棋子", "提示");
			return 0;
		}
		break;
	case 2://表示点击的地方是正方棋子
		if (times % 3 == 0 || times % 3 == 2)
		{
			if (times % 3 == 0)
				MessageBox("不符合设置障碍规则", "提示");
			else
				MessageBox("不符合下子规则", "提示");
			times--;
			return 0;
		}
		else
		{
			if (times % 6>0 && times % 6<4)
			{
				info.Format("M:Get (%s,%s)", xxcout, yycout);
				m_action.InsertString(m_action.GetCount(), info);
				Get(x, y);
				ss[0].lx = x; ss[0].ly = y;
			}
			else
			{
				times--;
				MessageBox("反方行棋", "提示");
				return 0;
			}
		}
		break;
	case 3://表示点击的地方是反方棋子
		if (times % 3 == 0 || times % 3 == 2)
		{
			if (times % 3 == 0)
				MessageBox("不符合设置障碍规则", "提示");
			else
				MessageBox("不符合下子规则", "提示");
			times--;
			return 0;
		}
		else
		{
			if (times % 6>0 && times % 6<4)
			{
				times--;
				MessageBox("正方行棋", "提示");
				return 0;
			}
			else
			{
				info.Format("M:Get (%s,%s)", xxcout, yycout);
				m_action.InsertString(m_action.GetCount(), info);
				Get(x, y);
				ss[0].lx = x; ss[0].ly = y;
			}
		}
		break;
	}

	lx = x; ly = y;
	Invalidate(FALSE);//刷新棋盘
	int Result = Is_Over();
	if (Result != 0)
	{
		if (Result == 1)
		{
			if (mode == 0)
				MessageBox("反方胜，再来一局吧", "提示");
			else
				MessageBox("电脑胜，再来一局吧", "提示");

		}
		else
			MessageBox("正方胜，再来一局吧", "提示");
		int m = MessageBox("选择模式？是=人机，否=人人", "选择模式", 4);
		if (m == 6)
		{
			int m = MessageBox("选择先手？是=人先手，否=电脑先手", "选择模式", 4);
			if (m == 6)
			{
				mode = 1;
				status = 0;
				//人机，人先手

			}
			else
			{
				mode = 2;
				status = 2;
				//人机，电脑先手
			}

		}
		else
		{
			mode = 0;
			status = 0;
		}
		for (int i = 0; i<10; i++)//棋盘初始化
			for (int j = 0; j<10; j++)
				if ((i == 3 && j == 0) || (i == 6 && j == 0) || (i == 0 && j == 3) || (i == 9 && j == 3))
					Broad[i][j] = 3;//原程序为2
				else if ((i == 0 && j == 6) || (i == 9 && j == 6) || (i == 3 && j == 9) || (i == 6 && j == 9))
					Broad[i][j] = 2;//原程序为3
				else
					Broad[i][j] = 0;
		lx = -1;
		ly = -1;
		times = 0;
		Is_Move = 0;
		Invalidate(FALSE);
		for (int i = m_action.GetCount() - 1; i >= 0; i--)
			m_action.DeleteString(i);
	}
	if (times % 6 == 3 && mode == 1) status = 1;
	if (((times % 6 == 0) || (times == 0)) && mode == 2) status = 2;
	return 0;
}
int CYaMaXunDlg::Putbar(int x, int y)//判断障碍物放置是否符合规则的函数
{
	if (lx == x || ly == y || (ly - lx) == (y - x) || (x + y) == (lx + ly))//lx和ly是上次点击处的坐标，x和y是这次点击处的坐标
	{
		if (lx == x)
		{
			if (ly>y)
			{
				for (int i = y + 1; i<ly; i++)
					if (Broad[x][i] == 1 || Broad[x][i] == 2 || Broad[x][i] == 3)
						return 0;
			}
			else
			{
				for (int i = ly + 1; i<y; i++)
					if (Broad[x][i] == 1 || Broad[x][i] == 2 || Broad[x][i] == 3)
						return 0;
			}
		}
		if (ly == y)
		{
			if (lx>x)
			{
				for (int i = x + 1; i<lx; i++)
					if (Broad[i][y] == 1 || Broad[i][y] == 2 || Broad[i][y] == 3)
						return 0;
			}
			else
			{
				for (int i = lx + 1; i<x; i++)
					if (Broad[i][y] == 1 || Broad[i][y] == 2 || Broad[i][y] == 3)
						return 0;
			}
		}
		if ((ly - lx) == (y - x))
		{
			int k = y - x;
			if (ly>y)
			{
				for (int i = y + 1; i<ly; i++)
					if (Broad[i - k][i] == 1 || Broad[i - k][i] == 2 || Broad[i - k][i] == 3)
						return 0;
			}
			else
			{
				for (int i = ly + 1; i<y; i++)
					if (Broad[i - k][i] == 1 || Broad[i - k][i] == 2 || Broad[i - k][i] == 3)
						return 0;
			}
		}
		if ((ly + lx) == (y + x))
		{
			int k = y + x;
			if (ly>y)
			{
				for (int i = y + 1; i<ly; i++)
					if (Broad[k - i][i] == 1 || Broad[k - i][i] == 2 || Broad[k - i][i] == 3)
						return 0;
			}
			else
			{
				for (int i = ly + 1; i<y; i++)
					if (Broad[k - i][i] == 1 || Broad[k - i][i] == 2 || Broad[k - i][i] == 3)
						return 0;
			}
		}

		Broad[x][y] = 1;
		return 1;
	}
	return 0;
}
int CYaMaXunDlg::Move(int x, int y)//判断棋子移动是否符合规则
{
	if (lx == x || ly == y || (ly - lx) == (y - x) || (x + y) == (lx + ly))
	{
		if (lx == x)
		{
			if (ly>y)
			{
				for (int i = y + 1; i<ly; i++)
					if (Broad[x][i] == 1 || Broad[x][i] == 2 || Broad[x][i] == 3)
						return 0;
			}
			else
			{
				for (int i = ly + 1; i<y; i++)
					if (Broad[x][i] == 1 || Broad[x][i] == 2 || Broad[x][i] == 3)
						return 0;
			}
		}
		if (ly == y)
		{
			if (lx>x)
			{
				for (int i = x + 1; i<lx; i++)
					if (Broad[i][y] == 1 || Broad[i][y] == 2 || Broad[i][y] == 3)
						return 0;
			}
			else
			{
				for (int i = lx + 1; i<x; i++)
					if (Broad[i][y] == 1 || Broad[i][y] == 2 || Broad[i][y] == 3)
						return 0;
			}
		}
		if ((ly - lx) == (y - x))
		{
			int k = y - x;
			if (ly>y)
			{
				for (int i = y + 1; i<ly; i++)
					if (Broad[i - k][i] == 1 || Broad[i - k][i] == 2 || Broad[i - k][i] == 3)
						return 0;
			}
			else
			{
				for (int i = ly + 1; i<y; i++)
					if (Broad[i - k][i] == 1 || Broad[i - k][i] == 2 || Broad[i - k][i] == 3)
						return 0;
			}
		}
		if ((ly + lx) == (y + x))
		{
			int k = y + x;
			if (ly>y)
			{
				for (int i = y + 1; i<ly; i++)
					if (Broad[k - i][i] == 1 || Broad[k - i][i] == 2 || Broad[k - i][i] == 3)
						return 0;
			}
			else
			{
				for (int i = ly + 1; i<y; i++)
					if (Broad[k - i][i] == 1 || Broad[k - i][i] == 2 || Broad[k - i][i] == 3)
						return 0;
			}
		}

		Broad[x][y] = Broad[lx][ly];
		Broad[lx][ly] = 0;
		return 1;
	}
	return 0;
}
int CYaMaXunDlg::Get(int x, int y)
{
	Is_Move = 1;
	return 0;
}

void CYaMaXunDlg::OnRestart() //这是程序窗口上重新开始按钮的函数，至于那个按钮怎么加的，我没有问我同学
{
	/*	for(int i=0;i<10;i++)
	for(int j=0;j<10;j++)
	if((i==3&&j==0)||(i==6&&j==0)||(i==0&&j==3)||(i==9&&j==3))
	Broad[i][j]=2;
	else if((i==0&&j==6)||(i==9&&j==6)||(i==3&&j==9)||(i==6&&j==9))
	Broad[i][j]=3;
	else
	Broad[i][j]=0;
	lx=-1;
	ly=-1;
	times=0;
	Is_Move=0;
	Invalidate(FALSE);
	for(int i=m_action.GetCount()-1;i>=0;i--)
	m_action.DeleteString(i);
	int m=MessageBox("选择模式？是=人机，否=人人","选择模式",4);
	if(m==6)
	{
	int m=MessageBox("选择先手？是=人先手，否=电脑先手","选择模式",4);
	if(m==6)
	{
	mode=1;
	status=0;
	//人机，人先手

	}
	else
	{
	mode=2;
	status=2;
	//人机，电脑先手
	}

	}
	else
	{
	mode=0;
	status=0;
	}*/
	// TODO: Add your control notification handler code here	
}
int CYaMaXunDlg::Is_Over()//判断胜负的函数
{
	int count = 0;
	for (int i = 0; i<10; i++)//对正方棋子所处情况的检查
	{
		for (int j = 0; j<10; j++)
		{
			if (Broad[i][j] == 2)
			{
				if (
					((i - 1<0 || j - 1<0) || (i - 1 >= 0 && j - 1 >= 0 && (Broad[i - 1][j - 1] == 1 || Broad[i - 1][j - 1] == 2 || Broad[i - 1][j - 1] == 3)))
					&& ((j - 1<0) || (j - 1 >= 0 && (Broad[i][j - 1] == 1 || Broad[i][j - 1] == 2 || Broad[i][j - 1] == 3)))
					&& ((j - 1<0 || i + 1>9) || (j - 1 >= 0 && i + 1<10 && (Broad[i + 1][j - 1] == 1 || Broad[i + 1][j - 1] == 2 || Broad[i + 1][j - 1] == 3)))
					&& ((i + 1>9) || (i + 1<10 && (Broad[i + 1][j] == 1 || Broad[i + 1][j] == 2 || Broad[i + 1][j] == 3)))
					&& ((j + 1>9 || i + 1>9) || (j + 1<10 && i + 1<10 && (Broad[i + 1][j + 1] == 1 || Broad[i + 1][j + 1] == 2 || Broad[i + 1][j + 1] == 3)))
					&& ((j + 1>9) || (j + 1<10 && (Broad[i][j + 1] == 1 || Broad[i][j + 1] == 2 || Broad[i][j + 1] == 3)))
					&& ((j + 1>9 || i - 1<0) || (j + 1<10 && i - 1 >= 0 && (Broad[i - 1][j + 1] == 1 || Broad[i - 1][j + 1] == 2 || Broad[i - 1][j + 1] == 3)))
					&& ((i - 1<0) || (i - 1 >= 0 && (Broad[i - 1][j] == 1 || Broad[i - 1][j] == 2 || Broad[i - 1][j] == 3)))
					)
					count++;
			}
		}
	}
	if (count == 4) return 1;
	count = 0;
	for (int i = 0; i<10; i++)//对反方棋子所处情况的检查
	{
		for (int j = 0; j<10; j++)
		{
			if (Broad[i][j] == 3)
			{
				if (
					((i - 1<0 || j - 1<0) || (i - 1 >= 0 && j - 1 >= 0 && (Broad[i - 1][j - 1] == 1 || Broad[i - 1][j - 1] == 2 || Broad[i - 1][j - 1] == 3)))
					&& ((j - 1<0) || (j - 1 >= 0 && (Broad[i][j - 1] == 1 || Broad[i][j - 1] == 2 || Broad[i][j - 1] == 3)))
					&& ((j - 1<0 || i + 1>9) || (j - 1 >= 0 && i + 1<10 && (Broad[i + 1][j - 1] == 1 || Broad[i + 1][j - 1] == 2 || Broad[i + 1][j - 1] == 3)))
					&& ((i + 1>9) || (i + 1<10 && (Broad[i + 1][j] == 1 || Broad[i + 1][j] == 2 || Broad[i + 1][j] == 3)))
					&& ((j + 1>9 || i + 1>9) || (j + 1<10 && i + 1<10 && (Broad[i + 1][j + 1] == 1 || Broad[i + 1][j + 1] == 2 || Broad[i + 1][j + 1] == 3)))
					&& ((j + 1>9) || (j + 1<10 && (Broad[i][j + 1] == 1 || Broad[i][j + 1] == 2 || Broad[i][j + 1] == 3)))
					&& ((j + 1>9 || i - 1<0) || (j + 1<10 && i - 1 >= 0 && (Broad[i - 1][j + 1] == 1 || Broad[i - 1][j + 1] == 2 || Broad[i - 1][j + 1] == 3)))
					&& ((i - 1<0) || (i - 1 >= 0 && (Broad[i - 1][j] == 1 || Broad[i - 1][j] == 2 || Broad[i - 1][j] == 3)))
					)
					count++;
			}
		}
	}
	if (count == 4) return 2;
	return 0;
}

void CYaMaXunDlg::OnRButtonDown(UINT nFlags, CPoint point) //鼠标右键取消棋子选择功能的实现，本来想实现悔棋的，但我同学说麻烦
{
	// TODO: Add your message handler code here and/or call default
	int x, y;
	//char xx[2];
	//char yy[2];
	x = point.x / 50;
	y = point.y / 50;
	//itoa(x+1,xx,10);
	//itoa(y+1,yy,10);
	//CString info;
	if (x == lx&&y == ly && (Broad[x][y] == 2 || Broad[x][y] == 3) && times % 3 == 1)
	{
		times--;
		Is_Move = 0;
		//info.Format("cancle to get (%s,%s)",xx,yy);
		//m_action.InsertString(m_action.GetCount(),info);
		m_action.DeleteString(m_action.GetCount() - 1);
		Invalidate(FALSE);
	}

	CDialog::OnRButtonDown(nFlags, point);
}

UINT CYaMaXunDlg::MyThreadProc(LPVOID pParam)//这涉及到线程的那块，我也不理解，这函数的作用是将电脑选择的招数显示出来
{
	CYaMaXunDlg *me = (CYaMaXunDlg *)pParam;
	Hebe result;
	
	char num5[10];
	char num6[10];
	char num7[10];
	char num8[10];
	CString Info;

	char xxcout[3]; //移动后的x
	char yycout[3]; //移动后的y
	char lxxcout[3];//移动前的x
	char lyycout[3];//移动前的y
	char barxcout[3];//障碍x
	char barycout[3];//障碍y

	static int count = 0;  //写棋谱记录多少回合用
	
	while (1)
	{
		Sleep(200);
		
		if (status == 1)  //电脑执棋就是黑色，就是后手
		{
			count++;
			for (int i = 0; i<10; i++)
				for (int j = 0; j<10; j++)
					if (me->Broad[i][j] == 3)
						me->Broad[i][j] = 2;
					else if (me->Broad[i][j] == 2)
						me->Broad[i][j] = 3;
			result = me->Computer1();
			//-----------结果修改完成----------该备注新加
			//棋谱规范 2018new
			//x轴规范
			{
				if (result.chess_x == 0) sscanf("A", "%s", xxcout);
				else if (result.chess_x == 1) sscanf("B", "%s", xxcout);
				else if (result.chess_x == 2) sscanf("C", "%s", xxcout);
				else if (result.chess_x == 3) sscanf("D", "%s", xxcout);
				else if (result.chess_x == 4) sscanf("E", "%s", xxcout);
				else if (result.chess_x == 5) sscanf("F", "%s", xxcout);
				else if (result.chess_x == 6) sscanf("G", "%s", xxcout);
				else if (result.chess_x == 7) sscanf("H", "%s", xxcout);
				else if (result.chess_x == 8) sscanf("I", "%s", xxcout);
				else  sscanf("J", "%s", xxcout);

				if (result.x == 0) sscanf("A", "%s", lxxcout);
				else if (result.x == 1) sscanf("B", "%s", lxxcout);
				else if (result.x == 2) sscanf("C", "%s", lxxcout);
				else if (result.x == 3) sscanf("D", "%s", lxxcout);
				else if (result.x == 4) sscanf("E", "%s", lxxcout);
				else if (result.x == 5) sscanf("F", "%s", lxxcout);
				else if (result.x == 6) sscanf("G", "%s", lxxcout);
				else if (result.x == 7) sscanf("H", "%s", lxxcout);
				else if (result.x == 8) sscanf("I", "%s", lxxcout);
				else  sscanf("J", "%s", lxxcout);

				if (result.bar_x == 0) sscanf("A", "%s", barxcout);
				else if (result.bar_x == 1) sscanf("B", "%s", barxcout);
				else if (result.bar_x == 2) sscanf("C", "%s", barxcout);
				else if (result.bar_x == 3) sscanf("D", "%s", barxcout);
				else if (result.bar_x == 4) sscanf("E", "%s", barxcout);
				else if (result.bar_x == 5) sscanf("F", "%s", barxcout);
				else if (result.bar_x == 6) sscanf("G", "%s", barxcout);
				else if (result.bar_x == 7) sscanf("H", "%s", barxcout);
				else if (result.bar_x == 8) sscanf("I", "%s", barxcout);
				else  sscanf("J", "%s", barxcout);
			}
			//y轴规范
			itoa(11 - (result.chess_y + 1), yycout, 10);
			itoa(11 - (result.y + 1), lyycout, 10);
			itoa(11 - (result.bar_y + 1), barycout, 10);


			FILE *fp;
			fp = fopen("test.txt", "a+");
			fprintf(fp, "B ");
			fprintf(fp, "%d %d %d %d %d %d\n", result.y + 1, result.x + 1, result.chess_y + 1, result.chess_x + 1, result.bar_y + 1, result.bar_x + 1);
			fclose(fp);

			//2018new 电脑后手执行完要换行
			FILE *fp2;
			fp2 = fopen("FinalQiPu.txt", "a+");
			fprintf(fp2, "%s%s%s%s(%s%s)\n%d  ",lxxcout, lyycout, xxcout, yycout,barxcout,barycout,count+1);  //2018new 这里最后count+1 别问为什么
			fclose(fp2);

			for (int i = 0; i<10; i++)
				for (int j = 0; j<10; j++)
					if (me->Broad[i][j] == 3)
						me->Broad[i][j] = 2;
					else if (me->Broad[i][j] == 2)
						me->Broad[i][j] = 3;
		
			Info.Format("***********************");  //new
			me->m_action.InsertString(me->m_action.GetCount(), Info);
		
			Info.Format("C:Get (%s,%s)", lxxcout,lyycout);   //new
			me->m_action.InsertString(me->m_action.GetCount(), Info);
			
			Info.Format("C:to(%s,%s)", xxcout, yycout);     //new
			me->m_action.InsertString(me->m_action.GetCount(), Info);

			Info.Format("C:Put bar at (%s,%s)", barxcout, barycout); //new
			me->m_action.InsertString(me->m_action.GetCount(), Info);

			itoa(result.score, num5, 10);
			itoa(result.timecount, num6, 10);
			Info.Format("评价数:%s", num5);
			me->m_action.InsertString(me->m_action.GetCount(), Info);
			Info.Format("时间:%s", num6);
			me->m_action.InsertString(me->m_action.GetCount(), Info);
			Info.Format("得分:%.5f", B);
			me->m_action.InsertString(me->m_action.GetCount(), Info);
			itoa(c, num8, 10);
			Info.Format("节点:%s", num8);
			me->m_action.InsertString(me->m_action.GetCount(), Info);
			Info.Format("W:%.2f", WS);
			me->m_action.InsertString(me->m_action.GetCount(), Info);
			TIME += result.timecount ;
			Info.Format("TIME:%.0f", TIME);
			me->m_action.InsertString(me->m_action.GetCount(), Info);
			Info.Format("***********************");  //new
			me->m_action.InsertString(me->m_action.GetCount(), Info);

			me->Broad[result.chess_x][result.chess_y] = 3;
			me->Broad[result.x][result.y] = 0;
			me->Broad[result.bar_x][result.bar_y] = 1;
			me->Invalidate(FALSE);
			status = 0;
			me->times = me->times + 3;
			int Re = me->Is_Over();
			if (Re != 0)
			{
				if (Re == 1)
					me->MessageBox("电脑胜，再来一局吧", "提示");
				else
					me->MessageBox("你胜利，再来一局吧", "提示");
				for (int i = 0; i<10; i++)
					for (int j = 0; j<10; j++)
						if ((i == 3 && j == 0) || (i == 6 && j == 0) || (i == 0 && j == 3) || (i == 9 && j == 3))
							me->Broad[i][j] = 2;
						else if ((i == 0 && j == 6) || (i == 9 && j == 6) || (i == 3 && j == 9) || (i == 6 && j == 9))
							me->Broad[i][j] = 3;
						else
							me->Broad[i][j] = 0;
				me->lx = -1;
				me->ly = -1;
				me->times = 0;
				me->Is_Move = 0;
				me->Invalidate(FALSE);
				me->mode = 0;
				for (int i = me->m_action.GetCount() - 1; i >= 0; i--)
					me->m_action.DeleteString(i);
			}
		}
		if (status == 2)
		{
			count++;
			result = me->Computer1();
			//棋谱规范 2018new
			//x轴规范
			{
				if (result.chess_x == 0) sscanf("A", "%s", xxcout);
				else if (result.chess_x == 1) sscanf("B", "%s", xxcout);
				else if (result.chess_x == 2) sscanf("C", "%s", xxcout);
				else if (result.chess_x == 3) sscanf("D", "%s", xxcout);
				else if (result.chess_x == 4) sscanf("E", "%s", xxcout);
				else if (result.chess_x == 5) sscanf("F", "%s", xxcout);
				else if (result.chess_x == 6) sscanf("G", "%s", xxcout);
				else if (result.chess_x == 7) sscanf("H", "%s", xxcout);
				else if (result.chess_x == 8) sscanf("I", "%s", xxcout);
				else  sscanf("J", "%s", xxcout);

				if (result.x == 0) sscanf("A", "%s", lxxcout);
				else if (result.x == 1) sscanf("B", "%s", lxxcout);
				else if (result.x == 2) sscanf("C", "%s", lxxcout);
				else if (result.x == 3) sscanf("D", "%s", lxxcout);
				else if (result.x == 4) sscanf("E", "%s", lxxcout);
				else if (result.x == 5) sscanf("F", "%s", lxxcout);
				else if (result.x == 6) sscanf("G", "%s", lxxcout);
				else if (result.x == 7) sscanf("H", "%s", lxxcout);
				else if (result.x == 8) sscanf("I", "%s", lxxcout);
				else  sscanf("J", "%s", lxxcout);

				if (result.bar_x == 0) sscanf("A", "%s", barxcout);
				else if (result.bar_x == 1) sscanf("B", "%s", barxcout);
				else if (result.bar_x == 2) sscanf("C", "%s", barxcout);
				else if (result.bar_x == 3) sscanf("D", "%s", barxcout);
				else if (result.bar_x == 4) sscanf("E", "%s", barxcout);
				else if (result.bar_x == 5) sscanf("F", "%s", barxcout);
				else if (result.bar_x == 6) sscanf("G", "%s", barxcout);
				else if (result.bar_x == 7) sscanf("H", "%s", barxcout);
				else if (result.bar_x == 8) sscanf("I", "%s", barxcout);
				else  sscanf("J", "%s", barxcout);
			}
			//y轴规范
			itoa(11 - (result.chess_y + 1), yycout, 10);
			itoa(11 - (result.y + 1), lyycout, 10);
			itoa(11 - (result.bar_y + 1), barycout, 10);



			FILE *fp;
			fp = fopen("test.txt", "a+");
			fprintf(fp, "W ");
			fprintf(fp, "%d %d %d %d %d %d\n", result.y + 1, result.x + 1, result.chess_y + 1, result.chess_x + 1, result.bar_y + 1, result.bar_x + 1);
			fclose(fp);


			//2018new 电脑先手执行前要换行
			FILE *fp2;
			fp2 = fopen("FinalQiPu.txt", "a+");
			fprintf(fp2, "\n%d  %s%s%s%s(%s%s)  ", count,lxxcout, lyycout, xxcout, yycout, barxcout, barycout);
			fclose(fp2);


		
			Info.Format("***********************");  //new
			me->m_action.InsertString(me->m_action.GetCount(), Info);
			
			Info.Format("C:Get (%s,%s)", lxxcout, lyycout);   //new
			me->m_action.InsertString(me->m_action.GetCount(), Info);
			
			Info.Format("C:to(%s,%s)", xxcout, yycout);     //new
			me->m_action.InsertString(me->m_action.GetCount(), Info);

		
			Info.Format("C:Put bar at (%s,%s)", barxcout, barycout); //new
			me->m_action.InsertString(me->m_action.GetCount(), Info);
			////////////////////////////////////////////////////////////////////////////
			itoa(result.score, num5, 10);
			itoa(result.timecount, num6, 10);
			Info.Format("评价数:%s", num5);
			me->m_action.InsertString(me->m_action.GetCount(), Info);
			Info.Format("时间:%s", num6);
			me->m_action.InsertString(me->m_action.GetCount(), Info);

			//	itoa(B,num7,10);
			// Info.Format("得分:%s",num7);
			Info.Format("得分:%.5f", B);
			me->m_action.InsertString(me->m_action.GetCount(), Info);

			itoa(c, num8, 10);
			Info.Format("节点:%s", num8);
			me->m_action.InsertString(me->m_action.GetCount(), Info);

			Info.Format("W:%.2f", WS);
			me->m_action.InsertString(me->m_action.GetCount(), Info);

			TIME += result.timecount;
			Info.Format("TIME:%.0f", TIME);
			me->m_action.InsertString(me->m_action.GetCount(), Info);

			Info.Format("***********************");  //new
			me->m_action.InsertString(me->m_action.GetCount(), Info);
			///////////////////////////////////////////////////////////////////////////


			me->Broad[result.chess_x][result.chess_y] = 2;
			me->Broad[result.x][result.y] = 0;
			me->Broad[result.bar_x][result.bar_y] = 1;
			me->Invalidate(FALSE);
			status = 0;
			me->times = me->times + 3;
			int Re = me->Is_Over();
			if (Re != 0)
			{
				if (Re == 1)
					me->MessageBox("你胜利，再来一局吧", "提示");
				else
					me->MessageBox("电脑胜，再来一局吧", "提示");
				for (int i = 0; i<10; i++)
					for (int j = 0; j<10; j++)
						if ((i == 3 && j == 0) || (i == 6 && j == 0) || (i == 0 && j == 3) || (i == 9 && j == 3))
							me->Broad[i][j] = 2;
						else if ((i == 0 && j == 6) || (i == 9 && j == 6) || (i == 3 && j == 9) || (i == 6 && j == 9))
							me->Broad[i][j] = 3;
						else
							me->Broad[i][j] = 0;
				me->lx = -1;
				me->ly = -1;
				me->times = 0;
				me->Is_Move = 0;
				me->Invalidate(FALSE);
				me->mode = 0;
				for (int i = me->m_action.GetCount() - 1; i >= 0; i--)
					me->m_action.DeleteString(i);
			}
		}

	}
	return 0;


}
Hebe CYaMaXunDlg::Computer()//这开始就是搜索和评估的部分了
{

	int count = 0;
	Hebe GetResult;
	GetResult.bar_x = 1; GetResult.bar_y = 1; GetResult.chess_x = 1; GetResult.chess_y = 1; GetResult.x = 1;


	return GetResult;
}
Hebe CYaMaXunDlg::Computer1()
{
	string sst;
	char t[5];
	BYTE position[12][12];  //12*12估计是为了边界处理
	for (int i = 0; i<12; i++)     
	{
		for (int j = 0; j<12; j++)
		{
			position[i][j] = 1;
		}
	}

	for (int i = 1; i<11; i++)
	{
		for (int j = 1; j<11; j++)
		{
			position[i][j] = Broad[i - 1][j - 1];
		}
	}

	string s;
	for (int i = 1; i<11; i++)
	{
		for (int j = 1; j<11; j++)
		{
			sprintf(t, "%d", position[j][i]);
			sst = t;
			s = s + sst;
		}
	}
	mov tt;


	l.insert(pair<string, mov>("", tt));
	map<string, mov>::iterator it;
	/*CString temp;
	temp=s.c_str();
	AfxMessageBox(temp);*/
	it = l.find(s);

	Searchengine A;
	mov bestmove;
	////////////计时
	int timecount;
	extern int ec;
	extern int testc;
	extern int node;
	timecount = GetTickCount();
	if (it == l.end())
	{
		bestmove = A.searchagoodmove(position);
		//AfxMessageBox("mapfailed!");
		Beep(1000, 200);
	}
	else
	{
		bestmove = it->second;
		Beep(1000, 200);
	}

	Hebe a;

	a.bar_x = bestmove.barx - 1; a.bar_y = bestmove.bary - 1;
	a.chess_x = bestmove.x - 1; a.chess_y = bestmove.y - 1;
	a.x = bestmove.lx - 1; a.y = bestmove.ly - 1;
	a.score = testc;//ec;//A.num;
	a.timecount = GetTickCount() - timecount;
	a.node = node;
	B = bestmove.score;
	c = a.node;
	ss[1].barx = a.bar_x;
	ss[1].bary = a.bar_y;
	ss[1].lx = a.x;
	ss[1].ly = a.y;
	ss[1].x = a.chess_x;
	ss[1].y = a.chess_y;

	return a;
}






int CYaMaXunDlg::Is_OK(int x1, int y1, int x, int y, int tep[10][10])//判断电脑生成的招数是否符合规则
{
	if (x1 == x || y1 == y || (y1 - x1) == (y - x) || (x + y) == (x1 + y1))
	{
		if (x1 == x)
		{
			if (y1>y)
			{
				for (int i = y + 1; i<y1; i++)
					if (tep[x][i] == 1 || tep[x][i] == 2 || tep[x][i] == 3)
						return 0;
			}
			else
			{
				for (int i = y1 + 1; i<y; i++)
					if (tep[x][i] == 1 || tep[x][i] == 2 || tep[x][i] == 3)
						return 0;
			}
		}
		if (y1 == y)
		{
			if (x1>x)
			{
				for (int i = x + 1; i<x1; i++)
					if (tep[i][y] == 1 || tep[i][y] == 2 || tep[i][y] == 3)
						return 0;
			}
			else
			{
				for (int i = x1 + 1; i<x; i++)
					if (tep[i][y] == 1 || tep[i][y] == 2 || tep[i][y] == 3)
						return 0;
			}
		}
		if ((y1 - x1) == (y - x))
		{
			int k = y - x;
			if (y1>y)
			{
				for (int i = y + 1; i<y1; i++)
					if (tep[i - k][i] == 1 || tep[i - k][i] == 2 || tep[i - k][i] == 3)
						return 0;
			}
			else
			{
				for (int i = y1 + 1; i<y; i++)
					if (tep[i - k][i] == 1 || tep[i - k][i] == 2 || tep[i - k][i] == 3)
						return 0;
			}
		}
		if ((y1 + x1) == (y + x))
		{
			int k = y + x;
			if (y1>y)
			{
				for (int i = y + 1; i<y1; i++)
					if (tep[k - i][i] == 1 || tep[k - i][i] == 2 || tep[k - i][i] == 3)
						return 0;
			}
			else
			{
				for (int i = y1 + 1; i<y; i++)
					if (tep[k - i][i] == 1 || tep[k - i][i] == 2 || tep[k - i][i] == 3)
						return 0;
			}
		}
		return 1;
	}
	return 0;
}

void CYaMaXunDlg::OnButton1()
{
	Broad[ss[1].barx][ss[1].bary] = 0;
	Broad[ss[1].lx][ss[1].ly] = Broad[ss[1].x][ss[1].y];
	Broad[ss[1].x][ss[1].y] = 0;

	Broad[ss[0].barx][ss[0].bary] = 0;
	Broad[ss[0].lx][ss[0].ly] = Broad[ss[0].x][ss[0].y];
	Broad[ss[0].x][ss[0].y] = 0;

	Invalidate(FALSE);








	// TODO: Add your control notification handler code here

}
NodeOfSave * CYaMaXunDlg::MyInit()
{
	NodeOfSave temp;
	NodeOfSave *p;
	NodeOfSave *p1;
	NodeOfSave *head;
	FILE *fp;
	int i, j;


	if ((fp = fopen("data.dat", "r")) != NULL)
	{
		fread(&temp, sizeof(struct NodeOfSave), 1, fp);
		p1 = (NodeOfSave *)malloc(sizeof(struct NodeOfSave));
		head = p1;
		p1->count = temp.count;
		p1->Dcount = temp.Dcount;
		p1->Mcount = temp.Mcount;
		p1->Next = NULL;
		for (i = 0; i<10; i++)
		{
			for (j = 0; j<10; j++)
			{
				p1->Data[i][j] = temp.Data[i][j];
			}
		}
		p1->result.barx = temp.result.barx;
		p1->result.bary = temp.result.bary;
		p1->result.lx = temp.result.lx;
		p1->result.ly = temp.result.ly;
		p1->result.x = temp.result.x;
		p1->result.y = temp.result.y;
		while (fread(&temp, sizeof(struct NodeOfSave), 1, fp))
		{
			p = (NodeOfSave *)malloc(sizeof(struct NodeOfSave));

			p->count = temp.count;
			p->Dcount = temp.Dcount;
			p->Mcount = temp.Mcount;
			p->Next = NULL;
			//	MessageBox("此模式是人人！","提示");
			for (i = 0; i<10; i++)
			{
				for (j = 0; j<10; j++)
				{
					p->Data[i][j] = temp.Data[i][j];
				}
			}
			p->result.barx = temp.result.barx;
			p->result.bary = temp.result.bary;
			p->result.lx = temp.result.lx;
			p->result.ly = temp.result.ly;
			p->result.x = temp.result.x;
			p->result.y = temp.result.y;
			p1->Next = p;
			p1 = p;
		};
		fclose(fp);
	}
	return head;

}

string CYaMaXunDlg::transpos(string s)
{
	int i;
	for (i = 0; i<5; i++)
	{
		char c;

		c = s[i];
		s[i] = s[9 - i];
		s[9 - i] = c;

		c = s[10 + i];
		s[10 + i] = s[19 - i];
		s[19 - i] = c;

		c = s[20 + i];
		s[20 + i] = s[29 - i];
		s[29 - i] = c;

		c = s[30 + i];
		s[30 + i] = s[39 - i];
		s[39 - i] = c;

		c = s[40 + i];
		s[40 + i] = s[49 - i];
		s[49 - i] = c;

		c = s[50 + i];
		s[50 + i] = s[59 - i];
		s[59 - i] = c;

		c = s[60 + i];
		s[60 + i] = s[69 - i];
		s[69 - i] = c;

		c = s[70 + i];
		s[70 + i] = s[79 - i];
		s[79 - i] = c;

		c = s[80 + i];
		s[80 + i] = s[89 - i];
		s[89 - i] = c;

		c = s[90 + i];
		s[90 + i] = s[99 - i];
		s[99 - i] = c;
	}
	return s;
}

void CYaMaXunDlg::OnButtonAcc()
{
	// TODO: Add your control notification handler code here
	if (flag == 0)
		flag = 1;
	else if (flag == 1)
		flag = 2;
	else
		flag = 0;
}


//-----------------------2018改动-----------------------------------
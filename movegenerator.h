// movegenerator.h: interface for the movegenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOVEGENERATOR_H__0BF17A1D_CD3F_4D1E_8E21_A94108519DEE__INCLUDED_)
#define AFX_MOVEGENERATOR_H__0BF17A1D_CD3F_4D1E_8E21_A94108519DEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct mov
{
	BYTE x;
	BYTE y;
	BYTE lx;
	BYTE ly;
	BYTE barx;
	BYTE bary;
	double score;
 

};

class movegenerator
{
public:
	movegenerator();
    virtual ~movegenerator();

	int Greatepossiblemove(BYTE position[][12],int side,int nply);
	int Greatepossiblebar(BYTE position[][12],int x,int y,int lx,int ly,int nply);



public:
	mov moveline[10][2500];  //深度 2500种走法
	int movecount;

};

#endif // !defined(AFX_MOVEGENERATOR_H__0BF17A1D_CD3F_4D1E_8E21_A94108519DEE__INCLUDED_)

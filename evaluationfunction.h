// evaluationfunction.h: interface for the evaluationfunction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVALUATIONFUNCTION_H__87003B7B_4B9A_471B_8383_72883322FF37__INCLUDED_)
#define AFX_EVALUATIONFUNCTION_H__87003B7B_4B9A_471B_8383_72883322FF37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class evaluationfunction  
{
public:
	evaluationfunction();
	
	void copy(BYTE position[][12]);

    void kingmovesearch();
	void queenmovesearch();
    void mobilitysearch();

	void mobilityaccount();
	void t1account();
	void t2account();
	void c1account();
	void c2account();
	void waccount();
	void aaccount();
    double evaluation(BYTE position[][12],int side);

	virtual ~evaluationfunction();

	// Generated message map functions

    int nside;//0-white,1-black;

	BYTE kingmovewhite[12][12];
	BYTE queenmovewhite[12][12];

    BYTE kingmoveblack[12][12];
	BYTE queenmoveblack[12][12];

	BYTE curposition[12][12];
	BYTE mobility[12][12];

	double t1;
	double t2;
	double c1;
	double c2;
	double w;
	int awhite[4];
	int ablack[4];

	
	
};



#endif // !defined(AFX_EVALUATIONFUNCTION_H__87003B7B_4B9A_471B_8383_72883322FF37__INCLUDED_)

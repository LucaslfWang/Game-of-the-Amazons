// Searchengine.h: interface for the Searchengine class.
//
//////////////////////////////////////////////////////////////////////
#include"movegenerator.h"
#include"evaluationfunction.h"
#include"YaMaXunDlg.h"

#if !defined(AFX_SEARCHENGINE_H__2079319B_9CE5_4036_8219_7B2F9AAB5712__INCLUDED_)
#define AFX_SEARCHENGINE_H__2079319B_9CE5_4036_8219_7B2F9AAB5712__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

# define CUT_NODE 1
# define ALL_NODE -1
# define PV_NODE 0
const int PHASE_HASH=0; 
const int PHASE_KILLER1=1;
const int PHASE_KILLER2=2;
const int PHASE_CreatePM=3;
enum ENTRY_TYPE{ _exact , _lower_bound, _upper_bound}; 
typedef struct HASHITEM{
    LONGLONG checksum;	// or long long might be even better
  	ENTRY_TYPE  entry_type;
    short depth;
    double eval;
 	mov hashmove;
}HashItem;

class Searchengine  
{
public:
	Searchengine();
	virtual ~Searchengine();  
	mov searchagoodmove(BYTE position[][12]);
	BYTE makemove(mov *MOVE);
	void unmakemove(mov *MOVE,BYTE ID);
 //////////////////searchengine//////////////////////////
	double sR( int depth ,int node_type);
	double ms(double alpha ,double beta, int depth );
	friend bool xor(mov move1 ,mov move2);
	void Setbestmove(mov MV, int depth);
	//////////////////   ////////////////////////////
	//////////////history heustic/////////////////////////////////
    int *m_HistoryTable;
	BYTE GetHistoryScore(mov *MOVE);
	void EnterHistoryScore(mov *MOVE,int depth);
    friend bool cmp(mov mov1, mov mov2); 
/////////////////Hash Table////////////////////////////////////
	void InitializeHashKey();
	void CalculateInitHashKey(BYTE position[][12]);
    void Hash_MakeMove(mov *MOVE ,BYTE position[][12]);
    void Hash_UnMakeMove(mov *MOVE ,BYTE position[][12]);
    double LookUpHashTable(double alpha, double beta, int depth ,mov &mv );
	void EnterHashTable(ENTRY_TYPE entry_type, double eval, short depth ,mov mv );
/////////////////////////////////////////////////////////////////
public:
    HashItem *m_pTT;
    UINT m_nHashKey32[4][10][10];
	ULONGLONG m_ulHashKey64[4][10][10];
  	UINT m_HashKey32;
 	LONGLONG m_HashKey64;
	evaluationfunction *ef;//π¿÷µ∫À–ƒ÷∏’Î
	mov bestmove;
	int Maxdepth;
};

#endif // !defined(AFX_SEARCHENGINE_H__2079319B_9CE5_4036_8219_7B2F9AAB5712__INCLUDED_)

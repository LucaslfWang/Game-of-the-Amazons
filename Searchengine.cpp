// Searchengine.cpp: implementation of the Searchengine class.
//
//////////////////////////////////////////////////////////////////////
/////////////////new
#include "stdafx.h"
#include "sstream"
#include <string>
#include <iostream>
#include "YaMaXun.h"
#include "Searchengine.h"
#include "math.h"
#include <cassert>
#include "algorithm"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
mov killmoveTable[9];
movegenerator *mg;//�߷�����ָ��
int nDistance;
int Player;
int Limit_Count;
BYTE curposition[12][12];
mov nullmove;
extern double WS;

int times;
int testc;
int md = 1;
int node;
unsigned int Verteilung = 1000;//�޶���ʱ��  2018У���޸�


struct RS {
	mov curhashmove;
	int curcount, nCount;
	mov Next(int depth);
};
Searchengine::Searchengine()
{


}
Searchengine::~Searchengine()
{
	delete m_HistoryTable;
	delete m_pTT;
}
BYTE Searchengine::makemove(mov *MOVE)//���ӣ��������ͣ�2-�ף�3-��,����Hash_MakeMove()
{
	Hash_MakeMove(MOVE, curposition);
	Player = 1 - Player;
	nDistance++;
	BYTE ID;
	ID = curposition[MOVE->lx][MOVE->ly];
	curposition[MOVE->x][MOVE->y] = ID;
	curposition[MOVE->lx][MOVE->ly] = 0;
	curposition[MOVE->barx][MOVE->bary] = 1;
	return ID;
}
void Searchengine::unmakemove(mov *MOVE, BYTE ID)//���أ�����Hash_UnMakeMove(),sR()
{
	Hash_UnMakeMove(MOVE, curposition);
	Player = 1 - Player;
	nDistance--;
	curposition[MOVE->barx][MOVE->bary] = 0;
	curposition[MOVE->lx][MOVE->ly] = ID;
	curposition[MOVE->x][MOVE->y] = 0;
}
mov Searchengine::searchagoodmove(BYTE position[][12])//����������Bs.evaluation������
{
	int i, j;
	nullmove.barx = nullmove.bary = nullmove.lx = nullmove.ly = nullmove.score = nullmove.x = nullmove.y = 0;
	int punkt = 0;//�ϰ�����
	for (i = 1; i < 11; i++)
		for (j = 1; j < 11; j++)
		{
			if (position[i][j] == 1)
				punkt++;
		}
	
	movegenerator As;
	evaluationfunction Bs;
	mg = &As;
	ef = &Bs;
	node = 0;
	m_HistoryTable = new int[1000000];//��ʷ��¼��
	memset(m_HistoryTable, 0, 1000000 * 4);
	memset(killmoveTable, 0, 9 * sizeof(mov));
	Bs.evaluation(position, 1);
	WS = Bs.w;

	if (punkt % 2 == 0)
	{
		Verteilung = 10000;
		Limit_Count = 100;
		md = 1;

	}
	else
	{
		Verteilung = 10000;
		Limit_Count = 100;
		md = 1;
	}
/*
	if (punkt % 2 == 0)
	{
		if (WS >= 62)
		{
			Verteilung = 28000;
			Limit_Count = 210;
			md = 3;
		}
		if (WS < 62 && WS >= 58)
		{
			Verteilung = 30000;
			Limit_Count = 300;
			md = 3;
		}
		if (WS < 58 && WS >= 48)
		{
			Verteilung = 35000;
			Limit_Count = 210;
			md = 5;
		}
		if (WS < 48 && WS >= 42)
		{
			Verteilung = 30000;
			Limit_Count = 250;
			md = 5;
		}
		if (WS < 42 && WS >= 32)
		{
			Verteilung = 40000;
			Limit_Count = 150;
			md = 5;
		}
		if (WS < 32 && WS >= 22)
		{
			Verteilung = 35000;
			Limit_Count = 200;
			md = 5;
		}
		if (WS < 22 && WS >= 15)
		{
			Verteilung = 30000;
			Limit_Count = 250;
			md = 5;
		}
		if (WS < 15)
		{
			Verteilung = 30000;
			Limit_Count = 100;
			md = 5;
		}
	}
	else//������
	{
		if (WS >= 60)
		{
			Verteilung = 22000;
			Limit_Count = 220;
			md = 3;
		}
		if (WS < 60 && WS >= 58)
		{
			Verteilung = 25000;
			Limit_Count = 300;
			md = 3;
		}
		if (WS < 58 && WS >= 48)
		{
			Verteilung = 40000;
			Limit_Count = 200;
			md = 5;
		}
		if (WS < 48 && WS >= 42)
		{
			Verteilung = 28000;
			Limit_Count = 250;
			md = 5;
		}
		if (WS < 42 && WS >= 32)
		{
			Verteilung = 45000;
			Limit_Count = 150;
			md = 5;
		}
		if (WS < 32 && WS >= 28)
		{
			Verteilung = 32000;
			Limit_Count = 200;
			md = 5;
		}
		if (WS < 28)
		{
			Verteilung = 20000;
			Limit_Count = 200;
			md = 5;
		}
	}
*/


	testc = 0;
	nDistance = 0;
	node = 0;
	Player = 0;
	InitializeHashKey();
	memcpy(curposition, position, 144);
	CalculateInitHashKey(position);
	times = GetTickCount();//��ʱ
	bestmove = nullmove;
/*	for (Maxdepth = 1; Maxdepth <= md; Maxdepth++)//��������������
//	{
		if (GetTickCount() - times > Verteilung)
		{
			break;
		}
		ms(-20000, 20000, Maxdepth);
	}
	*/
		Maxdepth = md;
		ms(-20000, 20000, Maxdepth);
	return bestmove;
	
}

double Searchengine::ms(double alpha, double beta, int depth)
{
	double score;
	double best = -20000;
	mov *mv;
	mov hashmv, bestmv;
	int  i;
	RS Rs;
	BYTE ID;
	ENTRY_TYPE hashflag;
	if ((GetTickCount() - times) > Verteilung)//����
	{
		return 1234567;
	}
	score = LookUpHashTable(alpha, beta, depth, hashmv);
	if (score != 66666)
	{
		return score;
	}
	if (depth == 0)
	{
		testc++;//������
		best = ef->evaluation(curposition, Player);
		EnterHashTable(_exact, score, depth, hashmv);
		return best;
	}
	Rs.nCount = mg->Greatepossiblemove(curposition, Player, depth);
	if (depth == Maxdepth)//��������
	{
		for (i = 0; i < Rs.nCount; i++)
		{
			if ((GetTickCount() - times) > Verteilung)//����
			{
				return 1234567;
			}
			mv = &mg->moveline[depth][i];
			ID = makemove(mv);
			mv->score = ef->evaluation(curposition, 1 - Player)+ 0.8*GetHistoryScore(mv);
			unmakemove(mv, ID);
		}
		std::sort(mg->moveline[depth], mg->moveline[depth] + Rs.nCount, cmp);
		if (Rs.nCount > Limit_Count)
		{
			Rs.nCount = Limit_Count;
		}
	}
	else//��ʷ��������Ч�ʺܸ�
	{
		for (i = 0; i < Rs.nCount; i++)
		{
			mg->moveline[depth][i].score = 0.8*GetHistoryScore(&mg->moveline[depth][i]);
		}
		std::sort(mg->moveline[depth], mg->moveline[depth] + Rs.nCount, cmp);
	}
	if (Rs.nCount == 0)
	{
		return -10000;
	}
	//��ͨAB��֦+�û���
	hashflag = _upper_bound;
	bestmv.barx = bestmv.bary = bestmv.lx = bestmv.ly = bestmv.x = bestmv.y = 0;
	if (xor (killmoveTable[nDistance], nullmove))
	{
		for (i = 0; i < Rs.nCount; ++i)
		{
			if (!xor (killmoveTable[nDistance], mg->moveline[depth][i]))
			{
				swap(mg->moveline[depth][0], mg->moveline[depth][i]);
			}
		}
	}
	for (i = 0; i < Rs.nCount; ++i)
	{
		mv = &mg->moveline[depth][i];
		if (depth == md && (GetTickCount() - times) < Verteilung)
		{
			node++;//�ڵ�
		}
		ID = makemove(mv);
		if (best == -20000) 
		{
			score = -ms(-beta, -alpha, depth - 1);
		}
		else
		{
			score = -ms(-alpha - .0001, -alpha, depth - 1);
			if (score > best && score<beta)
			{
				score = -ms(-beta, -alpha, depth - 1);
			}
		}
		unmakemove(mv, ID);
		if (score > best)
		{
			best = score;
			
			if (depth == Maxdepth)
			{
				bestmove = *mv;
				bestmove.score = best;
			}
			if (score >= alpha)
			{
				hashflag = _exact;
				bestmv = *mv;
				alpha = score;
			}
			if (score >= beta)
			{
				hashflag = _lower_bound;
				bestmv = *mv;
				break;
			}
		}
	}
	EnterHashTable(hashflag, best, depth, bestmv);
	if (xor (bestmv, nullmove)) 
	{
		EnterHistoryScore(&bestmv, depth);
		killmoveTable[nDistance] = bestmv;

	}
	if (best == -20000)
	{
		return 1234567;
	}
	return best;
}

bool cmp(mov mov1, mov mov2)
{
	return mov1.score > mov2.score;
}

bool xor(mov move1, mov move2)//�ж������߷��Ƿ�ͬ
{
	if (move1.barx == move2.barx && move1.bary == move2.bary && move1.lx == move2.lx
		&& move1.ly == move2.ly && move1.x == move2.x && move1.y == move2.y)
		return false;
	else
		return true;
}

LONGLONG rand64(void)
{
	return rand() ^ ((LONGLONG)rand() << 15) ^ ((LONGLONG)rand() << 30) ^
		((LONGLONG)rand() << 45) ^ ((LONGLONG)rand() << 60);
}
LONG rand32(void)
{
	return rand() ^ ((LONG)rand() << 15) ^ ((LONG)rand() << 30);

}
void Searchengine::InitializeHashKey()
{
	int i, j, k;
	srand((unsigned)time(NULL));
	for (i = 0; i < 4; i++)
		for (j = 0; j < 10; j++)
			for (k = 0; k < 10; k++)
			{
				m_nHashKey32[i][j][k] = rand32();
				m_ulHashKey64[i][j][k] = rand64();
			}
	m_pTT = new HashItem[2048 * 2048];
}
void Searchengine::CalculateInitHashKey(BYTE position[][12])
{
	int i, j;
	BYTE nStoneType;
	m_HashKey32 = 0;
	m_HashKey64 = 0;
	for (i = 1; i < 11; i++)
		for (j = 1; j < 11; j++)
		{
			nStoneType = position[i][j];

			if (nStoneType != 0)    //0=NO_CHESS  
			{
				m_HashKey32 = m_HashKey32 ^ m_nHashKey32[nStoneType][i - 1][j - 1];
				m_HashKey64 = m_HashKey64 ^ m_ulHashKey64[nStoneType][i - 1][j - 1];

			}
		}
}
void Searchengine::Hash_MakeMove(mov *MOVE, BYTE position[][12])
{
	BYTE FromID;
	FromID = position[MOVE->lx][MOVE->ly];
	////////////////////����
	m_HashKey32 = m_HashKey32^m_nHashKey32[FromID][MOVE->lx - 1][MOVE->ly - 1];   //^Ϊ��λ��
	m_HashKey64 = m_HashKey64 ^m_ulHashKey64[FromID][MOVE->lx - 1][MOVE->ly - 1];
	////////////////////////����/////////////////////////////////////////
	m_HashKey32 = m_HashKey32^m_nHashKey32[FromID][MOVE->x - 1][MOVE->y - 1];
	m_HashKey64 = m_HashKey64 ^ m_ulHashKey64[FromID][MOVE->x - 1][MOVE->y - 1];
	/////////////////////////////�����ϰ�/////////////////// �ϰ�=1
	m_HashKey32 = m_HashKey32^m_nHashKey32[1][MOVE->barx - 1][MOVE->bary - 1];
	m_HashKey64 = m_HashKey64 ^ m_ulHashKey64[1][MOVE->barx - 1][MOVE->bary - 1];
}
void Searchengine::Hash_UnMakeMove(mov *MOVE, BYTE position[][12])
{
	BYTE ToID;
	ToID = position[MOVE->x][MOVE->y];
	/////////////////////��ԭ�ϰ�//////////////////////
	m_HashKey32 = m_HashKey32^m_nHashKey32[1][MOVE->barx - 1][MOVE->bary - 1];
	m_HashKey64 = m_HashKey64 ^ m_ulHashKey64[1][MOVE->barx - 1][MOVE->bary - 1];
	////////////////��ԭ���ӵ�///////////////////////
	m_HashKey32 = m_HashKey32^m_nHashKey32[ToID][MOVE->x - 1][MOVE->y - 1];
	m_HashKey64 = m_HashKey64 ^ m_ulHashKey64[ToID][MOVE->x - 1][MOVE->y - 1];
	//////////////////////////////��Ա���ӵ�///////////////////////
	m_HashKey32 = m_HashKey32^m_nHashKey32[ToID][MOVE->lx - 1][MOVE->ly - 1];
	m_HashKey64 = m_HashKey64 ^m_ulHashKey64[ToID][MOVE->lx - 1][MOVE->ly - 1];
}

double Searchengine::LookUpHashTable(double alpha, double beta, int depth, mov  &mv)
{
	int x;
	HashItem * pht;
	x = m_HashKey32 & 0x3FFFFF;
	pht = &m_pTT[x];
	if (pht->checksum != m_HashKey64)
	{
		mv.barx = mv.bary = mv.lx = mv.ly = mv.x = mv.y = 0;
		return 66666;
	}
	mv = pht->hashmove;
	if (pht->depth >= depth)
	{
		switch (pht->entry_type)
		{
		case _exact:
			return pht->eval;
		case _lower_bound:
			if (pht->eval >= beta)
				return (pht->eval);
			else
				break;
		case _upper_bound:
			if (pht->eval <= alpha)
				return (pht->eval);
			else
				break;
		}
	}
	return 66666;
}

void Searchengine::EnterHashTable(ENTRY_TYPE entry_type, double eval, short depth, mov mv)
{
	int x;
	HashItem * pht;
	x = m_HashKey32 & 0x3FFFFF;//��ʮλ��ϣ��ַ
	pht = &m_pTT[x];
	if (pht->depth > depth)
	{
		return;
	}
	pht->checksum = m_HashKey64;
	pht->entry_type = entry_type;
	pht->hashmove = mv;
	pht->eval = eval;
	pht->depth = depth;
}

BYTE Searchengine::GetHistoryScore(mov *MOVE)
{
	int number;
	number = (MOVE->lx - 1) + (MOVE->ly - 1) * 10 + (MOVE->x - 1) * 100 + (MOVE->y - 1) * 1000 + (MOVE->barx - 1) * 10000 + (MOVE->bary - 1) * 100000;
	return m_HistoryTable[number];
}

void Searchengine::EnterHistoryScore(mov *MOVE, int depth)
{
	int number;
	number = (MOVE->lx - 1) + (MOVE->ly - 1) * 10 + (MOVE->x - 1) * 100 + (MOVE->y - 1) * 1000 + (MOVE->barx - 1) * 10000 + (MOVE->bary - 1) * 100000;
	m_HistoryTable[number] += 1 << depth;
}
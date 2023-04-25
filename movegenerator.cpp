// movegenerator.cpp: implementation of the movegenerator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "YaMaXun.h"
#include "movegenerator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

movegenerator::movegenerator()
{

}

movegenerator::~movegenerator()
{

}

int movegenerator::Greatepossiblemove(BYTE position[][12], int side, int nply)  //第二个参数是深度
{
	movecount = 0;
	BYTE i, j;
	BYTE k, l;
	for (int ii = 0; ii < 2500; ii++)   //清零
	{
		moveline[nply][ii].x = 0;
		moveline[nply][ii].y = 0;
		moveline[nply][ii].lx = 0;
		moveline[nply][ii].ly = 0;
		moveline[nply][ii].barx = 0;
		moveline[nply][ii].bary = 0;
		moveline[nply][ii].score = 0;
	}
	//如果有棋子 则走8个方向
	for (i = 0; i < 12; i++)    //2018new  原来改的
	{
		for (j = 0; j < 12; j++)
 		{
			if (position[i][j] == 2 && side == 0)
			{
				k = i; l = j;
				while ( position[k - 1][l - 1] == 0)
				{
					movecount = movecount + Greatepossiblebar(position, k - 1, l - 1, i, j, nply); k--; l--;
				}

				k = i; l = j;
				while ( position[k - 1][l] == 0)
				{
					movecount = movecount + Greatepossiblebar(position, k - 1, l, i, j, nply); k--;
				}

				k = i; l = j;
				while ( position[k - 1][l + 1] == 0)
				{
					movecount = movecount + Greatepossiblebar(position, k - 1, l + 1, i, j, nply); k--; l++;
				}

				k = i; l = j;
				while (position[k][l - 1] == 0)
				{
					movecount = movecount + Greatepossiblebar(position, k, l - 1, i, j, nply); l--;
				}

				k = i; l = j;
				while (position[k][l + 1] == 0)
				{
					movecount = movecount + Greatepossiblebar(position, k, l + 1, i, j, nply); l++;
				}

				k = i; l = j;
				while (position[k + 1][l - 1] == 0)
				{
					movecount = movecount + Greatepossiblebar(position, k + 1, l - 1, i, j, nply); k++; l--;
				}

				k = i; l = j;
				while (position[k + 1][l] == 0)
				{
					movecount = movecount + Greatepossiblebar(position, k + 1, l, i, j, nply); k++;
				}

				k = i; l = j;
				while (position[k + 1][l + 1] == 0)
				{
					movecount = movecount + Greatepossiblebar(position, k + 1, l + 1, i, j, nply); k++; l++;
				}

			}
			if (position[i][j] == 3 && side == 1)
			{
				k = i; l = j;
				while (position[k - 1][l - 1] == 0)
				{
					movecount = movecount + Greatepossiblebar(position, k - 1, l - 1, i, j, nply); k--; l--;
				}
				k = i; l = j;
				while ( position[k - 1][l] == 0)
				{
					movecount = movecount + Greatepossiblebar(position, k - 1, l, i, j, nply); k--;
				}
				k = i; l = j;
				while ( position[k - 1][l + 1] == 0)
				{
					movecount = movecount + Greatepossiblebar(position, k - 1, l + 1, i, j, nply); k--; l++;
				}

				k = i; l = j;
				while ( position[k][l - 1] == 0)
				{
					movecount = movecount + Greatepossiblebar(position, k, l - 1, i, j, nply); l--;
				}

				k = i; l = j;
				while ( position[k][l + 1] == 0)
				{
					movecount = movecount + Greatepossiblebar(position, k, l + 1, i, j, nply); l++;
				}

				k = i; l = j;
				while ( position[k + 1][l - 1] == 0)
				{
					movecount = movecount + Greatepossiblebar(position, k + 1, l - 1, i, j, nply); k++; l--;
				}

				k = i; l = j;
				while (position[k + 1][l] == 0)
				{
					movecount = movecount + Greatepossiblebar(position, k + 1, l, i, j, nply); k++;
				}

				k = i; l = j;
				while ( position[k + 1][l + 1] == 0)
				{
					movecount = movecount + Greatepossiblebar(position, k + 1, l + 1, i, j, nply); k++; l++;
				}
			}
		}
	}
	return movecount;

}

int movegenerator::Greatepossiblebar(BYTE position[][12], int x, int y, int lx, int ly, int nply)
{
	BYTE curposition[12][12];
	int n = 0;
	int i, j;
	int k, l;
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			curposition[i][j] = position[i][j];
		}
	}
	curposition[x][y] = curposition[lx][ly];
	curposition[lx][ly] = 0;
									//走完棋
	i = x; j = y;
	k = i; l = j;
	while (curposition[k - 1][l - 1] == 0)
	{
		moveline[nply][n + movecount].x = x;
		moveline[nply][n + movecount].y = y;
		moveline[nply][n + movecount].lx = lx;
		moveline[nply][n + movecount].ly = ly; 
		moveline[nply][n + movecount].barx = k - 1;
		moveline[nply][n + movecount].bary = l - 1;
		moveline[nply][n + movecount].score = 0;
		k--; l--; n++;
	}

	k = i; l = j;
	while (curposition[k - 1][l] == 0)
	{
		moveline[nply][n + movecount].x = x;
		moveline[nply][n + movecount].y = y;
		moveline[nply][n + movecount].lx = lx;
		moveline[nply][n + movecount].ly = ly;
		moveline[nply][n + movecount].barx = k - 1; 
		moveline[nply][n + movecount].bary = l;
		moveline[nply][n + movecount].score = 0;
		k--; n++;
	}

	k = i; l = j;
	while (curposition[k - 1][l + 1] == 0)
	{
		moveline[nply][n + movecount].x = x;
		moveline[nply][n + movecount].y = y;
		moveline[nply][n + movecount].lx = lx; 
		moveline[nply][n + movecount].ly = ly; 
		moveline[nply][n + movecount].barx = k - 1;
		moveline[nply][n + movecount].bary = l + 1;
		moveline[nply][n + movecount].score = 0;
		k--; l++; n++;
	}

	k = i; l = j;
	while (curposition[k][l - 1] == 0)
	{
		moveline[nply][n + movecount].x = x;
		moveline[nply][n + movecount].y = y; 
		moveline[nply][n + movecount].lx = lx; 
		moveline[nply][n + movecount].ly = ly;
		moveline[nply][n + movecount].barx = k;
		moveline[nply][n + movecount].bary = l - 1;
		moveline[nply][n + movecount].score = 0;
		l--; n++;
	}

	k = i; l = j;
	while (curposition[k][l + 1] == 0)
	{
		moveline[nply][n + movecount].x = x;
		moveline[nply][n + movecount].y = y;
		moveline[nply][n + movecount].lx = lx; 
		moveline[nply][n + movecount].ly = ly; 
		moveline[nply][n + movecount].barx = k;
		moveline[nply][n + movecount].bary = l + 1;
		moveline[nply][n + movecount].score = 0;
		l++; n++;
	}

	k = i; l = j;
	while (curposition[k + 1][l - 1] == 0)
	{
		moveline[nply][n + movecount].x = x;
		moveline[nply][n + movecount].y = y; 
		moveline[nply][n + movecount].lx = lx;
		moveline[nply][n + movecount].ly = ly; 
		moveline[nply][n + movecount].barx = k + 1; 
		moveline[nply][n + movecount].bary = l - 1;
		moveline[nply][n + movecount].score = 0;
		k++; l--; n++;
	}
	k = i; l = j;
	while (curposition[k + 1][l] == 0)
	{
		moveline[nply][n + movecount].x = x;
		moveline[nply][n + movecount].y = y; 
		moveline[nply][n + movecount].lx = lx;
		moveline[nply][n + movecount].ly = ly;
		moveline[nply][n + movecount].barx = k + 1;
		moveline[nply][n + movecount].bary = l;
		moveline[nply][n + movecount].score = 0;
		k++; n++;
	}
	k = i; l = j;
	while (curposition[k + 1][l + 1] == 0)
	{
		moveline[nply][n + movecount].x = x; 
		moveline[nply][n + movecount].y = y; 
		moveline[nply][n + movecount].lx = lx;
		moveline[nply][n + movecount].ly = ly; 
		moveline[nply][n + movecount].barx = k + 1; 
		moveline[nply][n + movecount].bary = l + 1;
		moveline[nply][n + movecount].score = 0;
		k++; l++; n++;
	}
	return n;
}


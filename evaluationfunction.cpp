// evaluationfunction.cpp: implementation of the evaluationfunction class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "YaMaXun.h"
#include "evaluationfunction.h"
#include<math.h> 

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// evaluationfunction

extern int first;

evaluationfunction::evaluationfunction()
{
}

evaluationfunction::~evaluationfunction()
{
}


int dx[] = { -1,0,1,-1,1,-1,0,1 };
int dy[] = { 1,1,1,0,0,-1,-1,-1 };

struct coordinate
{
	int x, y;
	int num;
	coordinate() {}
	coordinate(int a, int b, int c) :x(a), y(b), num(c) {}
}coor, tmp, q[110];

void evaluationfunction::kingmovesearch()//到某点最少需经过几个格点
{
	int i, j, k, l, u, v;
	for (i = 1; i < 11; ++i)
	{
		for (j = 1; j < 11; ++j)
		{
			kingmovewhite[i][j] = 0;//初始化为0
			kingmoveblack[i][j] = 0;
		}
	}
	k = l = 0;
	for (i = 1; i < 11; ++i)
	{
		for (j = 1; j < 11; ++j)
		{
			if (curposition[i][j] == 2)//white king 1
			{
				coor.x = i;
				coor.y = j;
				coor.num = 0;
				q[k++] = coor;
			}
		}
	}
	while (k != l)
	{
		tmp = q[l++];
		for (i = 0; i < 8; i++)
		{
			u = tmp.x + dx[i];
			v = tmp.y + dy[i];
			if (u > 0 && u < 11 && v>0 && v < 11 && kingmovewhite[u][v] == 0 && curposition[u][v] == 0)
			{
				coor.x = u;
				coor.y = v;
				coor.num = tmp.num + 1;
				q[k++] = coor;
				kingmovewhite[u][v] = coor.num;
			}
		}
	}
	k = l = 0;
	for (i = 1; i < 11; ++i)
	{
		for (j = 1; j < 11; ++j)
		{
			if (curposition[i][j] == 3)//black king 1
			{
				coor.x = i;
				coor.y = j;
				coor.num = 0;
				q[k++] = coor;
			}
		}
	}
	while (l != k)
	{
		tmp = q[l++];
		for (i = 0; i < 8; i++)
		{
			u = tmp.x + dx[i];
			v = tmp.y + dy[i];
			if (u > 0 && u < 11 && v>0 && v < 11 && kingmoveblack[u][v] == 0 && curposition[u][v] == 0)
			{
				coor.x = u;
				coor.y = v;
				coor.num = tmp.num + 1;
				q[k++] = coor;
				kingmoveblack[u][v] = coor.num;
			}
		}
	}
}

void evaluationfunction::copy(BYTE position[][12])
{
	for (int i = 0; i < 12; ++i)
	{
		for (int j = 0; j < 12; ++j)
		{
			curposition[i][j] = position[i][j];
		}
	}
}

void evaluationfunction::queenmovesearch()//到某点的最小路径
{
	int i, j, k, l, u, v;
	for (i = 1; i < 11; ++i)
	{
		for (j = 1; j < 11; ++j)
		{
			queenmovewhite[i][j] = 0;
			queenmoveblack[i][j] = 0;
		}
	}
	k = l = 0;
	for (i = 1; i < 11; ++i)
	{
		for (j = 1; j < 11; ++j)
		{
			if (curposition[i][j] == 2)//white king 1
			{
				coor.x = i;
				coor.y = j;
				coor.num = 0;
				q[k++] = coor;
			}
		}
	}
	while (k != l)
	{
		tmp = q[l++];
		for (i = 0; i < 8; ++i)
		{
			u = tmp.x + dx[i];
			v = tmp.y + dy[i];
			while (u > 0 && u < 11 && v>0 && v < 11 && curposition[u][v] == 0)
			{
				if (queenmovewhite[u][v] == 0)
				{
					coor.x = u;
					coor.y = v;
					coor.num = tmp.num + 1;
					q[k++] = coor;
					queenmovewhite[u][v] = coor.num;
				}
				u += dx[i];
				v += dy[i];
			}
		}
	}
	k = l = 0;
	for (i = 1; i < 11; ++i)
	{
		for (j = 1; j < 11; ++j)
		{
			if (curposition[i][j] == 3)//white king 1
			{
				coor.x = i;
				coor.y = j;
				coor.num = 0;
				q[k++] = coor;
			}
		}
	}
	while (l != k)
	{
		tmp = q[l++];
		for (i = 0; i < 8; i++)
		{
			u = tmp.x + dx[i];
			v = tmp.y + dy[i];
			while (u > 0 && u< 11 && v>0 && v< 11 && curposition[u][v] == 0)
			{
				if (queenmoveblack[u][v] == 0)
				{
					coor.x = u;
					coor.y = v;
					coor.num = tmp.num + 1;
					q[k++] = coor;
					queenmoveblack[u][v] = coor.num;
				}
				u += dx[i];
				v += dy[i];
			}
		}
	}
}

void evaluationfunction::mobilitysearch()
{
	for (int i = 0; i<12; i++)
	{
		for (int j = 0; j<12; j++)
		{
			mobility[i][j] = 0;
		}
	}

	for (int i = 0; i<12; i++)
	{
		for (int j = 0; j<12; j++)
		{
			if (curposition[i][j] == 0)
			{
				if (curposition[i - 1][j - 1] == 0)
				{
					mobility[i][j] = mobility[i][j] + 1;
				}
				if (curposition[i - 1][j] == 0)
				{
					mobility[i][j] = mobility[i][j] + 1;
				}
				if (curposition[i - 1][j + 1] == 0)
				{
					mobility[i][j] = mobility[i][j] + 1;
				}
				if (curposition[i][j - 1] == 0)
				{
					mobility[i][j] = mobility[i][j] + 1;
				}
				if (curposition[i][j + 1] == 0)
				{
					mobility[i][j] = mobility[i][j] + 1;
				}
				if (curposition[i + 1][j - 1] == 0)
				{
					mobility[i][j] = mobility[i][j] + 1;
				}
				if (curposition[i + 1][j] == 0)
				{
					mobility[i][j] = mobility[i][j] + 1;
				}
				if (curposition[i + 1][j + 1] == 0)
				{
					mobility[i][j] = mobility[i][j] + 1;
				}
			}
		}

	}
}

void evaluationfunction::t1account()
{
	t1 = 0;
	for (int i = 0; i<12; i++)
	{
		for (int j = 0; j<12; j++)
		{
			if (curposition[i][j] == 0)
			{
				if (queenmovewhite[i][j] == queenmoveblack[i][j] != 0)
				{
					t1 = t1 + 0.1;
				}//k=0.1，可修改参数

				if (queenmovewhite[i][j]<queenmoveblack[i][j])
				{
					if (queenmovewhite[i][j] == 0)
					{
						t1 = t1 - 1;
					}
					if (queenmovewhite[i][j] != 0)
					{
						t1 = t1 + 1;
					}

				}
				if (queenmovewhite[i][j]>queenmoveblack[i][j])
				{
					if (queenmoveblack[i][j] == 0)
					{
						t1 = t1 + 1;
					}
					if (queenmoveblack[i][j] != 0)
					{
						t1 = t1 - 1;
					}
				}

			}



		}
	}


}

void evaluationfunction::t2account()
{
	t2 = 0;
	for (int i = 0; i<12; i++)
	{
		for (int j = 0; j<12; j++)
		{
			if (curposition[i][j] == 0)
			{
				if (kingmovewhite[i][j] == kingmoveblack[i][j] != 0)
				{
					t2 = t2 + 0.1;
				}

				if (kingmovewhite[i][j]<kingmoveblack[i][j])
				{
					if (kingmovewhite[i][j] == 0)
					{
						t2 = t2 - 1;
					}
					if (kingmovewhite[i][j] != 0)
					{
						t2 = t2 + 1;
					}

				}
				if (kingmovewhite[i][j]>kingmoveblack[i][j])
				{
					if (kingmoveblack[i][j] == 0)
					{
						t2 = t2 + 1;
					}
					if (kingmoveblack[i][j] != 0)
					{
						t2 = t2 - 1;
					}
				}

			}



		}
	}
}

void evaluationfunction::c1account()
{
	c1 = 0;
	for (int i = 0; i<12; i++)
	{
		for (int j = 0; j<12; j++)
		{
			if (curposition[i][j] == 0)
			{
				if (queenmovewhite[i][j] != 0 && queenmoveblack[i][j] != 0)
				{
					c1 = c1 + pow(2, -(queenmovewhite[i][j])) - pow(2, -(queenmoveblack[i][j]));
				}
				if (queenmovewhite[i][j] == 0 && queenmoveblack[i][j] != 0)
				{
					c1 = c1 - pow(2, -(queenmoveblack[i][j]));
				}
				if (queenmovewhite[i][j] != 0 && queenmoveblack[i][j] == 0)
				{
					c1 = c1 + pow(2, -(queenmovewhite[i][j]));
				}

			}
		}
	}
	c1 = c1 * 2;

}

void evaluationfunction::c2account()
{
	c2 = 0;
	double a;
	for (int i = 0; i<12; i++)
	{
		for (int j = 0; j<12; j++)
		{
			if (curposition[i][j] == 0)
			{
				if (kingmovewhite[i][j] != 0 && kingmoveblack[i][j] != 0)
				{
					a = (kingmoveblack[i][j] - kingmovewhite[i][j]);
					c2 = c2 + min(1, (double)max(-1, a / 6));
				}
				if (kingmovewhite[i][j] == 0 && kingmoveblack[i][j] != 0)
				{
					c2 = c2 - 1;
				}
				if (kingmovewhite[i][j] != 0 && kingmoveblack[i][j] == 0)
				{
					c2 = c2 + 1;
				}
			}
		}
	}


}

void evaluationfunction::waccount()
{
	w = 0;
	for (int i = 0; i<12; i++)
	{
		for (int j = 0; j<12; j++)
		{
			if (curposition[i][j] == 0)
			{
				if (queenmovewhite[i][j] != 0 && queenmoveblack[i][j] != 0)
				{
					w = w + pow(2, -(fabs(queenmovewhite[i][j] - queenmoveblack[i][j])));
				}
			}
		}
	}

}

void evaluationfunction::aaccount()
{
	int k, l, m;
	int n = 0;
	int h = 0;
	awhite[0] = awhite[1] = awhite[2] = awhite[3] = ablack[0] = ablack[1] = ablack[2] = ablack[3] = 0;


	for (int i = 0; i<12; i++)
	{
		for (int j = 0; j<12; j++)
		{
			if (curposition[i][j] == 2)
			{
				k = i; l = j; m = 1;
				while (curposition[k - 1][l - 1] == 0 && queenmoveblack[k - 1][l - 1] != 0)
				{
					awhite[n] = awhite[n] + mobility[k - 1][l - 1] / m; k--; l--; m = m * 2;
				}

				k = i; l = j; m = 1;
				while (curposition[k - 1][l] == 0 && queenmoveblack[k - 1][l] != 0)
				{
					awhite[n] = awhite[n] + mobility[k - 1][l] / m; k--; m = m * 2;
				}

				k = i; l = j; m = 1;
				while (curposition[k - 1][l + 1] == 0 && queenmoveblack[k - 1][l + 1] != 0)
				{
					awhite[n] = awhite[n] + mobility[k - 1][l + 1] / m; k--; l++; m = m * 2;
				}

				k = i; l = j; m = 1;
				while (curposition[k][l - 1] == 0 && queenmoveblack[k][l - 1] != 0)
				{
					awhite[n] = awhite[n] + mobility[k][l - 1] / m; l--; m = m * 2;
				}

				k = i; l = j; m = 1;
				while (curposition[k][l + 1] == 0 && queenmoveblack[k][l + 1] != 0)
				{
					awhite[n] = awhite[n] + mobility[k][l + 1] / m; l++; m = m * 2;
				}

				k = i; l = j; m = 1;
				while (curposition[k + 1][l - 1] == 0 && queenmoveblack[k + 1][l - 1] != 0)
				{
					awhite[n] = awhite[n] + mobility[k + 1][l - 1] / m; k++; l--; m = m * 2;
				}

				k = i; l = j; m = 1;
				while (curposition[k + 1][l] == 0 && queenmoveblack[k + 1][l] != 0)
				{
					awhite[n] = awhite[n] + mobility[k + 1][l] / m; k++; m = m * 2;
				}

				k = i; l = j; m = 1;
				while (curposition[k + 1][l + 1] == 0 && queenmoveblack[k + 1][l + 1] != 0)
				{
					awhite[n] = awhite[n] + mobility[k + 1][l + 1] / m; k++; l++; m = m * 2;
				}
				n++;
			}

			if (curposition[i][j] == 3)
			{
				k = i; l = j; m = 1;
				while (curposition[k - 1][l - 1] == 0 && queenmovewhite[k - 1][l - 1] != 0)
				{
					ablack[h] = ablack[h] + mobility[k - 1][l - 1] / m; k--; l--; m = m * 2;
				}

				k = i; l = j; m = 1;
				while (curposition[k - 1][l] == 0 && queenmovewhite[k - 1][l] != 0)
				{
					ablack[h] = ablack[h] + mobility[k - 1][l] / m; k--; m = m * 2;
				}

				k = i; l = j; m = 1;
				while (curposition[k - 1][l + 1] == 0 && queenmovewhite[k - 1][l + 1] != 0)
				{
					ablack[h] = ablack[h] + mobility[k - 1][l + 1] / m; k--; l++; m = m * 2;
				}

				k = i; l = j; m = 1;
				while (curposition[k][l - 1] == 0 && queenmovewhite[k][l - 1] != 0)
				{
					ablack[h] = ablack[h] + mobility[k][l - 1] / m; l--; m = m * 2;
				}

				k = i; l = j; m = 1;
				while (curposition[k][l + 1] == 0 && queenmovewhite[k][l + 1] != 0)
				{
					ablack[h] = ablack[h] + mobility[k][l + 1] / m; l++; m = m * 2;
				}

				k = i; l = j; m = 1;
				while (curposition[k + 1][l - 1] == 0 && queenmovewhite[k + 1][l - 1] != 0)
				{
					ablack[h] = ablack[h] + mobility[k + 1][l - 1] / m; k++; l--; m = m * 2;
				}

				k = i; l = j; m = 1;
				while (curposition[k + 1][l] == 0 && queenmovewhite[k + 1][l] != 0)
				{
					ablack[h] = ablack[h] + mobility[k + 1][l] / m; k++; m = m * 2;
				}

				k = i; l = j; m = 1;
				while (curposition[k + 1][l + 1] == 0 && queenmovewhite[k + 1][l + 1] != 0)
				{
					ablack[h] = ablack[h] + mobility[k + 1][l + 1] / m; k++; l++; m = m * 2;
				}
				h++;
			}
		}
	}
}

int ec = 0;
double evaluationfunction::evaluation(BYTE position[][12], int side)//请修改此处代码
{
	ec++;
	double value;

	copy(position);
	nside = side;
	kingmovesearch();
	queenmovesearch();
	mobilitysearch();
	t1account();//queen走法的领地数量
	t2account();//king走法的领地数量
	c1account();//queen走法的地理位置优劣
	c2account();//king走法的地理位置优劣
	waccount();
	double a, b, c;//参数
	a = (5 / (w + 5));
	b = (w / (w + 20));
	c = (1 - (a + b)) / 2;
	
	value = a*t1 + b*(t2 / 2) + c*((c1 + c2) / 2);    //2018-2019校赛 请修改此处的值 除非你愿意用这么菜的东西~

	if (side == 0)
		return value;
	else
		return -value;
}


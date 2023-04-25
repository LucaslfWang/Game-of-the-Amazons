#include "stdafx.h"
#include "YaMaXun.h"
#include "YaMaXunDlg.h"

int*CYaMaXunDlg::getnewscore(int x,int y,int temp[][10],int*score)
{
	int tempnew[10][10];
	int i,j;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			tempnew[i][j]=temp[i][j];
		}
	}
	
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if(tempnew[i][j]==1||tempnew[i][j]==2||tempnew[i][j]==3)
				continue;
			if(Is_OK(x,y,i,j,tempnew))
			{
				*score+=1;
                if(*score>5)
					return score;
				tempnew[i][j]=2;tempnew[x][y]=1;
				score=getnewscore(i,j,tempnew,score);
				return score;
			}
		}
	}
	return score;
				



}
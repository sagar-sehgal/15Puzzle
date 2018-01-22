#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int **A;
	int c,action,h,f;   //Cost = c, Actions{1=up,2=right,3=down,4=left}
	struct node *child[4];
	struct node *parent;
}node;


int misPlacedTiles(int **A)
{
	int i,j;
	int x = 0;
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			if(A[i][j] != i*3 + j+1)
				x++;
		}
	}

	return x;

}

int stepsCorrect(int **A)
{
	int i,j;
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			if(A[i][j] != i*3 + j+1)
			{
				x = A[i][j]/3;
				y = A[i][j]%3 - 1;
				p = x - i;
				q = y - j;
				if(p < 0)
					p = (-1)*p;
				if(q < 0)
					q = (-1)*q;

				z += p + q;

			}
		}
	}

	return z;

}


void solvePuzzle(struct node startState)
{
	struct node openlist[1000000], closedlist[1000000];

	openlist[0] = startState;	

	while

}




int main()
{
	int i;
	int **ex = (int **)malloc(3*sizeof(int *));
	
	= {{3,2,1}, {4,5,6}, {7,8,0}};`
	struct node startState;

	startState.A = ex;
	startState.c = startState.action = 0;
	startState.h = misPlacedTiles(startState.A);
	for(i=0; i<4; i++)
		startState.child[i] = NULL;
	startState.parent = NULL;

	solvePuzzle(startState);

	
	return 0;
}
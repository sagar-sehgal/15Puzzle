#include<stdio.h>
#include<stdlib.h>
const int lx=3;
typedef struct node
{
	int **A;
	int c,action,h,f;   //Cost = c, Actions{1=up,2=right,3=down,4=left}
	//f=c+h
	struct node *child[4];
	struct node *parent;
}node;
int misPlacedTiles(int **A)
{
	int i,j;
	int x = 0;
	for(i=0; i<lx; i++)
	{
		for(j=0; j<lx; j++)
		{
			if(A[i][j] != i*lx + j+1)
			{
				x++;
				//printf("%d***", A[i][j]);
			}
		}
	}
	return x - 1;
}
// int stepsCorrect(int **A)
// {
// 	int i,j;
// 	for(i=0; i<lx; i++)
// 	{
// 		for(j=0; j<lx; j++)
// 		{
// 			if(A[i][j] != i*lx + j+1)
// 			{
// 				x = A[i][j]/lx;
// 				y = A[i][j]%lx - 1;
// 				p = x - i;
// 				q = y - j;
// 				if(p < 0)
// 					p = (-1)*p;
// 				if(q < 0)
// 					q = (-1)*q;

// 				z += p + q;

// 			}
// 		}
// 	}

// 	return z;

// }
void solvePuzzle(struct node startState)
{
	struct node openlist[1000000], closedlist[1000000];
	openlist[0] = startState;	
	// while
}
int** get2dmat(int x){
	int **ex = (int**)malloc(x*sizeof(int*));
	for(int i=0;i<x;i++){
		ex[i]=(int*)malloc(x*sizeof(int));
	}
	return ex;
}
node* getNode(){ 
	node* n;
	n=(node*)malloc(sizeof(node));
	n->parent=NULL;
	n->child[0]=n->child[1]=n->child[2]=n->child[3]=NULL;
	return n;
}
void printNode(node *n){
	if(n==NULL){
		printf("NULL NODE\n");
		return;
	}
	for(int i=0;i<lx;i++){
		for(int j=0;j<lx;j++){

			printf("%d ",n->A[i][j]);
		}
		printf("\n");
	}
	printf("---------------------\n");
}
node* moveLeft(node* n,int i,int j){
	if(j==0){
		return NULL;
	}
	node *a=getNode();
	a->A=n->A;
	a->c=n->c+1;
	int x=a->A[i][j];
	a->A[i][j]=a->A[i][j-1];
	a->A[i][j-1]=x;
	a->h=misPlacedTiles(a->A);
	
	// printf("%d\n",a->h);
	a->f=a->c+a->h;
	a->parent=n;
	a->action=4;
	return a;
}
node* moveRight(node *n,int i,int j){
	if(j==lx-1){
		return NULL;
	}
	node *a=getNode();
	a->A=n->A;
	a->c=n->c+1;
	int x=a->A[i][j];
	a->A[i][j]=a->A[i][j+1];
	a->A[i][j+1]=x;
	a->h=misPlacedTiles(a->A);
	// printf("%d\n",a->h);
	a->f=a->c+a->h;
	a->parent=n;
	a->action=2;
	return a;
}
node* moveTop(node *n,int i,int j){
	if(i==0){
		return NULL;
	}
	node *a=getNode();
	a->A=n->A;
	a->c=n->c+1;
	int x=a->A[i][j];
	a->A[i][j]=a->A[i-1][j];
	a->A[i-1][j]=x;
	a->h=misPlacedTiles(a->A);
	// printf("%d\n",a->h);
	a->f=a->c+a->h;
	a->parent=n;
	a->action=1;
	return a;
}
node* moveDown(node *n,int i,int j){
	if(i==lx-1){
		return NULL;
	}
	node *a=getNode();
	a->A=n->A;
	a->c=n->c+1;
	int x=a->A[i][j];
	a->A[i][j]=a->A[i+1][j];
	a->A[i+1][j]=x;
	a->h=misPlacedTiles(a->A);
	// printf("%d\n",a->h);
	a->f=a->c+a->h;
	a->parent=n;
	a->action=3;
	return a;
}
void expand(node *n){
	int i,j;
	for( i=0;i<lx;i++){
		for( j=0;i<lx;j++){
			if(n->A[i][j]==0){
				break;
			}
		}
		if(n->A[i][j]==0){
			break;
		}
	}
	n->child[0]=moveTop(n,i,j);
	n->child[1]=moveRight(n,i,j);
	n->child[2]=moveDown(n,i,j);
	n->child[3]=moveLeft(n,i,j);
}

int main()
{
	int i;
	int **ex = get2dmat(lx);
	for(int i=0;i<lx;i++){
		for(int j=0;j<lx;j++){
			scanf("%d",&ex[i][j]);
		}
	}
	node *ss=getNode();
	ss->A=ex;
	ss->c=0;
	printf("%d\n",misPlacedTiles(ss->A));
	printNode(ss);
	expand(ss);
	return 0;
}
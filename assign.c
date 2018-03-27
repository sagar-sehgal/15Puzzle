#include<stdio.h>
#include<stdlib.h>
const int lx=4;
int nodeGen=0;
int stepCount=0;
int hno;
typedef struct node
{
	int **A;
	int c,action,h,f;   //Cost = c, Actions{1=up,2=right,3=down,4=left}
	//f=c+h
	struct node *child[4];
	struct node *parent;
}node;
typedef struct set{
	node *n;
	struct set *next;
}set;
int misPlacedTiles(int **A)
{
	int i,j;
	int x = 0;
	for(i=0; i<lx;i++)
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
int heuristic2(int **A)
{
	int i,j,x,y,p,q,z=0;
	for(i=0; i<lx; i++)
	{
		for(j=0; j<lx; j++)
		{
			if((A[i][j] != i*lx + j+1) && A[i][j]!=0)
			{
				if(A[i][j]%lx == 0)
				{
					x = A[i][j]/lx - 1;
					y = lx-1;
					p = x - i;
					q = y - j;
				}
				else
				{
					x = A[i][j]/lx;
					y = A[i][j]%lx - 1;
					p = x - i;
					q = y - j;
				}
				if(p < 0)
					p = (-1)*p;
				if(q < 0)
					q = (-1)*q;

				z += p + q;
				//printf("%d----%d%d\n", p+q, i, j);

			}
		}
	}

	return z;
}
int stepsCorrect(int **A){
	if(hno==1){
		return misPlacedTiles(A);
	}
	else if(hno==2){
		return heuristic2(A);
	}
}
// void solvePuzzle(struct node startState)
// {
// 	struct node openlist[1000000], closedlist[1000000];
// 	openlist[0] = startState;	
// 	// while
// }
int** get2dmat(int x){
	int **ex = (int**)malloc(x*sizeof(int*));
	for(int i=0;i<x;i++){
		ex[i]=(int*)malloc(x*sizeof(int));
	}
	return ex;
}
node* getNode(){ 
	nodeGen++;
	node* n;
	n=(node*)malloc(sizeof(node));
	n->parent=NULL;
	n->child[0]=n->child[1]=n->child[2]=n->child[3]=NULL;
	return n;
}
void printNode(node *n){
	if(n==NULL){
		return;
	}
	printNode(n->parent);
	// printf("%d=%d+%d\n",n->f,n->c,n->h);
	if(n->action==1)
		printf("action=Move Up\n");
	else if(n->action==2)
		printf("action=Move Right\n");
	else if(n->action==3)
		printf("action=Move Down\n");
	else if(n->action==4)
		printf("action=Move Left\n");
	
	for(int i=0;i<lx;i++){
		for(int j=0;j<lx;j++){
			printf("%d ",n->A[i][j]);
		}
		printf("\n");
	}
	stepCount++;
	printf("---------------------\n");
}
void copyArray(node* n,node *m){
	m->A=get2dmat(lx);
	for(int i=0;i<lx;i++){
		for(int j=0;j<lx;j++){
			m->A[i][j]=n->A[i][j];
		}
	}
}
node* moveLeft(node* n,int i,int j){
	if(j==0){
		return NULL;
	}
	node *a=getNode();
	copyArray(n,a);
	a->c=n->c+1;
	int x=a->A[i][j];
	a->A[i][j]=a->A[i][j-1];
	a->A[i][j-1]=x;
	a->h=stepsCorrect(a->A);
	
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
	copyArray(n,a);
	a->c=n->c+1;
	int x=a->A[i][j];
	a->A[i][j]=a->A[i][j+1];
	a->A[i][j+1]=x;
	a->h=stepsCorrect(a->A);
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
	copyArray(n,a);
	a->c=n->c+1;
	int x=a->A[i][j];
	a->A[i][j]=a->A[i-1][j];
	a->A[i-1][j]=x;
	a->h=stepsCorrect(a->A);
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
	copyArray(n,a);
	a->c=n->c+1;
	int x=a->A[i][j];
	a->A[i][j]=a->A[i+1][j];
	a->A[i+1][j]=x;
	a->h=stepsCorrect(a->A);
	// printf("%d\n",a->h);
	a->f=a->c+a->h;
	a->parent=n;
	a->action=3;
	return a;
}
void expand(node *n){
	int i,j;
	int flag=0;
	for(i=0;i<lx;i++){
		for(j=0;j<lx;j++){
			if(n->A[i][j]==0){
				flag=1;
				break;
			}
		}
		if(flag){
			break;
		}
	}
	// printf(">>>>%d-%d\n",i,j);
	n->child[0]=moveTop(n,i,j);
	n->child[1]=moveRight(n,i,j);
	n->child[2]=moveDown(n,i,j);
	n->child[3]=moveLeft(n,i,j);
}
set* getSet(){
	set* s;
	s=(set*)malloc(sizeof(set));
	s->next=NULL;
	s->n=NULL;
	return s;
}
set* addInClosedSet(set* start,node *n){
	set *s=getSet();
	s->n=n;
	if(start==NULL){
		return s;
	}
	else{
		set *x;
		x=start;
		while(x->next!=NULL){
			x=x->next;
		}
		x->next=s;
		return start;
	}
}
int checkCopyMat(int **a,int **b){
	for(int i=0;i<lx;i++){
		for(int j=0;j<lx;j++){
			if(a[i][j]!=b[i][j]){
				return 0;
			}
		}
	}
	return 1;
}
set* checkForBadCopySet(set *start,node *n){
	if(n==NULL || start==NULL){
		return NULL;
	}
	set *s;
	s=start;
	if(checkCopyMat(s->n->A,n->A)){
		if(s->n->f > n->f){
			set* q;
			q=s->next;
			free(q->n);
			q->n=n;
			return q;
		}
	}
	while(s->next!=NULL){
		if(checkCopyMat(s->next->n->A,n->A)){
			if(s->next->n->f > n->f){
				set* q;
				q=s->next;
				s->next=q->next;
				q->next=NULL;
				free(q->n);
				q->n=n;
				return q;
			}
		}
		s=s->next;
	}
	if(checkCopyMat(s->n->A,n->A)){
		if(s->n->f > n->f){
			set* q;
			q=s;
			s=q->next;
			q->next=NULL;
			free(q->n);
			q->n=n;
			return q;
		}
	}
	return NULL;
}
set* addInOpenSet(set *openSet,node *n){
	if(n==NULL){
		return openSet;
	}
	set *s=getSet();
	s->n=n;
	if(openSet==NULL){
		return s;
	}
	set *x;
	x=openSet;
	if(s->n->f < x->n->f){
		s->next=x;
		return s;
	}
	while(x->next!=NULL && (x->next->n->f < s->n->f)){
		x=x->next;
	}
	s->next=x->next;
	x->next=s;
	return openSet;
}
set* getBestNodeOpenSet(set *start){
	start=start->next;
	return start;
}
void printPathR(node *x){
	while(x->parent!=NULL){
		printNode(x);
		x=x->parent;
	}
}
set* checkAndAddOpenSet(set* openSet,node* n){
	if(n==NULL){
		return openSet;
	}
	if(openSet==NULL){
		openSet=addInOpenSet(openSet,n);
		return openSet;
	}
	set *s;
	s=openSet;
	set *q;
	if(checkCopyMat(s->n->A,n->A)){
		if(s->n->f > n->f){
			openSet=addInOpenSet(openSet,n);
			q=s;
			s=s->next;
			// printf("found really\n");
			return s;
		}
	}
	while(s->next!=NULL){
		if(checkCopyMat(s->next->n->A,n->A)){
			if(s->next->n->f > n->f){
				q=s->next;
				s->next=q->next;
				openSet=addInOpenSet(openSet,n);
				// printf("found really\n");
				return openSet;
			}
		}
		s=s->next;
	}
	if(s->next==NULL)
	{
		if(checkCopyMat(s->n->A,n->A)){
			if(s->n->f > n->f){
				q=s;
				s=q->next;
				openSet=addInOpenSet(openSet,n);
				// printf("found really\n");
				return openSet;
			}
		}
	}
	openSet=addInOpenSet(openSet,n);
	return openSet;
}
int getInvCount(int arr[])
{
    int inv_count = 0;
    for (int i = 0; i < lx * lx - 1; i++)
    {
        for (int j = i + 1; j < lx * lx; j++)
        {
            // count pairs(i, j) such that i appears
            // before j, but i > j.
            if (arr[j] && arr[i] && arr[i] > arr[j])
                inv_count++;
        }
    }
    return inv_count;
}
int findXPosition(int puzzle[lx][lx])
{
    // start from bottom-right corner of matrix
    for (int i = lx - 1; i >= 0; i--)
        for (int j = lx - 1; j >= 0; j--)
            if (puzzle[i][j] == 0)
                return lx - i;
}
int isSolvable(int puzzle[lx][lx])
{
    // Count inversions in given puzzle
    int invCount = getInvCount((int*)puzzle);
 
    // If grid is odd, return true if inversion
    // count is even.
    if (lx & 1)
        return !(invCount & 1);
 
    else     // grid is even
    {
        int pos = findXPosition(puzzle);
        if (pos & 1)
            return !(invCount & 1);
        else
            return invCount & 1;
    }
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
	int puzzle[lx][lx];
	for(int i=0;i<lx;i++){
		for(int j=0;j<lx;j++){
			puzzle[i][j]=ex[i][j];
		}
	}
	printf("Enter the Heuristic you want:");
	scanf("%d",&hno);
	int isSol=isSolvable(puzzle);
	if(isSol==0){
		printf("The current cnfiguration of puzzle is not solvable\n");
		return 0;
	}
	set *closedSet=NULL;
	set *openSet=NULL;
	node *ss=getNode();
	ss->A=ex;
	ss->c=0;
	ss->h=stepsCorrect(ss->A);
	ss->f=ss->c+ss->h;
	ss->action=0;
	node *x;
	x=ss;

	// int m;
	// set *e,*w;
	openSet=addInOpenSet(openSet,x);
	// e=openSet;
	// expand(e->n);
	// openSet=getBestNodeOpenSet(openSet);
	// closedSet=addInClosedSet(closedSet,x);
	// set *p,*o;
	// w=e;

	// e=w;
	// printf("%d\n",e->n->child[0]->f);
	// p=checkForBadCopySet(closedSet,e->n->child[0]);
	// if(p==NULL)
	// 	o=checkForBadCopySet(openSet,e->n->child[0]);
	// printf("1\n");
	// if(p==NULL && o==NULL)
	// 	openSet=addInOpenSet(openSet,e->n->child[0]);
	// p=checkForBadCopySet(openSet,e->n->child[1]);
	// if(p==NULL)
	// 	o=checkForBadCopySet(openSet,e->n->child[1]);
	// printf("2\n");
	// if(p==NULL && o==NULL)
	// 	openSet=addInOpenSet(openSet,e->n->child[1]);
	// p=checkForBadCopySet(openSet,e->n->child[2]);
	// if(p==NULL)
	// 	o=checkForBadCopySet(openSet,e->n->child[2]);
	// printf("3\n");
	// if(p==NULL && o==NULL)
	// 	openSet=addInOpenSet(openSet,e->n->child[2]);
	// p=checkForBadCopySet(openSet,e->n->child[3]);
	// if(p==NULL)
	// 	o=checkForBadCopySet(openSet,e->n->child[3]);
	// printf("4\n");
	// if(p==NULL && o==NULL)
	// 	openSet=addInOpenSet(openSet,e->n->child[3]);
	
	// e=openSet;
	// printf("openset\n");
	// while(e!=NULL){
	// 	printNode(e->n);
	// 	e=e->next;
	// }
	// e=closedSet;
	// printf("closedset\n");
	// while(e!=NULL){
	// 	printNode(e->n);
	// 	e=e->next;
	// }
	set *e,*w;
	while(openSet!=NULL){
		printf("Processing...Finding Solution %d\n",nodeGen);
		e=openSet;
		x=e->n;
		openSet=getBestNodeOpenSet(openSet);
		if(stepsCorrect(x->A)==0){
			// printf("$$$$$$$$$$$$$$$$$$\n");
			// printf("$$$$$$$$$$$$$$$$$$\n");
			printPathR(x);
			break;
		}
		printf("%d=%d+%d\n",x->f,x->c,x->h);
	
		expand(x);
		closedSet=addInClosedSet(closedSet,x);
		w=e;
		e=openSet;
		for(int i=0;i<4;i++){
			// if(stepsCorrect(x->A)==0){
			// 	printf("$$$$$$$$$$$$$$$$$$\n");
			// 	printf("$$$$$$$$$$$$$$$$$$\n");
			// 	printPathR(x);
			// 	return 0;
			// }
			e=checkForBadCopySet(closedSet,x->child[i]);
			if(e!=NULL){
				// set *q;
				// printf("Found in closed\n");
				openSet=addInOpenSet(openSet,e->n);
			}
			else if(e==NULL){
				// printf("found in open\n");
				openSet=checkAndAddOpenSet(openSet,x->child[i]);
				e=openSet;
				// printf("openset\n");
				// while(e!=NULL){
				// 	printf("%d\n",e->n->f);
				// 	e=e->next;
				// }
				// e=closedSet;
				// printf("closedset\n");
				// while(e!=NULL){
				// 	printNode(e->n);
				// 	e=e->next;
				// }
				// printf("^^^^^^^^^^^\n");
			}
		}
	}
	int closeCount=0,openCount=0;
	set *c=closedSet;
	while(c!=NULL){
		closeCount+=1;
		c=c->next;
	}
	printf("Number of nodes remaining in closed set=%d\n",closeCount);
	c=openSet;
	while(c!=NULL){
		openCount+=1;
		c=c->next;
	}
	printf("Number of nodes remaining in open set=%d\n",openCount);
	printf("Total Nodes Generated=%d\n",nodeGen);
	// printf("No. of steps=%d\n",stepCount);
	// printf("****************\n*****************\n");	
	// while(openSet!=NULL){
	// 	printNode(openSet->n);
	// 	openSet=openSet->next;
	// }

	// printf("****************\n*****************\n");
	// while(closedSet!=NULL){
	// 	printNode(closedSet->n);
	// 	closedSet=closedSet->next;
	// }
	// printf("%d\n", stepsCorrect(ss->A));
	return 0;
}

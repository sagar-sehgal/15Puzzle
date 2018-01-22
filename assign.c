#include<stdio.h>
typedef struct node{
	int a[3][3];
	int c,action,h,f;
	node *child[4];
	node *parent;
}node;
int main(){
	node *is;
	is=int node();
	node *fs;
	fs=int node();
	goal_check(is,fs);
	expand(cs)
	check_add_to_open(cs);
	
	return 0;
}
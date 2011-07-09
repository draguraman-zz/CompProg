#include <stdio.h>
#include <stdlib.h>

struct node;

typedef struct node {
	struct node *next;
	int n;
} node;

node nodes[100];
node  heads[100];
int loc[100];
int nblocks;

void ret(node*prev, node*cur)
{
	int a = cur->n;
	if (! prev) heads[a] = NULL;
	else {
		prev->next = NULL;

	}
	
	cur = cur->next;
	while (cur)
	{
		node* mynext = cur->next;
		a = cur->n;
		loc[a]=a;
		heads[a] = cur;
		cur=mynext; cur->next=NULL;
		}
}

node* get(int a, node**prev)
{
	node* myprev = NULL;
	*prev = NULL;
	node* p = heads[loc[a]];
	while(p){ 
		if (p->n == a) return p;
		*prev=  p;
		p=p->next;
		
	 }
}

void move(int a, int b, int isonto)
{

	if (loc[a] == loc[b]) return;
	int aloc = loc[a];
	int bloc = loc[b];
	node * aprev, acur, b
	if (isonto)
	{
		
		return; 
	}
}

int main()
{
	struct node* p;
	int i,j;
	

	scanf("%d",&nblocks);
	
	for (i=0;i < nblocks;i++)
	{
		loc[i] = i;
		heads[i] = &nodes[i];
		nodes[i].next = NULL;
		nodex[i].n = i;
		}
	while (2)
	{
		char cmd[100],  verb[100];
		int a,b;
		int onto;
		scanf("%s%d%s%d", cmd, &a, verb, &b);
		if (strcmp(cmd, "quit")==0) break;
		onto = (strcmp(verb, "onto")==0);
		if (strcmp(cmd, "move") == 0) move(a,b,onto);
		else pile(a,b,onto);
		}		

	for(i=0; i < nblocks;i++)
	{
		printf("%d:",i);
		p = heads[i];
		while(p)
		{
			printf(" %d", p->n);
			p =p->next;
		}
			printf("\n");
		}

}


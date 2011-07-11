/**
Algorithm:
IDA*

How to keep track of board state:
Use 64-bit bitmask! Each cell is 0-15 and there are 16 cells.
So in total 4*16 = 64 bits required! Just nice!

Use inversion method to check solvability. (Search wolfram)

Gotchas:
- Initial board already solved
- Out of memory for keeping track of large number of states
- Wasting precious time computing for non-solvable board and previously found
  states
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <set>

#define abs(a)  ((a) >= 0 ? (a): -(a))

typedef long long unsigned state_t;

const state_t goal = 0x0fedcba987654321;  // goal state

int sr,sc;            // starting row,col (zero-based)
state_t ss;           // starting state
char soln[999];       // backtracking solution string
std::set<state_t> f; // past board states

inline state_t set(state_t s, int r, int c, int n)
{
    int i = r*4 + c;
    state_t mask = (state_t)15 << (4*i);
   
    return ( s & (~mask)) | ((state_t)n << (4*i));
}

inline int get(state_t s, int r, int c )
{    
    int i = r*4 + c;  
    return ( s >> (4*i)) & 15;
}

inline int deltaCost(state_t s, int r, int c, int r2, int c2){
	int n = get(s, r2,c2);
	int tr = (n-1)/4;
	int tc = (n-1)%4;
	return abs(r-tr)+abs(c-tc) - abs(r2-tr)-abs(c2-tc);
}

// manhattan distance
 int cost(state_t s)
{
	int r,c;
	int d = 0;
	for (r = 0; r < 4; r ++){
		for (c = 0; c < 4; c++){
			int t = s & 15;		
			s >>= 4;
			if (t !=0 ) {
				int tr = (t-1) / 4;
				int tc = (t-1) % 4;
				d += abs(c-tc) +abs(r-tr); 
			}
		}
	}
	return (d);
}
/*
void print(state_t s )
{int i;
    for (i=0;i < 16; i ++){
        printf("%d ", s & 15);
        s >>= 4;
        if ((i+1) % 4 == 0) printf("\n");
    }
}

// search for the empty cell
void getpos(state_t s, int* r, int *c){
	int rr, cc;
	for (rr=0;rr< 4;rr++){
		for (cc=0;cc<4;cc++){
			if (get (s, rr,cc)==0){
				*r = rr; *c=cc; return;
			}
		}
	}
}*/

#define TRYIT(dr,dc,dir1) \
int newStartCost = startCost+deltaCost(s,r,c,r+dr,c+dc);\
if (depth + newStartCost <= costLimit ){\
	state_t news = set(set(s, r+dr, c+dc, 0), r,c, get(s, r+dr, c+dc)); \
	if (f.find(news) == f.end()){\
	  tries[numt].r = dr+r;\
	  tries[numt].c = dc+c;\
	  tries[numt].dir=dir1;\
	  tries[numt].newStartCost=newStartCost;\
	  tries[numt++].s=news;\
	  f.insert(news);\
	}\
}

bool dfs(int depth, int startCost, int costLimit, int r, int c, state_t s)
{
	struct {
		state_t s;
		int newStartCost;
		char dir;
		char r, c;
	} tries[4];
	int numt = 0;

	if (startCost == 0) {
		soln[depth]=0;
		printf("%s\n",soln);
		return true;
	}
	
         if (r){TRYIT(-1,0,'U');}
         if (r <= 2){TRYIT(1,0,'D');}
         if (c){TRYIT(0,-1,'L');}
         if (c <= 2){TRYIT(0,1,'R');}

	// loop to try the lowest cost first
	int i,j; int maxidx = 0;
	for (i=0;i < numt;i++){
		for (j = 0; j < numt;j++){
			if (tries[j].dir>=0 && tries[j].newStartCost < 
				tries[maxidx].newStartCost){
				maxidx = j;	
			}
		}
		
		soln[depth]=tries[maxidx].dir;

  		bool ok= dfs(depth+1,
			tries[maxidx].newStartCost,costLimit, 
			tries[maxidx].r, tries[maxidx].c, tries[maxidx].s);
		  if(ok)return true;
		  tries[maxidx].dir = -1;
		  maxidx = (maxidx+1)%numt;
	}

	return false;
}

bool doit()
{
	int startCost = cost(ss);

	for(int limit = startCost; limit <= 50; limit++){

		f.clear();
		f.insert(ss);
		bool ok= dfs(0, startCost, limit, sr, sc, ss);
		if (ok) return true; 
	}
	return false;
}

int main(int argc, char**argv)
{
	int i;
    int nu;
    scanf("%d", &nu);
    while (nu--){
        int c;
        ss = 0;
	int invSum = 0;
	int has[20] = {0};

        for (i = 0; i < 16; i ++){
            scanf("%d", & c );
            ss = set(ss, i/4, i %4, c);
		has[c] = 1;

		if (c == 0){ invSum += 1+i/4; sr = i/4; sc=i%4;}
		int j; 
		for (j=1;j < c; j ++){
			if (!has[j] ) invSum ++;
		}
		
        }

        if (invSum %2 || ! doit()) 
        	printf("This puzzle is not solvable.\n");
    }
}


/**
This currently still does not work! Too slow
Looks like we need IDA*

Algorithm:
Divide & conquer + BFS
This might not always produce the shortest solution due to the divide & conquer
phases.

Firstly, solve for the first row 1234
during the process, don't care about the other rows

Secondly, solve for the second row while not touching the first row

Thirdly, solve for the rest while not touching first and second rows!

How to keep track of board state.
Use 64-bit bitmask! Each cell is 0-15 and there are 16 cells.
So in total 4*16 = 64 bits required! Just nice!

Gotchas:
- Board already solved
- Out of memory for keeping track of large number of states
*/
#include <stdio.h>
#include <string.h>
#include <set>
#include <stdlib.h>
#include <deque>

typedef long long unsigned state_t;

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

int sr, sc; // start row,col

typedef struct
{
    char r, c; // row, col
    char dir; // move that leads to this state : L R U D
    char depth;
    int backidx;
    int idx;
    state_t s;
} move_t;

move_t moves[9999999];
int nummoves = 0;
state_t ss; // starting state
state_t goal;
std::deque<move_t*> q;
std::set<state_t> f;
char soln[999];
int sol = 0;

#define ML 1
#define MR 2
#define MD 4
#define MU 8

typedef state_t perm_t;

#define PP(dr,dc,dir1) \
    state_t news = set(set(m->s, m->r+dr, m->c+dc, 0), m->r,m->c, get(m->s, m->r+dr, m->c+dc)); \
    if (f.find(news) == f.end()){ \
    moves[nummoves].r = m->r + dr; \
    moves[nummoves].c = m->c + dc; \
    moves[nummoves].backidx = m->idx; \
    moves[nummoves].idx = nummoves; \
    moves[nummoves].dir = dir1; \
    moves[nummoves].s = news; \
        moves[nummoves].depth = m->depth+1; \
    nummoves++; \
    if (m->depth < 30)f.insert(news); \
    q.push_back(&moves[nummoves-1]) ; \
}
/*
void print(state_t s )
{int i;
    for (i=0;i < 16; i ++){
        printf("%d ", s & 15);
        s >>= 4;
        if ((i+1) % 4 == 0) printf("\n");
    }
}*/

void cant()
{
        printf("This puzzle is not solvable.\n");
}

// search for the empty cell
void getpos(state_t s, char* r, char *c){
	int rr, cc;
	for (rr=0;rr< 4;rr++){
		for (cc=0;cc<4;cc++){
			if (get (s, rr,cc)==0){
				*r = rr; *c=cc; return;
			}
		}
	}
}

void record(move_t*m) { 
	int idx = sol+m->depth-1; 
	do 
        { 
            if (m->dir < 0) break; 
            soln[idx] = m->dir;idx--; sol++; 
            m = &moves[m->backidx];
        }while (1) ;
}

move_t* find(state_t old, 
state_t mask, state_t g, perm_t perm){
 
    moves[0].s = old;
    getpos(moves[0].s, &moves[0].r,&moves[0].c);
    moves[0].dir = -1;
    moves[0].backidx = -1;
    moves[0].idx = 0;
    moves[0].depth=0;
    nummoves=1;
    q.clear();
    q.push_back(&moves[0]);
	int     solved=0;
	f.clear();
    f.insert(old);
	move_t *m=NULL;
	while (q.size()){
	  m=q.front();q.pop_front();
         if ((m->s & mask) == g){solved = 1; break;}
	if (m->depth > 51-sol) continue;
	 int cell_perm = get(perm, m->r, m->c);
         if (cell_perm & MU){PP(-1,0,'U');}
         if (cell_perm & MD){PP(1,0,'D');}
         if (cell_perm & ML){PP(0,-1,'L');}
         if (cell_perm & MR){PP(0,1,'R');}
	}

	if (!solved){
		cant(); return NULL;
	}
	
	record(m);
	return m;
}

void doit()
{
	sol = 0;
	move_t *m;
	m=&moves[0]; m->s =ss;	
	perm_t norm = ((perm_t) 0x9bbadffe << 32)|(perm_t) 0xdffe5776 ;
	perm_t perm = norm;
//	if (!(m=find(ss, 0xff, 0x21, perm))) return;

//	 perm = ((perm_t) 0x9bbadffe << 32) | (perm_t) 0xdf765676 ;
//	if (!(m=find(m->s, 0xffff, 0x4321, perm))) return;

//	 perm = ((perm_t) 0x9bbadffe << 32 )| (perm_t)0x57765776 ;
//	if (!(m=find(m->s, 0xffffff, 0x654321, perm))) return;

//	 perm = ((perm_t) 0x9bbadf76 << 32 )|(perm_t)0x56fe5776 ;
	if (!(m=find(m->s, 0xffffffff, 0x87654321, perm))) return;
	
//	 perm = ((perm_t) 0x9bba5776 << 32 )|(perm_t)0x57765776 ;
	if (!(m=find(m->s, (state_t)-1,goal, perm))) return;

	soln[sol]=0;
        printf("%s\n", soln);
}

int main()
{
    goal =0;
    int i,j,k;
    for (i=0;i< 4*4 - 1; i++){        
        goal = set(goal, i/4, i %4 , i+1); 
    }

    int nu;
    scanf("%d", &nu);
    while (nu--){
        int c;
        ss = 0;
        for (i = 0; i < 16; i ++){
            scanf("%d", & c );
            ss = set(ss, i/4, i %4, c);
            if ( c == 0){
                sr = i/4; sc = i%4;
            }
        }
        doit();
    }
}


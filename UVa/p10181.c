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

char soln[999];


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

void print(state_t s )
{int i;
    for (i=0;i < 16; i ++){
        printf("%d ", s & 15);
        s >>= 4;
        if ((i+1) % 4 == 0) printf("\n");
    }
}

void doit()
{
    std::deque<move_t*> q;
    std::set<state_t> f;

    moves[0].s = ss;
    moves[0].r = sr;
    moves[0].c = sc;
    moves[0].dir = -1;
    moves[0].backidx = -1;
    moves[0].idx = 0;
    moves[0].depth=0;
    nummoves=1;
    q.push_back(&moves[0]);
    int solved=0;
    move_t *m;
    f.insert(ss);
    while (q.size()){
    
         m = q.front(); q.pop_front();

         if (m->s ==goal){solved = 1; break;}

         if (m->depth > 46) continue;
         if (m->r > 0)
        {
            PP(-1,0,'U');
        }
         if (m->c > 0)
        {
            PP(0,-1,'L');
        }
         if (m->c < 3){ PP(0,1,'R');}
         if (m->r < 3){ PP(1,0,'D');}
    }
    printf("%d\n", f.size());
    if (solved){
        int sol = 0;
        do
        {

            if (m->dir < 0) break;
            soln[sol] = m->dir; sol++;
            m = &moves[m->backidx];
        }while (1);
        int i;
        for(i=0;i < sol; i++){
            printf("%c", soln[sol-1-i]);

        }
        printf("\n");
    }
    else {
        printf("This puzzle is not solvable.\n");
    }
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



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
    state_t s;
} move_t;


state_t ss; // starting state
state_t goal;

char soln[999];


#define PP(dr,dc,dir1) \
    state_t news = set(set(m->s, m->r+dr, m->c+dc, 0), m->r,m->c, get(m->s, m->r+dr, m->c+dc)); \
    if (f.find(news) == f.end()){ \
    move_t _m; q.push_back(_m); move_t&moves=q.back();\
        moves.r = m->r + dr; \
    moves.c = m->c + dc; \
    moves.dir = dir1; \
    moves.s = news; \
    moves.depth = m->depth+1; \
    if (m->depth < 30)f.insert(news); \
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
    std::deque<move_t> q;
    std::set<state_t> f;

    move_t _m;
    q.push_back(_m);
    move_t & moves = q.back();
    moves.s = ss;
    moves.r = sr;
    moves.c = sc;
    moves.dir = -1;
    moves.depth=0;
    int solved=0;
    move_t *m;
    f.insert(ss);
  int sol = 0;
    while (q.size()){
    
        move_t _mm = q.back();
         m = &_mm;

         q.pop_back();
         
         soln[m->depth] = m->dir;
        sol = m->depth+1;

         if (m->s ==goal){solved = 1; break;}

         if (m->depth <= 46){
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
    
    }
    
    if (solved){
/*        int sol = 0;
        do
        {

            if (m->dir < 0) break;
            soln[sol] = m->dir; sol++;
            m = &moves[m->backidx];
        }while (1); */
        int i;
        for(i=1;i < sol; i++){
            printf("%c", soln[i]);//sol-1-i]);

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



// incomplete, but basic idea is there

#include<string.h>
#include<stdio.h>
#include<vector>

using namespace std;

typedef long long ll;

struct node{
ll totalv; // total # of passengers for this node and its subtree
int idx, numchildren,cstart;};

struct ret{ll a, b, c;};

node nodes[3002]; // tree packed in an array
int v[3002]; // # of passengers for each station
int nstation;
vector<int> edges[3002];

ll themin; // answer
char vis[3002][3];

inline ll min(ll a, ll b){return a<b ? a : b;}
inline ll max(ll a, ll b){return a>b ? a : b;}

// contract is 1,2 or 3
// a, b, and c are the sum  for each contractor
// without consuming the curnode
void find(const node &curnode, int contract, ll a, ll b, ll c){
    int numchild=curnode.numchildren;
    ret my;
    ll max1;
//    if (vis[curnode.idx][contract-1]) return;
  //  vis[curnode.idx][contract-1] = 1;
    if (a >= themin) return;
    if (contract == 1){
        switch (numchild){
        case 0: return; // no valid arrangement
        case 1:{
            const node&childnode = nodes[ curnode.cstart ];
            // either contract #1 or #2 takes this childnode
            find(childnode,1, a+ v[curnode.idx],0,0); 
            find(childnode,2, a+v[curnode.idx],0,0);
            return;
        }
        case 2:{
            // scenarios:
            // 1] #1 takes the cur node, #2 and #3 take child
            // 2] #1 takes cur and left child, #2 take ..
            // 3] #1 takes cur and right child, #2 take...
            my.a = a+v[curnode.idx];
            my.b = nodes[curnode.cstart].totalv;
            my.c = nodes[curnode.cstart+1].totalv;
             max1 = max( my.a, max( my.b,my.c ) );
            if (max1 < themin){themin=max1;}
           
            // todo: missing cases here

            find(nodes[curnode.cstart+1], 2, my.a+my.b, 0, 0);
            find(nodes[curnode.cstart], 2, my.a+my.c, 0, 0);
            return ;
        }
        default:{
            int i,j;
            my.a = a+curnode.totalv;
            
            for(i=0;i<numchild;i++){
                my.a -= nodes[curnode.cstart+i].totalv;
                find(nodes[curnode.cstart+i], 1, my.a, 0, 0);
                find(nodes[curnode.cstart+i], 2, my.a, 0, 0);
                my.a += nodes[curnode.cstart+i].totalv;
            }
            
            for(i=0;i<numchild;i++){
                const node&child2 = nodes[curnode.cstart+i];
                my.b = child2.totalv;
                if (my.b>=themin) continue;
                for (j=i+1; j<numchild;j++){
                    const node&child3 = nodes[curnode.cstart+j];
                    my.c = child3.totalv;
                    my.a -= my.b+my.c;
                    max1 = max( my.a, max( my.b,my.c ) );
                    if (max1 < themin){themin=max1;}

                    // todo: missing cases here

                    my.a+= my.b+my.c;
                }
            }
            return;
        }
        }
    }
    if(b>=themin)return;
    switch(numchild){
    case 0: return ; // no valid arangement
    case 1: {
        my.a = a;
        my.b = b+v[curnode.idx];
        my.c = nodes[curnode.cstart].totalv;
         max1 = max( my.a, max( my.b,my.c ) );
        if (max1 < themin){themin=max1;}

        find(nodes[curnode.cstart], 2, a, my.b, 0);
        return;
    }
    
    default: {
                
            int i,j;
            my.b = b+curnode.totalv;
            my.a=a;
            for(i=0;i<numchild;i++){
                my.c = nodes[curnode.cstart+i].totalv;
                my.b -= my.c;             
                max1 = max( my.a, max( my.b,my.c ) );
                if (max1 < themin){themin=max1;}
                find(nodes[curnode.cstart+i],2, a, my.b, 0);
                my.b += my.c;
            }
        return;
    }
    }
}

volatile int cstart = 1;
char visited[3002];
ll build(int curnode, int nidx){
    if (visited[curnode]) return 0;
    visited[curnode]=1;

    nodes[nidx].idx=curnode;
    nodes[nidx].totalv = v[curnode];
    nodes[nidx].numchildren = 0;
    nodes[nidx].cstart = cstart;
    
    int i;
    int size = edges[curnode].size();

    for (i=0;i <  size; i++){
        int e = edges[curnode][i];
        if (visited[e]) continue;
        nodes[nidx].numchildren ++;
    }

    cstart += nodes[nidx].numchildren;
    int pp = 0;
    for (i = 0;i<size;i++){
        int e = edges[curnode][i];
        if (visited[e]) continue;
        nodes[nidx].totalv += build(e, nodes[nidx].cstart+ pp++);
    }
    return nodes[nidx].totalv;
}

int main(){
    scanf("%d",&nstation);
    int i,j;
    for (i=0;i<nstation;i++){
        scanf("%d", &v[i]);
    } int a,b;
    while (2==scanf("%d%d", & a, & b)){
        a--; b--;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    build(0,0);
    themin = ((unsigned long long)-1) >> 1;
    find(nodes[0], 1, 0, 0, 0);
    printf("%lld\n",themin);
}

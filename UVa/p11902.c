/**
Algorithm:
Brute force + Depth first search

Delete each node and check dominators
*/
#include<stdio.h>
#include<string.h>

int adj[102][102];
int n;
int nei[102];
char visited[102];

// simple DFS
void find(int cur){
    int i,j;
    if (visited[cur]) return;
        visited[cur] =1;
    int cnt = nei[cur];
    for (i=0;i<cnt;i++){
        int nxt = adj[cur][i];
        find(nxt);
    }
}

int dom[102][102];
char dash [402]; int cc=1;
int main(){
    int p;
    for (p=0;p<400;p++){
        dash[p]='-';
    }
    int nu;
    scanf ("%d", &nu);
    while (nu--){
        scanf("%d", &n);
        int i,j; memset(nei,0,sizeof(nei));
        for (i=0;i<n;i++){
            for (j=0;j<n;j++){
                int k; scanf ("%d", &k);
                if (k==0|| i==j) continue;
                adj[i][nei[i]++] = j;
            }
        }

        // find all nodes reachable from 0
        char reach[102];
        memset(visited,0,sizeof(visited));
        find(0);
        memcpy(reach,visited, sizeof(reach));
        memset(dom,0,sizeof(dom));

        // delete each node and find nodes that are reachable
        for (i=0;i< n;i++){
            if (! reach[i]) continue;

            // "delete" node i
            memset(visited,0,sizeof(visited));
            visited[i]=1;find(0);visited[i]=0;    

            // if node p is reachable but not now, then 
            // node i is dominator
            for (int p = 0; p <n;p++){
                if (reach[p] && !visited[p])
                {dom[i][p]=1;}
            }
        }
printf("Case %d:\n",cc++);
        for (i=0;i<n;i++){
            dash[2*n-1]=0;
            printf("+%s+\n",dash);
            dash[2*n-1]='-';
            for (j=0;j<n;j++){
              printf("|%c", dom[i][j] ? 'Y' :'N');  
            }
            printf("|\n");

        }
            dash[2*n-1]=0;
            printf("+%s+\n",dash);
            dash[2*n-1]='-'; //printf("\n");
    }
}


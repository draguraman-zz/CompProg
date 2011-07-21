#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char board[16][16];
char d1[50];
char d2[50];
char col[50];
int cnt;
int n;

void find(int r)
{
    struct {int r, j;} stk[100];
    int nstk=0;
    int i,j;
    j=0;

    while (1){
        for (; j < n; j++){
            if (col[j]||d1[r+j] || d2[n+r-j] || board[r][j]=='*') continue;
            col[j] = 1;
            d1[r+j] = 1;
            d2[n+r-j] = 1;

            stk[nstk].r = r;
            stk[nstk].j = j;
            nstk++;
            r++;
            if (r< n){
                j = -1; continue;
            }

                cnt++; 
                nstk--;
                r--;

            col[j] = 0;
            d1[r+j] = 0;
            d2[n+r-j] = 0;
        }

                if (nstk==0)return;
                nstk--;
                j=stk[nstk].j;
                r=stk[nstk].r;
            col[j] = 0;
            d1[r+j] = 0;
            d2[n+r-j] = 0;
            j++;
    }
}

int main(){int cc=1;
while (1){
    scanf("%d", &n);
    if (!n) break;
    int i,j;
    for(i=0;i<n;i++){
        scanf("%s", &board[i][0]);
    }
    cnt = 0;
    find(0);
    printf("Case %d: %d\n",cc,cnt);cc++;
}
}


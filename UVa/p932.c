/**
 * Algorithm:
 * Brute force
 *
 * For each queen, try removing it and put in another position.
 */
#include<stdio.h>
#include<string.h>
int grid[33][33];
int row[32];
int col[32];
int dia1[100];
int dia2[100];
int n;

// true true if conflict
bool put(int r, int c){
    row[r]++; col[c]++;
    dia1[r+c]++;
    dia2[n-r+c]++;
    grid[r][c]++;
    return row[r]>1 ||
        col[c]>1||dia1[r+c]>1||dia2[n-r+c]>1;
}

inline void unput( int r, int c ){
    row[r] --; col[c] --;

    dia1[r+c]--;
    dia2[n-r+c]--;
    grid[r][c]--;
}

// true if ok
 bool chk(){
    int i;
    for (i=0;i<n;i++)
    {
        if ( row[i]>1 ||
        col[i]>1) return false;
    }
    for (i=0; i<=2*n;i++) 
    {
            if (dia1[i] >1||dia2[i]>1) return false;
    }
    return true;
}

int qr[33];
int qc[33];
#define cls(p) memset(p,0,sizeof(p))
int main(){
    while (7){
        cls(row);cls(col);cls(dia1);cls(dia2);cls(grid);
        int k =scanf ("%d", &n);if(k !=1) break;
        int i,j; bool con=false;
        int qn=0;
        for(i=0;i<n;i++){
            char s[90];
            scanf("%s", s);
            for (j=0;j<n;j++){
                if ( s[j] == 'X'){
                    bool bb = put(i,j);
                    con = bb || con;
                    qr[qn]=i; qc[qn++]=j;
                }
            }
        }
        if (!con){ printf("YES\n\n");continue; }

        printf("NO\n"); bool solved=false;
        
        for (i=0;i<n;i++){
            int r = qr[i]; int c = qc[i];
            unput(r,c);
            int  k; ;
            for (j=0;j<n;j++){
                if (row[j]) continue;
                for(k=0;k<n;k++){
                    put(j,k);
                    if ( chk()){
                        j=i=n+1;solved=true;break;}
                    unput(j,k);
                }
            }
            if (solved)break;
            put(r,c);
        }
        if (!solved){ printf("NO\n\n");continue; }
        
        printf("YES\n");
        for (i=0;i<  n;i++){
            for(j=0;j<n;j++){
                if (grid[i][j]) printf("X");
                else printf("0");
            }
            printf("\n");
        }printf("\n");
    }
}



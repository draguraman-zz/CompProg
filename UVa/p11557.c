#include<map>
#include<string.h>
#include<stdio.h>
#include<set>
#include<vector>
#include<string>
using namespace std;

map<string,int> lines;
vector<int >  frags[102]; 
int nfrags;
vector<int> prog;
char fnames[102][256];


void doit(){
    vector<int> matched;
    int max = 0;
    int i,j; int progsize = prog.size();
    for (i=0; i < progsize; i++){
        int cur = prog[i];
        for (j=0;j <nfrags;j++){
            const vector<int>& f = frags[j];
            int flen = f.size();
            for (int k = 0; k < flen;k++){
                int l=0; 
                while (k+l<flen && 
                    i+l < progsize&& f[k+l] == prog[i+l])l++;
                if (l > max){  matched.clear(); 
                        matched.push_back(j);max=l;}
               else if (l==max){ matched.push_back(j); }
            }
        }
    }
    printf("%d",max);
    for (i=0; i < matched.size();i++){
        printf(" %s", fnames[matched[i]]);
    }
    printf("\n");
}
char line[256];
int u=0;
void read(vector<int>& pp){
pp.clear();
        while (9){
            gets(line); if (strcmp(line, "***END***")==0) break; int i;
            int store = 0;
            for ( i = 0 ; line[i];i++){
                char c = line[i];
                if (c!=' ')break;
            }
            if (line[i] == 0) continue;
            for ( ; line[i];i++){
                char c = line[i];
                line[store++]=c;
                if (c == ' '){i++;
                    while (line[i]== ' ')i++;
                   i--;
                }
            }
            if (line[store-1] == ' ') line[--store]=0;
            else line[store]=0;
            string ll(line);
            int lidx = lines[ll];
            if (lidx==0) lines[ll] =lidx= ++u;
            lidx--;
            pp.push_back(lidx);
        }
}
int main(){
    while (90){
     int k =    scanf("%d",&nfrags);
     if (k!= 1) break;
        gets(line); 
        u=0; lines.clear();
        for (int j = 0; j < nfrags;j++){
            gets( fnames[j]);
            read(frags[j]);    
        }
        read(prog); doit();    }
}




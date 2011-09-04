#include<string.h>
#include<stdio.h>

// 0 -> correct order
// 1 -> each word reversed
char in[2][5010]; // all words without spaces
int cnt [600]; // word len
int pos[600]; // starting idx of word i^th

typedef struct{
    int start;
    int mid1;
    int mid2;
    int end;
    int len;
    int sel; // 0 or 1
    int 
} d;
d f[2][5010]; // longest palin in substr 0..i
//

void doit(){

    
}



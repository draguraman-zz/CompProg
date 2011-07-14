

#include<map>
#include<queue>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
input:
#no .of topic
#id #requests #time-for-first #time-to-service $time-between
#no. of personnel
#person-id #no.-topics  [topic ids ... high to low prio]
0
*/


std::map<int,int> timeneed;

typedef struct
{
    int time; // time at which this req appears , minutes since start
    int id;
} req_t;

class reqcomp
{
    public: bool operator()(const req_t &a,const req_t&b)
    const {
        return a.time > b.time;
    }
};

std::priority_queue<req_t, std::vector<req_t>, reqcomp> q;

typedef struct
{
    int id;
    int last_job; // time of last job scheduled time
    int free; // time at which person is free
    int topics[999999]; // temrinated by -1
    
} person_t;

person_t persons[10];
int numpersons;

/*
int reqcomp(const void * a, const void * b)
{
    return ((req_t*)a)->time - ((req_t*)b)->time;
}*/

int select (int rid)
{
    int id = reqs[rid].id;
    int time = reqs[rid].time;
    int i,j;
    int idx = -1;
    int prio = 0x7fffffff;
    for(i=0;i < numpersons;i++){
        if (persons[i].free <= time)
        {
            // if per is free, grab his prio forthis topic
            for (j = 0;-1!= persons[i].topics[j];j++){
                if (persons[i].topics[j] == id)
                {
                    if (j < prio){ idx = i; prio = j; }
                    else if (j == prio )
                    {
                        if (persons[i].last_job < persons[idx].last_job)
                        {
                            idx=i;
                        }
                        else if(persons[i].last_job==persons[idx].last_job)
                        {
                                   
                            if (i < idx){ idx=i;  }
                        }
                    }break;
                }
            }
        }
    }

    return idx;
}

int handle(int rid){
    int i,j;
    int id = reqs[rid].id;
    int time = reqs[rid].time;

}

int sc=1;

int main()
{
    while (1)
    {
    int numtopics;
    scanf("%d", &numtopics);
    if (numtopics == 0) break;

    numpersons=0;
    numreq=0;
    total=0;
    int i,j,k;
    timeneed.clear();
    q.clear();
    for (i=0;i < numtopics; i++){
        int id, req, first, need, btw;
        scanf("%d%d%d%d%d", &id, &req, &first, &need, &btw);
        timeneed[id]=need;
        for (j = 0; j <req;j++){
            reqs[numreq].id =id;
            reqs[numreq].time = first;
            first += need+btw;
            numreq++;
        }
    }
    scanf("%d",&numpersons);
    for (i=0;i < numpersons;i++){
        int id, num;
        scanf("%d%d",&id,&num);
        persons[i].id=id;
        persons[i].free = persons[i].last_job=0;
        for (j=0;j<num;j++){
            scanf("%d",& persons[i].topics[j]);
        }
        persons[i].topics[j] = -1;

    }

// todo: what if two  requests of diff type appear?

    qsort( reqs, numreq, sizeof(req_t), reqcomp);

    int delta = 0; // time to push back each req by
    for (i=0;i<numreq;i++){
        int pid = select(i);

        int time = reqs[i].time+delta;
        int id = reqs[i].id;
        if (pid >=0){
            persons[pid].last_job = time;
            persons[pid].free = time + timeneed[id];
        }
        else{
            // no one is free or no suitable per found
            delta+=handle(i);
        }
    }

    int max = 0;
    for (i=0;i<numpersons;i++){
        if (persons[i].free > max) max = persons[i].free;
    }

    printf("Scenario %d: All requests are serviced within "
    "%d minutes.\n", sc, max); sc++;
}
}




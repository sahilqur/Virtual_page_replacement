#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
using namespace std;

int lru_clock(int ibuf[BUFSIZ],int len,int frames) {
int queue[frames][2],pos=0,flag=0,pointer=0,pagerep=0;
for(int i=0;i<frames;i++) {
    queue[i][0]=-1;
    queue[i][1]=0;
}

for(int i=0;i<len;i++) {
    pos=0;
    flag=0;
    for(int j=0;j<frames;j++) {
        if(ibuf[i]==queue[j][0]) {
                flag=1;
                pos=j;
                break;
        }
    }
    if(flag==1) {     // if element is present in queue
      	queue[pos][1]=1;
    }
    else if(flag!=1 && queue[frames-1][0]==-1) { // if ele is not in q and l<f
        queue[pointer][0]=ibuf[i];
        queue[pointer][1]=0;
        pointer=(pointer+1)%frames;
    }
    else {    				// page rep condition
       if(queue[pointer][1]==0) {
           queue[pointer][0]=ibuf[i];
           queue[pointer][1]=0;
           pagerep=pagerep+1;
	   pointer=(pointer+1)%frames;
           
           
       }
       else {
           while(queue[pointer][1]!=0) {
               queue[pointer][1]=0;
               pointer=(pointer+1)%frames;
           }
           queue[pointer][0]=ibuf[i];
           queue[pointer][1]=0;
	   pagerep=pagerep+1;
           pointer=(pointer+1)%frames;
           
          
       }
    }
}
return pagerep; 
}           



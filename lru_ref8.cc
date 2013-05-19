#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
using namespace std;

int lru_ref8(int ibuf[BUFSIZ],int len,int frames) {
int arr[frames][2],pos=0,flag=0,pointer=0,pagerep=0,min=0;
for(int i=0;i<frames;i++) {
    arr[i][0]=-1;
    arr[i][1]=0x00;
}
for(int i=0;i<len;i++) {
    pos=0;
    flag=0;
    min=arr[0][1];
    for(int j=0;j<frames;j++) {
        arr[j][1]=arr[j][1]>>1;
    }
    for(int j=0;j<frames;j++) {
        if(ibuf[i]==arr[j][0]) {
                flag=1;
                pos=j;
                break;
        }
    }
    if(flag==1) {     // if element is present in queue add 1 MSB
      	arr[pos][1]=arr[pos][1]|0x80;
    }
    else if(flag!=1 && arr[frames-1][0]==-1) { // if ele is not in q and l<f
        arr[pointer][0]=ibuf[i];
        arr[pointer][1]=arr[pointer][1]|0x80;
        pointer=(pointer+1)%frames;
    }
    else {    				// page rep condition
        for(int j=0;j<frames;j++) {
            if(min>arr[j][1]) {
                 min=arr[j][1];
            }
        }
        for(int j=0;j<frames;j++) {
            if(arr[j][1]==min) {
                 pos=j;
                 break;
            }
        }
        arr[pos][0]=ibuf[i];
        arr[pos][1]=0x80;       
        pagerep=pagerep+1;
    }
}
return pagerep; 
}           



#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
using namespace std;

int optimal(int ibuf[BUFSIZ],int len,int frames) {
int arr[frames],pos=0,flag=0,pointer=0,pagerep=0,pos1=0,posarr[frames];
int max=0,flag1=0,q=0,pos2=0;
for(int i=0;i<frames;i++) {
    arr[i]=-1;
}

for(int i=0;i<len;i++) {
    pos=i;flag=0;max=0;flag1=0;pos1=0;pos2=0;
    for(int j=0;j<frames;j++) {
        if(ibuf[i]==arr[j]) {
                flag=1;
                 break;
        }
    }
    if(flag!=1 && arr[frames-1]==-1) { // if ele is not in q and l<f
        arr[pointer]=ibuf[i];
        pointer=(pointer+1)%frames;
    }
    else if(flag!=1 && arr[frames-1]!=-1) {    	     // page rep condition
        for(int k=0;k<frames;k++) {
             pos1=-1;
             for(int m=pos+1;m<len;m++) {
                    if(arr[k]==ibuf[m]) {
                         pos1=m;
                         break;
                    }
             }
             posarr[k]=pos1;
             if(max<pos1) { 
                 max=pos1;
             }
        }
        for(int k=0;k<frames;k++) {
            if(posarr[k]==-1) {
                   pos1=k;                   
                   flag1=1;
                   break;
            }
        }
        for(int k=0;k<frames;k++) {
            if(posarr[k]==max) {
                   pos2=k;                   
                   break;
            }
        }
        
        if(flag1==1) {
           arr[pos1]=ibuf[i];
           pagerep=pagerep+1;
        }          
        else {
          arr[pos2]=ibuf[i];
          pagerep=pagerep+1;
        }
    }
    else {
       q=0;
    }
}
return pagerep; 
}           









#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
using namespace std;



int fifo(int ibuf[BUFSIZ],int len,int frames) {
int arr[frames],flag=0;
int pointer=0,page_rep=0;
for(int i=0;i<frames;i++)
arr[i]=-1;

for(int i=0;i<len;i++) {
    flag=0;	
    for(int k=0;k<frames;k++) {
	 if(ibuf[i]==arr[k]) {
	      flag=1;
	 }
    }
    if(flag!=1) {
	 if(arr[pointer]==-1) {
             arr[pointer]=ibuf[i];
	     pointer=(pointer+1)%frames;
	 }
	 else {
	    arr[pointer]=ibuf[i];
            pointer=(pointer+1)%frames;
            page_rep=page_rep+1;
         }
     }
}
return page_rep;
}




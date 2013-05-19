#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

using namespace std;

int lfu(int ibuf[BUFSIZ],int len,int frames) {
int arr[BUFSIZ],pagetable[BUFSIZ][2],flag=0,pos=0,page=0,min=0,flag1=0,pointer=0,count=0;
int pagerep=0,m=0,ele=0;
for(int i=0;i<frames;i++) {
    arr[i]=-1;
}

for(int i=0;i<BUFSIZ;i++) {
    pagetable[i][0]=-1;
	pagetable[i][1]=0;
}

for(int i=0;i<len;i++) {
    flag=0;	
    flag1=0;
    pos=0;
    page=0;
    ele=0;
	min=0;
	count=0;
    for(int k=0;k<frames;k++) {
	 if(ibuf[i]==arr[k]) {
              flag=1;
       	      break; 
         }             
    }
    if(flag!=1 && arr[0]==-1) {
       arr[pointer]=ibuf[i];
	   pagetable[0][0]=ibuf[i];
	   pagetable[0][1]=pagetable[0][1]+1;
       pointer=(pointer+1)%frames;
	}

    else if(flag!=1 && arr[frames-1]==-1) {    //when l<f
       arr[pointer]=ibuf[i];
	   for(int j=0;pagetable[j][0]!=-1;j++) {
		   pos=j;
	   }
	   pagetable[pos][0]=ibuf[i];
	   pagetable[pos][1]=pagetable[pos][1]+1;
       pointer=(pointer+1)%frames;
    }

    else if(flag!=1 && arr[frames-1]!=-1) {  //page rep 
   	   for(int j=0;pagetable[j][0]!=-1;j++) {
             if(arr[0]==pagetable[j][0]) {
                min=pagetable[j][1];
                break;
             }
	   }
	   for(int j=0;j<frames;j++) {
		   for(int k=0;pagetable[k][0]!=-1;k++) {
			   if(arr[j]==pagetable[k][0]) {
				   if(min>=pagetable[k][1]) {
					   min=pagetable[k][1];
				   }
			   }
		   }
	   }
	   for(int j=0;j<frames;j++) {
		   for(int k=0;pagetable[k][0]!=-1;k++) {
			   if(arr[j]==pagetable[k][0]) {
				   if(pagetable[k][1]==min) {
					   page=pagetable[k][0];
					   count=count+1;
				   }
			   }
		   }
	   }
	   if(count!=1) {
		   flag1=0;
		   for(int j=0;pagetable[j][0]!=-1;j++) {
			   if(arr[pointer]==pagetable[j][0]) {
				   if(pagetable[j][1]==min) {
					   flag1=1;
					   break;
				   }
			   }
		   }
		   if(flag1==1) {
               arr[pointer]=ibuf[i];
			   pointer=(pointer+1)%frames;
		       pagerep=pagerep+1;
		   }
		   else {
			   flag1=0;
			   for(int j=0;j<frames;j++) {
		           for(int k=0;pagetable[k][0]!=-1;k++) {
			             if(arr[j]==pagetable[k][0]) {
				              if(pagetable[k][1]!=min) {
								  pointer=(pointer+1)%frames;
							  }
							  else {
								  flag1=1;
							  }
						 }
				   }
				   if(flag1==1) {
					   break;
				   }
			   }
			   arr[pointer]=ibuf[i];
			   pointer=(pointer+1)%frames;
		       pagerep=pagerep+1;
		   }
	   }
	   else {		 
	     for(int j=0;j<frames;j++) {
		   if(arr[j]==page) {
			   arr[j]=ibuf[i];
			   pagerep=pagerep+1;
			   pointer=(j+1)%frames;
			   break;
		   }
	     }
	   }
	   flag1=0;
	   for(int j=0;pagetable[j][0]!=-1;j++) {
		   if(ibuf[i]==pagetable[j][0]) {
			   pagetable[j][1]=pagetable[j][1]+1;
			   flag1=1;
			   break;
		   }
	   }
	   pos=0;
	   if(flag1!=1) {
		   for(int j=0;pagetable[j][0]!=-1;j++) {
			   pos=j;
		   }
		   pagetable[pos+1][0]=ibuf[i];
		   pagetable[pos+1][1]=pagetable[pos+1][1]+1;
	   }
	}
	else {
		for(int j=0;pagetable[j][0]!=-1;j++) {
			if(pagetable[j][0]==ibuf[i]) {
				pagetable[j][1]=pagetable[j][1]+1;
				break;
			}
		}
	}
}
return pagerep;
}



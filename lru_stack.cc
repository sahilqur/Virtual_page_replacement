#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
using namespace std;


struct node {
    int data;
    node *next;
};

int length(node *);


int lru_stack(int ibuf[BUFSIZ],int len,int frames) {
int flag=0,pos=0,pos1=0,pos2=0,pagerep=0;
node *pointer,*pointer1,*head=NULL;
for(int i=0;i<len;i++) {
    flag=0;
    pos=0;
    pos1=0;
    pos2=0;
    pointer=head;
    pointer1=head;
    while(pointer!=NULL) {
	if(pointer->data==ibuf[i]) {
		flag=1;		
                break;        
        }
        pos=pos+1;
        pointer=pointer->next;
    }
    pointer=head;
    if(head==NULL) {     // if head is null       
       node *newnode;
       newnode=new node;
       newnode->data=ibuf[i];
       head=newnode;
       newnode->next=NULL;
    }
    else if(flag!=1 && length(pointer)<frames) {  // if element is not present and l<fr       
       node *newnode;
       newnode=new node;
       newnode->data=ibuf[i];
       newnode->next=head;
       head=newnode;
    }
    //pointer=head;
    else if(flag==1 && head->data!=ibuf[i]) {        // if element is present       
       while(pos1!=pos-1) {
              pointer=pointer->next;
	      pos1=pos1+1;
       }       
       while(pos2!=pos) {
	      pointer1=pointer1->next;
              pos2=pos2+1;
       }
       pointer->next=pointer1->next;
       pointer1->next=head;
       head=pointer1;
    }
    else if(flag==1 && head->data==ibuf[i]) {
      head->data=ibuf[i];
    }
    //pointer=head;
    else {        // element is not in list and len>frames      
      while(pointer1->next!=NULL) {
	   pointer=pointer1;
	   pointer1=pointer1->next;
      }
      pointer->next=NULL;
      node *newnode;
      newnode=new node;
      newnode->data=ibuf[i];
      newnode->next=head;
      head=newnode;
      pagerep=pagerep+1;
    }
}               
return pagerep;
}

int length(node *l) {
int lil=0;
while(l!=NULL) {
    lil=lil+1;
    l=l->next;
}
return lil;
}








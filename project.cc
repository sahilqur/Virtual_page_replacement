#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/time.h>
#include"lru_clock.cc"
#include"lru_stack.cc"
#include"fifo.cc"
#include"lru_ref8.cc"
#include"optimal.cc"
#include"lfu.cc"
using namespace std;

int main(int argc, char *argv[]) {
system("clear");
timeval tv,tv1,tv2,tv3,tv4,tv5,tv6;
int frames=5;
unsigned int opt_time=0,fif_time=0,lru_c_time=0,lru_s_time=0,lru_r_time=0,lfu_time=0;  
int fif_rep=0,lfu_rep=0,lru_s_rep=0,lru_c_rep=0,lru_r_rep=0,opt_rep=0;
char *r,ch,c;
int prev_ind,flag=0,ibuf[BUFSIZ],option=0,sc_op=1,temp=0,len=0,flag1=0,flag2=0,flag3=0;
char buf[BUFSIZ];
while(prev_ind = optind, (c =  getopt(argc, argv, ":h:f:r:i:")) != EOF) {
   if ( optind == prev_ind + 2 && *optarg == '-' ) {
        c = ':';
        -- optind;
   }
        switch (c)
        {
             case 'h':
                 option=1;
                 break;

             case 'f':
      		 frames=atoi(optarg);
                 break;

             case 'r':
                 if(*optarg=='F') 
		    sc_op=1;
		 else if(*optarg=='L' && *(optarg+1)=='F')
		    sc_op=2;
		 else if(*(optarg+4)=='S')
		    sc_op=3;
		 else if(*(optarg+4)=='C')
		    sc_op=4;
		 else if(*(optarg+4)=='R')
		    sc_op=5;
		 else
		    sc_op=6;
                 break;

             case 'i':
                 flag1=1;
		 r=optarg;
		 for(int t=0;t<100;t++) {
		       if(*(r+t)=='.') {
		          flag=1;					       
		       }	
		 }
	         if(flag==1) {
		       FILE *file;
		       file=fopen(optarg,"r");
		       if(!file) {
			  cout<<"cannot open file"<<optarg;
			  break;
		       }
                       fgets(buf,sizeof(buf),file);
		       int r=0;
  	              while(buf[r]!='\n') 
			{
			     temp=0;
			     if(isspace(buf[r])) {
				r=r+1;
			     }

			     else if(buf[r] >='0' && buf[r]<='9') {
				while(!isspace(buf[r])) {
				    temp=temp*10 + (buf[r]-'0');
				    r=r+1;
				}
				ibuf[len]=temp;
				len=len+1;
			     }

			     else {
				cout<<"invalid sequence";
				flag2=1;
				break;
		             }
			}
                  }
		 break;   
		
 
    	     case ':':
                 cerr << "Missing option." << endl;
                 exit(1);
                 break;
       }
}

if(flag1!=1) {
  cout<<"enter page sequence"<<endl;
  ch=getchar(); 
  while(ch!='\n') {
     temp=0;
     flag=0;
     if(isspace(ch)) {
         ch=getchar();
     }

     else if(ch >='0' && ch<='9') {
	while(!isspace(ch) && ch!='\n') {
	    if(!(ch >='0' && ch<='9')) {
                cout<<endl<<"invalid sequence"<<endl;
                flag3=1;
                break;
            }
	    temp=temp*10 + (ch-'0');
            ch=getchar();
      	}
        if(flag3==1) {
          break;
        }
	ibuf[len]=temp;
	len=len+1;
     }
     else {
	cout<<"invalid sequence"<<endl;
	break;
     }
   }
}

gettimeofday(&tv, NULL);
opt_rep=optimal(ibuf,len,frames);
gettimeofday(&tv1, NULL);
opt_time=tv1.tv_usec-tv.tv_usec;

if(flag2!=1 && flag3!=1) {
if(option==1) {
  gettimeofday(&tv, NULL);
  fif_rep=fifo(ibuf,len,frames);
  gettimeofday(&tv1, NULL);
  fif_time=tv1.tv_usec-tv.tv_usec;
  cout<<endl<<"Page replacement with FIFO "<<fif_rep;
  cout<<endl<<"Page replacement with optimal "<<opt_rep;
  cout<<endl<<"%page replacement penalty using FIFO "<<(float(fif_rep-opt_rep)/opt_rep)*100<<"%";
  cout<<endl<<"Total time to run FIFO "<<fif_time<<" msec";
  cout<<endl<<"Total time to run optimal algo "<<opt_time<<" msec";
  if(fif_time>opt_time) {
        cout<<endl<<"FIFO is "<<(float(fif_time-opt_time)/opt_time)*100<<"% slower than optimal algorithm";
  }
  else {
        cout<<endl<<"FIFO is "<<(float(opt_time-fif_time)/opt_time)*100<<"% faster than optimal algorithm";
  }

  gettimeofday(&tv, NULL);
  lfu_rep=lfu(ibuf,len,frames);
  gettimeofday(&tv1, NULL);
  lfu_time=tv1.tv_usec-tv.tv_usec;
  cout<<"\n\nPage replacement with LFU "<<lfu_rep;
  cout<<"\nPage replacement with optimal "<<opt_rep;
  cout<<"\npage replacement penalty using LFU "<<(float(lfu_rep-opt_rep)/opt_rep)*100<<"%";
  cout<<"\nTotal time to run LFU "<<lfu_time<<" msec";
  cout<<"\nTotal time to run optimal algo "<<opt_time<<" msec";
  if(lfu_time>opt_time) {
        cout<<"\nLFU is "<<(float(lfu_time-opt_time)/opt_time)*100<<"% slower than optimal algorithm";
  }
  else {
        cout<<"\nLFU is "<<(float(opt_time-lfu_time)/opt_time)*100<<"% faster than optimal algorithm";
  }
  
  gettimeofday(&tv, NULL);
  lru_s_rep=lru_stack(ibuf,len,frames);
  gettimeofday(&tv1, NULL);
  lru_s_time=tv1.tv_usec-tv.tv_usec;
  cout<<"\n\nPage replacement with LRU Stack "<<lru_s_rep;
  cout<<"\nPage replacement with optimal "<<opt_rep;
  cout<<"\npage replacement penalty using LRU Stack "<<(float(lru_s_rep-opt_rep)/opt_rep)*100<<"%";
  cout<<"\nTotal time to run LRU Stack "<<lru_s_time<<" msec";
  cout<<"\nTotal time to run optimal algo "<<opt_time<<" msec";
  if(lru_s_time>opt_time) {
        cout<<"\nLRU Stack is "<<(float(lru_s_time-opt_time)/opt_time)*100<<"% slower than optimal algorithm";
  }
  else {
        cout<<"\nLRU Stack is "<<(float(opt_time-lru_s_time)/opt_time)*100<<"% faster than optimal algorithm";
  }
 
  gettimeofday(&tv, NULL);
  lru_c_rep=lru_clock(ibuf,len,frames);
  gettimeofday(&tv1, NULL);
  lru_c_time=tv1.tv_usec-tv.tv_usec;
  cout<<"\n\nPage replacement with LRU Clock "<<lru_c_rep;
  cout<<"\nPage replacement with optimal "<<opt_rep;
  cout<<"\npage replacement penalty using LRU Clock "<<(float(lru_c_rep-opt_rep)/opt_rep)*100<<"%";
  cout<<"\nTotal time to run LRU Clock "<<lru_c_time<<" msec";
  cout<<"\nTotal time to run optimal algo "<<opt_time<<" msec";
  if(lru_c_time>opt_time) {
        cout<<"\nLRU Clock is "<<(float(lru_c_time-opt_time)/opt_time)*100<<"% slower than optimal algorithm";
  }
  else {
        cout<<"\nLRU Clock is "<<(float(opt_time-lru_c_time)/opt_time)*100<<"% faster than optimal algorithm";
  }
  
  gettimeofday(&tv, NULL);
  lru_r_rep=lru_ref8(ibuf,len,frames);
  gettimeofday(&tv1, NULL);
  lru_r_time=tv1.tv_usec-tv.tv_usec;
  cout<<"\n\nPage replacement with LRU ref8 "<<lru_r_rep;
  cout<<"\nPage replacement with optimal "<<opt_rep;
  cout<<"\npage replacement penalty using LRU ref8 "<<(float(lru_r_rep-opt_rep)/opt_rep)*100<<"%";
  cout<<"\nTotal time to run LRU ref8 "<<lru_r_time<<" msec";
  cout<<"\nTotal time to run optimal algo "<<opt_time<<" msec";
  if(lru_r_time>opt_time) {
        cout<<"\nLRU ref8 is "<<(float(lru_r_time-opt_time)/opt_time)*100<<"% slower than optimal algorithm";
  }
  else {
        cout<<"\nLRU ref8 is "<<(float(opt_time-lru_r_time)/opt_time)*100<<"% faster than optimal algorithm";
  }
}
  

else {
    switch(sc_op) {
	case 1:
         gettimeofday(&tv, NULL);
  	 fif_rep=fifo(ibuf,len,frames);
  	 gettimeofday(&tv1, NULL);
	 fif_time=tv1.tv_usec-tv.tv_usec;
  	 cout<<endl<<"Page replacement with FIFO "<<fif_rep;
         cout<<endl<<"Page replacement with optimal "<<opt_rep;
  	 cout<<endl<<"%page replacement penalty using FIFO "<<(float(fif_rep-opt_rep)/opt_rep)*100<<"%";
         cout<<endl<<"Total time to run FIFO "<<fif_time<<" msec";
         cout<<endl<<"Total time to run optimal algo "<<opt_time<<" msec";
         if(fif_time>opt_time) {
               cout<<endl<<"FIFO is "<<(float(fif_time-opt_time)/opt_time)*100<<"% slower than optimal algorithm";
         }
         else {
               cout<<endl<<"FIFO is "<<(float(opt_time-fif_time)/opt_time)*100<<"% faster than optimal algorithm";
         }
         break;
         
        case 2:
        gettimeofday(&tv, NULL);
        lfu_rep=lfu(ibuf,len,frames);
        gettimeofday(&tv1, NULL);
        lfu_time=tv1.tv_usec-tv.tv_usec;
        cout<<"\n\nPage replacement with LFU "<<lfu_rep;
        cout<<"\nPage replacement with optimal "<<opt_rep;
        cout<<"\npage replacement penalty using LFU "<<(float(lfu_rep-opt_rep)/opt_rep)*100<<"%";
        cout<<"\nTotal time to run LFU "<<lfu_time<<" msec";
        cout<<"\nTotal time to run optimal algo "<<opt_time<<" msec";
        if(lfu_time>opt_time) {
             cout<<"\nLFU is "<<(float(lfu_time-opt_time)/opt_time)*100<<"% slower than optimal algorithm";
        }
        else {
             cout<<"\nLFU is "<<(float(opt_time-lfu_time)/opt_time)*100<<"% faster than optimal algorithm";
        }
        break;

	case 3:
        gettimeofday(&tv, NULL);
        lru_s_rep=lru_stack(ibuf,len,frames);
        gettimeofday(&tv1, NULL);
        lru_s_time=tv1.tv_usec-tv.tv_usec;
        cout<<"\n\nPage replacement with LRU Stack "<<lru_s_rep;
        cout<<"\nPage replacement with optimal "<<opt_rep;
        cout<<"\npage replacement penalty using LRU Stack "<<(float(lru_s_rep-opt_rep)/opt_rep)*100<<"%";
        cout<<"\nTotal time to run LRU Stack "<<lru_s_time<<" msec";
        cout<<"\nTotal time to run optimal algo "<<opt_time<<" msec";
        if(lru_s_time>opt_time) {
            cout<<"\nLRU Stack is "<<(float(lru_s_time-opt_time)/opt_time)*100<<"% slower than optimal algorithm";
        }
        else {
            cout<<"\nLRU Stack is "<<(float(opt_time-lru_s_time)/opt_time)*100<<"% faster than optimal algorithm";
        }
      	break;
	
        case 4:
        gettimeofday(&tv, NULL);
        lru_c_rep=lru_clock(ibuf,len,frames);
        gettimeofday(&tv1, NULL);
        lru_c_time=tv1.tv_usec-tv.tv_usec;
        cout<<"\n\nPage replacement with LRU Clock "<<lru_c_rep;
        cout<<"\nPage replacement with optimal "<<opt_rep;
        cout<<"\npage replacement penalty using LRU Clock "<<(float(lru_c_rep-opt_rep)/opt_rep)*100<<"%";
        cout<<"\nTotal time to run LRU Clock "<<lru_c_time<<" msec";
        cout<<"\nTotal time to run optimal algo "<<opt_time<<" msec";
        if(lru_c_time>opt_time) {
            cout<<"\nLRU Clock is "<<(float(lru_c_time-opt_time)/opt_time)*100<<"% slower than optimal algorithm";
        }
        else {
            cout<<"\nLRU Clock is "<<(float(opt_time-lru_c_time)/opt_time)*100<<"% faster than optimal algorithm";
        }
        break;

	case 5:
        gettimeofday(&tv, NULL);
        lru_r_rep=lru_ref8(ibuf,len,frames);
        gettimeofday(&tv1, NULL);
        lru_r_time=tv1.tv_usec-tv.tv_usec;
        cout<<"\n\nPage replacement with LRU ref8 "<<lru_r_rep;
        cout<<"\nPage replacement with optimal "<<opt_rep;
        cout<<"\npage replacement penalty using LRU ref8 "<<(float(lru_r_rep-opt_rep)/opt_rep)*100<<"%";
        cout<<"\nTotal time to run LRU ref8 "<<lru_r_time<<" msec";
        cout<<"\nTotal time to run optimal algo "<<opt_time<<" msec";
        if(lru_r_time>opt_time) {
            cout<<"\nLRU ref8 is "<<(float(lru_r_time-opt_time)/opt_time)*100<<"% slower than optimal algorithm";
        }
        else {
            cout<<"\nLRU ref8 is "<<(float(opt_time-lru_r_time)/opt_time)*100<<"% faster than optimal algorithm";
        }
        break;

	default:
	  cout<<"invalid algo name";
	  break;
    }
}
}
cout<<"\n\n";
return 0;
}

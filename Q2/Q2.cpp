#include<iostream>
#include<graphics.h>
using namespace std;

// 20 10 30 18
// steap and gradual (+ive and -ive) , 0 ,inf

int main(){
	int x1,y1,x2,y2;
	cout<<"Enter Point 1, x-co-ordinate: "; cin>>x1;
	cout<<"Enter Point 1, y-co-ordinate: "; cin>>y1;
	cout<<"Enter Point 2, x-co-ordinate: "; cin>>x2;
	cout<<"Enter Point 2, y-co-ordinate: "; cin>>y2;
	int dx=x2-x1,dy=y2-y1;
	int a=dy,b=dx*-1;
	
	int dstart,dold_inc;
	
	// for gradual
	dstart=2*a+b;
	dold_inc=a;	// case <=0
	
	// for steap
	dstart=a+2*b;
	dold_inc=b;	// case <=0
	 
	int dold=dstart;
	cout<<"a:"<<a<<" b:"<<b<<" dstart:"<<dstart<<"\n";
	cout<<x1<<" "<<y1<<"\n";
	int y=y1,x=x1;
	
	int gd=DETECT,gm;
	
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	putpixel(x1,y1,RED);
	
//	for(int x=x1+1;x<=x2;x++){
//		if(dold<=0)
//			dold+=dold_inc;
//		else{
//			y++;
//			dold+=a+b;
//		}
//		cout<<x<<" "<<y<<"\n";
//		putpixel(x,y,RED);
//	}
	
	for(int y=y1+1;y<=y2;y++){
		if(dold>0)
			dold+=dold_inc;
		else{
			x++;
			dold+=a+b;
		}
		cout<<x<<" "<<y<<"\n";
		putpixel(x,y,RED);
	}
	
	
	
	getch();
	closegraph();
	return 0;
}


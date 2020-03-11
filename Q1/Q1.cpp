// dda

#include<iostream>
#include<cstdlib>
#include<fstream>
#include<graphics.h>
#include<conio.h>

// password: kmvlab01

using namespace std;
int main(){
	int x1,y1,x2,y2;
	cout<<"Enter Point 1, x-co-ordinate: "; cin>>x1;
	cout<<"Enter Point 1, y-co-ordinate: "; cin>>y1;
	cout<<"Enter Point 2, x-co-ordinate: "; cin>>x2;
	cout<<"Enter Point 2, y-co-ordinate: "; cin>>y2;
	int dx=x2-x1,dy=y2-y1;
	float step;
	if(abs(dx)>abs(dy))
		step=abs(dx);
	else
		step=abs(dy);
	float Xinc=dx/step, Yinc=dy/step;
	float x=x1,y=y1;
	
	int gd=DETECT,gm;
	
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	putpixel(x1,y1,RED);
	
	
//	ofstream fout;
//	fout.open("q1.csv");
//	fout<<"x1="<<x1<<",y1="<<y1<<",x2="<<x2<<",y2="<<y2<<"\n";
//	
//	fout<<x<<","<<y<<"\n";
	for(int i=0;i<step;i++){
		x+=Xinc; y+=Yinc;
		putpixel(x,y,RED);
//		fout<<x<<","<<y<<"\n";
	}
	
	getch();
	closegraph();
	return 0;
}



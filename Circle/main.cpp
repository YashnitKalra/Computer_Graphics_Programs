#include<iostream>
#include<graphics.h>
using namespace std;

void putPixels(int X,int Y, int x, int y){
	putpixel(X+x,Y+y,GREEN);
	putpixel(X+x,Y-y,GREEN);
	putpixel(X-x,Y+y,GREEN);
	putpixel(X-x,Y-y,GREEN);
	putpixel(X+y,Y+x,GREEN);
	putpixel(X+y,Y-x,GREEN);
	putpixel(X-y,Y+x,GREEN);
	putpixel(X-y,Y-x,GREEN);
}

void drawCircle(int X,int Y,int r){
	int d=5-4*r;	// d_start
	int x=0,y=r;
	putPixels(X,Y,x,y);
	
	while(y>=x){
		x++;
		if(d>0){	// south_east
			y--;
			d+=2*(x-y)+6;
		}
		else	// east
			d+=2*x+3;
		putPixels(X,Y,x,y);
	}
}

int main(){
	int x,y,r;
	cout<<"Enter x-coordinate of center of cirlce: ";
	cin>>x;
	cout<<"\nEnter y-coordinate of center of circle: ";
	cin>>y;
	cout<<"\nEnter radius of circle: ";
	cin>>r;
	
	int gd = DETECT, gm; 
	initgraph(&gd, &gm, "C:\\TC\\BGI");
	
	drawCircle(x,y,r);
	
	getch();
	closegraph();
	return 0;
}


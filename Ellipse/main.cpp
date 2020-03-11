#include<iostream>
#include<graphics.h>
using namespace std;

void putPixels(int X,int Y,int x,int y){
	putpixel(X+x,Y+y,GREEN);
	putpixel(X+x,Y-y,GREEN);
	putpixel(X-x,Y+y,GREEN);
	putpixel(X-x,Y-y,GREEN);
}

void drawEllipse(int X,int Y,int a,int b){
	int d1,d2,dx,dy,x=0,y=b;
	
	// region 1
	d1=(4*b*b)+(a*a)-(4*a*a*b);
	dx=2*b*b*x;
	dy=2*a*a*y;
	
	// in region 1
	while(dx<dy){
		putPixels(X,Y,x,y);
		x++;
		dx+=2*b*b;
		if(d1<0){	//east
			d1+=(3*b*b)+(2*x*b*b);	
		}
		else{		//south-east
			y--;
			dy-=2*a*a;
			d1+=(3*b*b)+(2*x*b*b)+(2*a*a)-(2*y*a*a);
		}
	}
	
	//region 2
	d2 = ((b*b)*((x+0.5)*(x+0.5)))+((a*a)*((y-1)*(y-1)))-(a*a*b*b);
	
	// in region 2
//	while (y > 0){
//		cout<<y<<", ";
//        putPixels(X,Y,x,y);
//        y--;
//        dy-=(2 * a * a);
//        if (d2>0){	//south
//            d2+= (3*a*a)-(2*a*a*y);
//        } 
//        else{		//south-east
//            x++; 
//            dx = dx + (2 * b * b); 
//            d2+=(2*b*b)+(5*x*b*b)+(3*a*a)-(2*a*a*y); 
//        }
//    }
    while (y >0){ 
        putPixels(X,Y,x,y);
        if (d2 > 0){ 
            y--; 
            dy = dy - (2 * a * a); 
            d2 = d2 + (a * a) - dy; 
        } 
        else{ 
            y--; 
            x++; 
            dx = dx + (2 * b * b); 
            dy = dy - (2 * a * a); 
            d2 = d2 + dx - dy + (a * a); 
        } 
    } 
}

int main(){
	int x,y,minor,major;
	cout<<"Enter x-coordinate of center of ellipse: ";
	cin>>x;
	cout<<"\nEnter y-coordinate of center of ellipse: ";
	cin>>y;
	cout<<"\nEnter length of minor-axis: ";
	cin>>minor;
	cout<<"\nEnter length of major-axis: ";
	cin>>major;
	
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	
	drawEllipse(x,y,major,minor);
	
	getch();
	closegraph();
	
	return 0;
}

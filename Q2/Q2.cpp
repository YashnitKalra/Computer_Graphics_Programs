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
	float slope=(float)dy/(float)dx;
	cout<<slope;
	
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	
	if(dx==0)		// vertical line
		for(int y=min(y1,y2);y<=max(y1,y2);y++)
			putpixel(x1,y,RED);
			
	else if(dy==0)	// horizontal line
		for(int x=min(x1,x2);x<=max(x1,x2);x++)
			putpixel(x,y1,RED);
			
	else{
		int x=x1,y=y1;
		if(slope>1){	// steep
			if(slope>0){	// +ive slope
				int D=dy-2*dx;
				for(y=y1;y<=y2;y++){
					putpixel(x,y,RED);
					if(D<0){
						x++;
						D+=dy-dx;
					}
					else
						D-=dx;
				}
			}
			else{			// -ive slope
				int D=2*dx-dy;
				for(y=y1;y>=y2;y--){
					putpixel(x,y,RED);
					if(D>0){
						x--;
						D-=dy-dx;
					}
					else
						D+=dx;
				}
			}
		}
		else{			// gradual
			if(slope>0){	// +ive slope
				int D=2*dy-dx;
				for(x=x1;x<=x2;x++){
					putpixel(x,y,RED);
					if(D>0){
						y++;
						D+=dy-dx;
					}
					else
						D+=dy;
				}
			}
			else{			// -ive slope
				int D=dx-2*dy;
				for(x=x1;x>=x2;x--){
					putpixel(x,y,RED);
					if(D<0){
						y++;
						D-=dy+dx;
					}
					else
						D+=dy;
				}
			}		
		}
	}
	
	getch();
	closegraph();
	return 0;
}

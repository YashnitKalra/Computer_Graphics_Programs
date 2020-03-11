#include<iostream>
#include<graphics.h>
#include<vector>
using namespace std;

int l,t,r,b;	

bool inside(int x,int y){
	return (x>=l && x<=r && y>=t && y<=b);
}

int getXintersect(int x1,int y1,int x2,int y2,int y){
	float m=(float)(y2-y1)/(float)(x2-x1);
	float c=(float)y1-(float)(m*x1);
	return ((y-c)/m);
}

int getYintersect(int x1,int y1,int x2,int y2,int x){
	float m=(float)(y2-y1)/(float)(x2-x1);
	float c=(float)y1-(float)(m*x1);
	return (m*x+c);
}

int *getIntersectionPoint(int x_inside,int y_inside,int x_outside,int y_outside){
	int *point=new int[2];
	if(x_outside<l){
		point[0]=l;
		point[1]=getYintersect(x_inside,y_inside,x_outside,y_outside,l);
	}
	else if(x_outside>r){
		point[0]=r;
		point[1]=getYintersect(x_inside,y_inside,x_outside,y_outside,r);
	}
	else if(y_outside<t){
		point[1]=t;
		point[0]=getXintersect(x_inside,y_inside,x_outside,y_outside,t);
	}
	else if(y_outside>b){
		point[1]=b;
		point[0]=getXintersect(x_inside,y_inside,x_outside,y_outside,b);
	}
	return point;
}

vector<int> getClippedVertices(int vertices[],int m){
	// starting from last points
	int xs=vertices[m-4];
	int ys=vertices[m-3];
	vector<int> clippedVertices;
	// visiting all points
	for(int i=0;i<m-2;i+=2){
		int xp=vertices[i];
		int yp=vertices[i+1];
		if(inside(xp,yp)){
			if(inside(xs,ys)){
				clippedVertices.push_back(xp);
				clippedVertices.push_back(yp);
				line(xs,ys,xp,yp);
			}
			else{
				int *intersectionPoint=getIntersectionPoint(xp,yp,xs,ys);
				clippedVertices.push_back(intersectionPoint[0]);
				clippedVertices.push_back(intersectionPoint[1]);
				clippedVertices.push_back(xp);
				clippedVertices.push_back(yp);
				line(xp,yp,intersectionPoint[0],intersectionPoint[1]);
			}
		}
		else{
			if(inside(xs,ys)){
				int *intersectionPoint=getIntersectionPoint(xs,ys,xp,yp);
				clippedVertices.push_back(intersectionPoint[0]);
				clippedVertices.push_back(intersectionPoint[1]);
				line(xs,ys,intersectionPoint[0],intersectionPoint[1]);
			}
		}
		xs=xp;
		ys=yp;
	}
	return clippedVertices;
}

int main(){
	cout<<"Enter left-coordinate of rectange: ";
	cin>>l;
	cout<<"Enter top-coordinate of rectange: ";
	cin>>t;
	cout<<"Enter right-coordinate of rectange: ";
	cin>>r;
	cout<<"Enter bottom-coordinate of rectange: ";
	cin>>b;
	int n;
	cout<<"Enter number of vertices of the polygon: ";
	cin>>n;
	int m=(n+1)*2;
	int vertices[m];
	for(int i=0;i<m-2;i+=2){
		cout<<"\nEnter x-coordinate for vertex "<<i/2+1<<": ";
		cin>>vertices[i];
		cout<<"Enter y-coordinate for vertex "<<i/2+1<<": ";
		cin>>vertices[i+1];
	}
	vertices[m-2]=vertices[0];
	vertices[m-1]=vertices[1];
	
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	rectangle(l,t,r,b);
	setcolor(GREEN);
	drawpoly(m/2,vertices);
	getch();
	
	cleardevice();
	setcolor(WHITE);
	rectangle(l,t,r,b);
	setcolor(GREEN);
	vector<int> clippedVertices=getClippedVertices(vertices,m);
//	drawpoly(clippedVertices.size()/2,clippedVertices.data());
	cout<<"Output: ";
	for(int i=0;i<clippedVertices.size();i+=2)
		cout<<"("<<clippedVertices[i]<<", "<<clippedVertices[i+1]<<"), ";
	
	getch();
	closegraph();
	
	return 0;
}

//input
//200
//200
//500
//400
//3
//20
//30
//300
//300
//200
//450

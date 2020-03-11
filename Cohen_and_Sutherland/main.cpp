#include<iostream>
#include<graphics.h>
#include<utility> 
#include<vector>
using namespace std;

int l,t,r,b;
int INSIDE = 0;		//0000 
int LEFT = 1;		//0001 
int RIGHT = 2;		//0010 
int BOTTOM = 4;		//0100 
int TOP = 8;		//1000

int getCode(int x,int y){
	int code=0;
	if(x<l)
		code|=LEFT;
	else if(x>r)
		code|=RIGHT;
	if(y<t)
		code|=TOP;
	else if(y>b)
		code|=BOTTOM;
	return code;
}

int getXintersect(pair<pair<int,int>,pair<int,int> > line,int y){
	float m=(float)(line.second.second-line.first.second)/(float)(line.second.first-line.first.first);
	float c=(float)line.first.second-(float)(m*line.first.first);
	int x=(y-c)/m;
	return (x);
}

int getYintersect(pair<pair<int,int>,pair<int,int> > line,int x){
	float m=(float)(line.second.second-line.first.second)/(float)(line.second.first-line.first.first);
	float c=(float)line.first.second-(float)(m*line.first.first);
	return (m*x+c);
}

vector<pair<pair<int,int>,pair<int,int> > > getClippedLines(pair<pair<int,int>,pair<int,int> > lines[],int n){
	vector<pair<pair<int,int>,pair<int,int> > > clippedLines;
	for(int i=0;i<n;i++){
		int code1=getCode(lines[i].first.first,lines[i].first.second);
		int code2=getCode(lines[i].second.first,lines[i].second.second);
		if(code1==0 && code2==0)	//inside
			clippedLines.push_back(lines[i]);
		else if((code1 & code2)==0){		//partially inside and outside
			pair<pair<int,int>,pair<int,int> > line=lines[i];
			//point 1
			if(code1 & LEFT){
				line.first.second=getYintersect(line,l);
				line.first.first=l;
			}
			else if(code1 & RIGHT){
				line.first.second=getYintersect(line,r);
				line.first.first=r;
			}
			if(code1 & TOP){
				line.first.first=getXintersect(line,t);
				line.first.second=t;
			}
			else if(code1 & BOTTOM){
				line.first.first=getXintersect(line,b);
				line.first.second=b;
			}
			//point 2
			if(code2 & LEFT){
				line.second.second=getYintersect(line,l);
				line.second.first=l;
			}
			else if(code2 & RIGHT){
				line.second.second=getYintersect(line,r);
				line.second.first=r;
			}
			if(code2 & TOP){
				line.second.first=getXintersect(line,t);
				line.second.second=t;
			}
			else if(code2 & BOTTOM){
				line.second.first=getXintersect(line,b);
				line.second.second=b;
			}
			clippedLines.push_back(line);
		}
		//else outside so discard
	}
	return clippedLines;
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
	cout<<"Enter number of line segments: ";
	cin>>n;
	pair<pair<int,int>,pair<int,int> > lines[n];
	
	for(int i=1;i<=n;i++){
		cout<<"\nEnter x1 for line "<<i<<": ";
		cin>>lines[i-1].first.first;
		cout<<"Enter y1 for line "<<i<<": ";
		cin>>lines[i-1].first.second;
		cout<<"Enter x2 for line "<<i<<": ";
		cin>>lines[i-1].second.first;
		cout<<"Enter y2 for line "<<i<<": ";
		cin>>lines[i-1].second.second;
	}
	
	int gd=DETECT,gm;
	initgraph(&gd, &gm, "C:\\TC\\BGI");
	
	rectangle(l,t,r,b);
	setcolor(GREEN);
	for(int i=0;i<n;i++){
		line(lines[i].first.first,lines[i].first.second,lines[i].second.first,lines[i].second.second);
	}
	
	getch();
	cleardevice();
	
	vector<pair<pair<int,int>,pair<int,int> > > clippedLines=getClippedLines(lines,n);
	
	setcolor(WHITE);
	rectangle(l,t,r,b);
	setcolor(GREEN);
	for(int i=0;i<clippedLines.size();i++){
		line(clippedLines.at(i).first.first,clippedLines.at(i).first.second,clippedLines.at(i).second.first,clippedLines.at(i).second.second);
	}
	getch();
	closegraph();
	
	return 0;
}

//input

//200
//200
//500
//400
//4
//50
//50
//600
//550
//100
//100
//100
//500
//370
//300
//250
//265
//160
//170
//400
//350

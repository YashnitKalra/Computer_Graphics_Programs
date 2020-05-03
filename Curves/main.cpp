#include<iostream>
#include<utility>	
#include<math.h>
#include<graphics.h>
#include<vector>

using namespace std;

void plot(float x[],float y[],int n){
	int gd = DETECT, gm; 
	initgraph(&gd, &gm, "C:\\TC\\BGI");
	for(int i=0;i<n;i++)
		putpixel(x[i],y[i],GREEN);
	getch();
	closegraph();
}

pair<float,float>* enterControlPoints(int n){
	pair<float,float> *cp=new pair<float,float>[n];
	for(int i=0;i<n;i++){
		cout<<"Enter Control Point "<<i+1<<" (space seperated): ";
		cin>>cp[i].first;
		cin>>cp[i].second;
	}
	return cp;
}

void hermite(int n){
	pair<float,float> *cp=enterControlPoints(n);
	float x[101],y[101];
	int i=0;
	float t2,t3;
	for(float t=0;t<=1;t+=0.01,i++){
		t2=pow(t,2);
		t3=pow(t,3);
		x[i]=(2*t3-3*t2+1)*cp[0].first + (t3-2*t2+t)*cp[1].first + (-2*t3+3*t2)*cp[2].first + (t3-t2)*cp[3].first;
		y[i]=(2*t3-3*t2+1)*cp[0].second + (t3-2*t2+t)*cp[1].second + (-2*t3+3*t2)*cp[2].second + (t3-t2)*cp[3].second;
	}
	plot(x,y,101);
}

void bezier(int n){
	pair<float,float> *cp=enterControlPoints(n);
	float x[101],y[101];
	int i=0;
	for(float t=0;t<=1;t+=0.01,i+=1){
		x[i]=pow(1-t,3)*cp[0].first + 3*t*pow(1-t,2)*cp[1].first + 3*pow(t,2)*(1-t)*cp[2].first + pow(t,3)*cp[3].first;
		y[i]=pow(1-t,3)*cp[0].second + 3*t*pow(1-t,2)*cp[1].second + 3*pow(t,2)*(1-t)*cp[2].second + pow(t,3)*cp[3].second;
	}
	plot(x,y,101);
}

int main(){
	int choice;
	Again:
	cout<<"1. Hermite Curve\n2. Bezier Curve\n\nEnter Choice: ";
	cin>>choice;
	switch(choice){
		case 1:
			hermite(4);
			break;
		case 2:
			bezier(4);
			break;
		default:
			cout<<"Invalid Choice\n"; goto Again;
	}
	return 0;
}


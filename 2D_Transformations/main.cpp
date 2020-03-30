#include<iostream>
#include<vector>
#include<graphics.h>
#include<math.h>
using namespace std;

class Matrix{
	public:
		int rows,columns;
		float **arr;
		Matrix(){}
		Matrix(int r,int c){
			rows=r;
			columns=c;
			arr=new float* [r];
			for(int i=0;i<r;i++){
				arr[i]=new float[c];
				for(int j=0;j<c;j++)
					arr[i][j]=0;
			}
		}
		void print(){
			for(int i=0;i<rows;i++){
				cout<<"[ ";
				for(int j=0;j<columns;j++)
					cout<<arr[i][j]<<" ";
				cout<<"]\n";
			}
		}
		static Matrix multiply(Matrix m1, Matrix m2){
			Matrix m(m1.rows,m2.columns);
			for(int i=0;i<m.rows;i++){
				for(int j=0;j<m.columns;j++){
					for(int k=0;k<m1.columns;k++)
						m.arr[i][j]+=m1.arr[i][k]*m2.arr[k][j];
				}
			}
			return m;
		}
};

void plot(vector<int> arr1,vector<int> arr2){
	arr1.push_back(arr1[0]);
	arr1.push_back(arr1[1]);
	arr2.push_back(arr2[0]);
	arr2.push_back(arr2[1]);
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	setcolor(GREEN);
	drawpoly(arr1.size()/2,arr1.data());
	getch();
	cleardevice();
	setcolor(GREEN);
	drawpoly(arr2.size()/2,arr2.data());
	getch();
	closegraph();
}

Matrix getTransformationMatrix(){
	Matrix t(3,3);
	float arr[][3]={
		{1,0,0},
		{0,1,0},
		{0,0,1}
	};
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			t.arr[i][j]=arr[i][j];
	return t;
}

void translate(Matrix m[],int n,vector<int> p){
	Matrix t=getTransformationMatrix();
	vector<int> points;
	cout<<"\nEnter translation for x-coordinates: ";
	cin>>t.arr[2][0];
	cout<<"Enter translation for y-coordinates: ";
	cin>>t.arr[2][1];
	cout<<"Transformation Matrix:\n";
	t.print();
	cout<<"RESULT:\n";
	for(int i=0;i<n;i++){
		m[i]=Matrix::multiply(m[i],t);
		points.push_back(m[i].arr[0][0]); points.push_back(m[i].arr[0][1]);
		cout<<"Vertex "<<i+1<<": ";
		m[i].print();
	}
	plot(p,points);
}

void rotate(Matrix m[],int n,vector<int> p){
	Matrix t=getTransformationMatrix();
	vector<int> points;
	int r;
	cout<<"\nEnter angle of rotation: ";
	cin>>r;
	t.arr[0][0]=cos(r); t.arr[0][1]=sin(r);
	t.arr[1][0]=-1*sin(r); t.arr[1][1]=cos(r);
	cout<<"Transformation Matrix:\n";
	t.print();
	cout<<"RESULT:\n";
	for(int i=0;i<n;i++){
		m[i]=Matrix::multiply(m[i],t);
		points.push_back(m[i].arr[0][0]); points.push_back(m[i].arr[0][1]);
		cout<<"Vertex "<<i+1<<": ";
		m[i].print();
	}
	plot(p,points);
}

void scale(Matrix m[],int n,vector<int> p){
	Matrix t=getTransformationMatrix();
	vector<int> points;
	int s;
	cout<<"\nEnter scaling factor: ";
	cin>>s;
	t.arr[0][0]=s; t.arr[1][1]=s;
	cout<<"Transformation Matrix:\n";
	t.print();
	cout<<"RESULT:\n";
	for(int i=0;i<n;i++){
		m[i]=Matrix::multiply(m[i],t);
		points.push_back(m[i].arr[0][0]); points.push_back(m[i].arr[0][1]);
		cout<<"Vertex "<<i+1<<": ";
		m[i].print();
	}
	plot(p,points);
}

void reflect(Matrix m[],int n,vector<int> p){
	// https://www.onlinemath4all.com/reflection-transformation-matrix.html#ContentColumn
	Matrix t=getTransformationMatrix();
	Again:	// switch case default
	cout<<"\n\nReflect About:\n\n1. X-Axis\n2. Y-Axis\n3. Line Y=X\n4. Line Y=-X\n5. Origin\n\nEnter Choice: ";
	int choice; cin>>choice;
	vector <int> points;
	switch(choice){
		case 1:
			t.arr[1][1]=-1; break;
		case 2:
			t.arr[0][0]=-1; break;
		case 3:
			t.arr[0][0]=0; t.arr[0][1]=1; t.arr[1][0]=1; t.arr[1][1]=0; break;
		case 4:
			t.arr[0][0]=0; t.arr[0][1]=-1; t.arr[1][0]=-1; t.arr[1][1]=0; break;
		case 5:
			t.arr[0][0]=-1; t.arr[1][1]=-1; break;
		default:
			goto Again; break;
	}
	cout<<"Transformation Matrix:\n";
	t.print();
	cout<<"RESULT:\n";
	for(int i=0;i<n;i++){
		m[i]=Matrix::multiply(m[i],t);
		points.push_back(m[i].arr[0][0]); points.push_back(m[i].arr[0][1]);
		cout<<"Vertex "<<i+1<<": ";
		m[i].print();
	}
	plot(p,points);	
}

int main(){
	int n;
	cout<<"Enter number of vertices: ";
	cin>>n;
	Matrix m[n];
	vector<int> points;
	for(int i=0;i<n;i++){
		m[i]=Matrix(1,3);
		cout<<"\nEnter x-coordinate of vertex "<<i+1<<": ";
		cin>>m[i].arr[0][0];	points.push_back(m[i].arr[0][0]);
		cout<<"Enter y-coordinate of vertex "<<i+1<<": ";
		cin>>m[i].arr[0][1];	points.push_back(m[i].arr[0][1]);
		m[i].arr[0][2]=1;
	}
	int choice;
	cout<<"\nPoints are:\n";
	for(int i=0;i<n;i++){
		cout<<"Vertex "<<i+1<<": ";
		m[i].print();
	}
	
	// menu
	cout<<"\n1. Translate\n2. Rotate\n3. Scale\n4. Reflection\n\nEnter Choice: ";
	cin>>choice;
	switch(choice){
		case 1:
			translate(m,n,points); break;
		case 2:
			rotate(m,n,points); break;
		case 3:
			scale(m,n,points); break;
		case 4:
			reflect(m,n,points); break;
		default:
			break;
	}
	return 0;
}
//input
//translate
//3
//100
//100
//50
//200
//150
//200
//1
//50
//-50

//rotate
//3
//100.05
//100.5
//50.5
//200.5
//150.5
//200.5
//2
//0.785398

//scale
//3
//100
//100
//50
//200
//150
//200
//3
//2

// reflection
//3
//300
//300
//400
//400
//200
//400
//4

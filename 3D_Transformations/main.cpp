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

void plot(vector<int> arr){
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	setcolor(GREEN);
	drawpoly(arr.size()/2,arr.data());
	getch();
	closegraph();
}

Matrix getTransformationMatrix(){
	Matrix t(4,4);
	float arr[][4]={
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1},
	};
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			t.arr[i][j]=arr[i][j];
	return t;
}

void translate(Matrix m[],int n){
	Matrix t=getTransformationMatrix();
	
	cout<<"\nEnter translation for x-coordinates: ";
	cin>>t.arr[3][0];
	cout<<"Enter translation for y-coordinates: ";
	cin>>t.arr[3][1];
	cout<<"Enter translation for z-coordinates: ";
	cin>>t.arr[3][2];
	cout<<"Transformation Matrix:\n";
	t.print();
	cout<<"RESULT:\n";
	for(int i=0;i<n;i++){
		m[i]=Matrix::multiply(m[i],t);
		cout<<"Vertex "<<i+1<<": ";
		m[i].print();
	}

}

void rotate(Matrix m[],int n,int choice,float r){
	Matrix t=getTransformationMatrix();
	switch(choice){
		case 1:
			t.arr[1][1] = cos(r); t.arr[1][2] = sin(r);
			t.arr[2][1] = -sin(r); t.arr[2][2] = cos(r);
			break;
		case 2:
			t.arr[0][0] = cos(r); t.arr[0][2] = -sin(r);
			t.arr[2][0] = sin(r); t.arr[2][2] = cos(r);
			break;
		case 3:
			t.arr[0][0] = cos(r); t.arr[0][1] = sin(r);
			t.arr[1][0] = -sin(r); t.arr[1][1] = cos(r);
			break;
		default:
			cout<<"\nWrong Axis Choice"; return;
	}
	cout<<"Transformation Matrix:\n";
	t.print();
	cout<<"RESULT:\n";
	for(int i=0;i<n;i++){
		m[i]=Matrix::multiply(m[i],t);
		cout<<"Vertex "<<i+1<<": ";
		m[i].print();
	}
}

void scale(Matrix m[],int n){
	Matrix t=getTransformationMatrix();
	int sx,sy,sz;
	cout<<"\nEnter scaling factors sx,sy,sz: ";
	cin>>sx>>sy>>sz;
	t.arr[0][0]=sx; t.arr[1][1]=sy; t.arr[2][2]=sz;
	cout<<"Transformation Matrix:\n";
	t.print();
	cout<<"RESULT:\n";
	for(int i=0;i<n;i++){
		m[i]=Matrix::multiply(m[i],t);
		cout<<"Vertex "<<i+1<<": ";
		m[i].print();
	}
}

void reflect(Matrix m[],int n){
	Matrix t=getTransformationMatrix();
	Again:	// switch case default
	cout<<"\n\nReflect About:\n\n1. X-Axis\n2. Y-Axis\n3. Z-Axis\n4. XY Plane\n5. YZ Plane\n6. XZ Plane\n\nEnter Choice: ";
	int choice; cin>>choice;
	switch(choice){
		case 1:
			t.arr[1][1]=-1; t.arr[2][2]=-1; break;
		case 2:
			t.arr[0][0]=-1; t.arr[2][2]=-1; break;
		case 3:
			t.arr[1][1]=-1; t.arr[2][2]=-1; break;
		case 4:
			t.arr[2][2]=-1; break;
		case 5:
			t.arr[0][0]=-1; break;
		case 6:
			t.arr[1][1]=-1; break;
		default:
			goto Again; break;
	}
	cout<<"Transformation Matrix:\n";
	t.print();
	cout<<"RESULT:\n";
	for(int i=0;i<n;i++){
		m[i]=Matrix::multiply(m[i],t);
		cout<<"Vertex "<<i+1<<": ";
		m[i].print();
	}
}

void orthographic(Matrix m[],int n,char plane){
	Matrix t=getTransformationMatrix();
	vector<int> points;
	cout<<"Result:\n\n";
	switch(plane){
		case 'x':
			t.arr[0][0]=0;
			for(int i=0;i<n;i++){
				m[i]=Matrix::multiply(m[i],t);
				cout<<"Vertex "<<i+1<<": ";
				points.push_back(m[i].arr[0][1]); points.push_back(m[i].arr[0][2]);
				m[i].print();
			}
			break;
		case 'y':
			t.arr[1][1]=0;
			for(int i=0;i<n;i++){
				m[i]=Matrix::multiply(m[i],t);
				cout<<"Vertex "<<i+1<<": ";
				points.push_back(m[i].arr[0][0]); points.push_back(m[i].arr[0][2]);
				m[i].print();
			}
			break;
		case 'z':
			t.arr[2][2]=0;
			for(int i=0;i<n;i++){
				m[i]=Matrix::multiply(m[i],t);
				cout<<"Vertex "<<i+1<<": ";
				points.push_back(m[i].arr[0][0]); points.push_back(m[i].arr[0][1]);
				m[i].print();
			}
			break;
	}
	plot(points);
}

void axonometric(Matrix m[],int n,float phi,float theta){
	rotate(m,n,2,phi);		// about y-axis
	rotate(m,n,1,theta);	// about x-axis
	orthographic(m,n,'z');	// project onto z=0 plane
}

void oblique(Matrix m[],int n,float f,float alpha){
	Matrix t=getTransformationMatrix();
	float a=f*cos(alpha);
	float b=f*sin(alpha);
	t.arr[2][2]=0;
	t.arr[2][0]=-a;
	t.arr[2][1]=-b;
	vector<int> points;
	for(int i=0;i<n;i++){
		m[i]=Matrix::multiply(m[i],t);
		cout<<"Vertex "<<i+1<<": ";
		points.push_back(m[i].arr[0][0]); points.push_back(m[i].arr[0][1]);
		m[i].print();
	}
	plot(points);
}

void perspective(Matrix m[],int n,float x,float y,float z){
	Matrix t=getTransformationMatrix();
	t.arr[0][3]=x;
	t.arr[1][3]=y;
	t.arr[2][3]=z;
	t.arr[2][2]=0;
	cout<<"\nTransformation Matrix:\n";
	t.print();
	vector<int> points;
	for(int i=0;i<n;i++){
		m[i]=Matrix::multiply(m[i],t);
		for(int j=0;j<4;j++)
			m[i].arr[0][j]/=m[i].arr[0][3];
		cout<<"Vertex "<<i+1<<": ";
		points.push_back(m[i].arr[0][0]); points.push_back(m[i].arr[0][1]);
		m[i].print();
	}
	plot(points);
}

// *************************************************************************************
int main(){
	int n;
	cout<<"Enter number of vertices: ";
	cin>>n;
	Matrix m[n];
	
	for(int i=0;i<n;i++){
		m[i]=Matrix(1,4);
		cout<<"\nEnter x-coordinate of vertex "<<i+1<<": ";
		cin>>m[i].arr[0][0];	
		cout<<"Enter y-coordinate of vertex "<<i+1<<": ";
		cin>>m[i].arr[0][1];	
		cout<<"Enter z-coordinate of vertex "<<i+1<<": ";
		cin>>m[i].arr[0][2];
		m[i].arr[0][3]=1;
	}
	int choice;
	cout<<"\nPoints are:\n";
	for(int i=0;i<n;i++){
		cout<<"Vertex "<<i+1<<": ";
		m[i].print();
	}
	
	char ch;
	do{
		// menu
		cout<<"\n1. Translate\n2. Rotate\n3. Scale\n4. Reflection\n\nEnter Choice: ";
		cin>>choice;
		switch(choice){
			case 1:
				translate(m,n); break;
			case 2:
				cout<<"\n\nRotate About:\n\n1. X-Axis\n2. Y-Axis\n3. Z-Axis\n\nEnter Choice: ";
				int axis_choice; cin>>axis_choice;
				float r;
				cout<<"\nEnter angle of rotation: ";
				cin>>r;
				r=r*3.14/180;	// convert to radians
				rotate(m,n,axis_choice,r); break;
			case 3:
				scale(m,n); break;
			case 4:
				reflect(m,n); break;
			default:
				break;
		}
		cout<<"\n\nDo you want to perform more transformations? (y/n): ";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	
	// projection menu
	cout<<"\n\n1. Orthographic onto x=0 plane\n2. Orthographic onto y=0 plane\n3. Orthographic onto z=0 plane\n4. Trimetric\n5. Dimetric\n6. Isometric\n7. Cavalier\n8. Cabinet\n9. Single Point Perspective\n10. Two Point Perspective\n11. Three Point Perspesctive\n\nEnter Choice: ";
	cin>>choice;
	float phi,theta;
	switch(choice){
		// orthographic
		case 1:
			orthographic(m,n,'x'); break;
		case 2:
			orthographic(m,n,'y'); break;
		case 3:
			orthographic(m,n,'z'); break;
		// axonometric
		case 4:
			cout<<"Enter angle of rotation about y-axis: ";
			cin>>phi;
			cout<<"Enter angle of rotation about x-axis: ";
			cin>>theta;
			phi*=3.14/180; theta*=3.14/180;
			axonometric(m,n,phi,theta); break;
		case 5:
			cout<<"Enter value of fz [0,1]: ";
			float fz; cin>>fz;
			phi=asin(fz/pow(2,0.5));
			theta=asin(fz/(pow(2-pow(fz,2),0.5)));
			axonometric(m,n,phi,theta); break;
		case 6:
			phi=45*3.14/180;
			theta=35.26*3.14/180;
			axonometric(m,n,phi,theta); break;
		// oblique
		case 7:
			cout<<"Enter angle between horizontal and projected z-axis: ";
			cin>>theta;
			oblique(m,n,1,theta*3.14/180);
			break;
		case 8:
			cout<<"Enter angle between horizontal and projected z-axis: ";
			cin>>theta;
			oblique(m,n,0.5,theta*3.14/180);
			break;
		// perpective
		case 9:
			perspective(m,n,0,0,0.05);
			break;
		case 10:
			perspective(m,n,0.001,0.001,0);
			break;
		case 11:
			perspective(m,n,0.001,0.001,0.001);
			break;
		default:
			break;
	}
	
	return 0;
}

// cube with one edge removed
//10
//100 100 200
//200 100 200
//200 150 200
//150 200 200
//100 200 200
//100 100 100
//200 100 100
//200 200 100
//100 200 100
//200 200 150

// cube
//8
//100 100 200
//200 100 200
//200 200 200
//100 200 200
//100 200 100
//200 200 100
//200 100 100
//100 100 100

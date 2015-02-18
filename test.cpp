#include<iostream>
#include<vector>
#include"poly_class.h"
using namespace std;
int main(int argc, char* argv[]){
    poly_class<double> a,b;
    b[0]=1;b[2]=1;b[1]=2;
    cout<<b<<endl;
    a[1]=1;
    cout<<pow(a,2)<<endl;
    //a[0]=1;a[1]=1;
    //cout<<b.derivative()<<endl;getchar();
    cout<<b%a<<endl;
    return 0;
}

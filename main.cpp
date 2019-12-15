//#include"bigIntNum.h"
#include<iostream>
#include<chrono>
#include<fstream>
using namespace std;
int main()
{
 //   ifstream file("test.txt");
//    bigIntNum a,b;
//    file>>a>>b;
//    cout<<a<<endl;
//    cout<<b<<endl;
//    //cout<<"Nhap a ,b : ";
//    //cin>>a>>b;
//    cout<<a.digit()<<endl;
//    cout<<b.digit()<<endl;
//     auto start = chrono::high_resolution_clock::now();
//    cout<<(a/b)<<endl;
 auto start = chrono::high_resolution_clock::now();
    long double a1 = 0;
    long double a2 = 1;
    long double a3;
    int t =2;
while(t!=10000)
    {   a3 = a1+a2;
        a2 = a3;
        a1 = a2;
        t++;
}
    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;
    cout<<a3<<endl;
    cout<<"Elapsed : "<<elapsed.count()<<" s\n"<<endl;

}

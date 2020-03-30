/*
C++ program to
design a macro to
perform add operation.
*/
#include <iostream>
#define ADD(x,y) x+y;

using namespace std;
int main()
{
    int num1, num2;
    cout<<"Enter first number: ";
    cin>>num1;
    cout<<"Enter second number: ";
    cin>>num2;
    int sum = ADD(num1, num2);
    cout<<"\nSum using Addition MACRO: "<<sum<<endl;
    return 0;
}

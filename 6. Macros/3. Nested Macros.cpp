/*
C++ program
to implement
nested macro definitions.
*/
#include <iostream>
#define SQUARE(x) (x*x)
#define CUBE(x) x*SQUARE(x)

using namespace std;
int main()
{
    int num;
    cout<<"Enter a number: ";
    cin>>num;
    cout<<"Cube of the number using nested MACROS: "<<CUBE(num)<<endl;
    return 0;
}

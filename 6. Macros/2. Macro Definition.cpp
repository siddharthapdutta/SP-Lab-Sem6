/*
C++ program output text file of
macro definition from the
given input assembly source code.
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int main()
{
    string line;
    string start = "MACRO";
    string end = "MEND";
    int flag = -1;
    ifstream inpfile ("Source Program.txt");
    ofstream outfile ("Macro Definition.txt");
    if (inpfile.is_open())
    {
        while (getline(inpfile, line))
        {
            if (line.substr(0, start.length()) == start)
                flag = 1;
            if (flag == 1)
                outfile<<line<<endl;
            if (line.substr(0, end.length()) == end)
                flag = -1;
        }
    }
    cout<<"Macro definition saved in: 'Macro Definition.txt'"<<endl;
    inpfile.close();
    outfile.close();
    return 0;
}
